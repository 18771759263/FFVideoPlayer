#include "MyFFmpeg.h"
#include <QtWidgets/QMessageBox>

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "swresample.lib") //重采样

static double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

MyFFmpeg::MyFFmpeg()
{
	m_errbuf[0] = '\0';

	//ffmpeg编程的第一句
	av_register_all(); 
}

MyFFmpeg::~MyFFmpeg()
{
}

//打开视频
int MyFFmpeg::Open(const char *path) 
{
	Close(); //先关闭上次的视频

	m_mutex.lock();
	
	int nRet = avformat_open_input(&m_afc, path, 0, 0);
	if (nRet != 0)
	{
		m_mutex.unlock();
		char buf[1024] = { 0 };
		av_strerror(nRet, buf, sizeof(buf));
		return 0;
	}

	m_totalMs = (m_afc->duration / AV_TIME_BASE) * 1000;  //视频的时间，结果是多少豪秒

	//打开解码器
	for (int i = 0; i < m_afc->nb_streams; i++)  //nb_streams打开的视频文件中流的数量，一般nb_streams = 2，音频流和视频流
	{
		AVCodecContext *acc = m_afc->streams[i]->codec; //分别获取音频流和视频流的解码器

		if (acc->codec_type == AVMEDIA_TYPE_VIDEO)   //如果是视频
		{
			m_videoStream = i;

			//FPS（Frames Per Second）：每秒传输帧数。   Frames Per Second更确切的解释是“每秒钟填充图像的帧数（帧/秒）”。FPS是测量用于保存、显示  帧面板使用
			m_fps = r2d(m_afc->streams[i]->avg_frame_rate);
			AVCodec *codec = avcodec_find_decoder(acc->codec_id);   // 解码器

			//"没有该类型的解码器"
			if (!codec) 
			{
				m_mutex.unlock();
				return 0;
			}

			int err = avcodec_open2(acc, codec, NULL);

			if (err != 0)
			{
				m_mutex.unlock();
				char buf[1024] = { 0 };
				av_strerror(err, buf, sizeof(buf));
				return 0;
			}
		}             //解码音频
		else if (acc->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			m_audioStream = i;
			AVCodec *codec = avcodec_find_decoder(acc->codec_id);
			if (avcodec_open2(acc, codec, NULL) < 0)
			{
				m_mutex.unlock();
				return false;
			}

			//设置音频的参数：采样频率和通道数
			this->m_sampleRate = acc->sample_rate;
			this->m_channel = acc->channels;
			switch (acc->sample_fmt)
			{
			case AV_SAMPLE_FMT_S16:         // signed 16 bits
				this->m_sampleSize = 16;
				break;
			case AV_SAMPLE_FMT_S32:
				this->m_sampleSize = 32;
				break;
			default:
				break;
			}
		}
	}

	m_mutex.unlock();

	return m_totalMs;
}

void MyFFmpeg::Close()
{
	m_mutex.lock();
	if (m_afc)
	{
		avformat_close_input(&m_afc);
	}

	if (m_yuv)
	{
		av_frame_free(&m_yuv);
	}

	if (m_cCtx)
	{
		sws_freeContext(m_cCtx);
		m_cCtx = NULL;
	}

	if (m_aCtx)
	{
		swr_free(&m_aCtx);
	}

	m_mutex.unlock();
}

string MyFFmpeg::GetError()
{
	m_mutex.lock();
	string re = this->m_errbuf;
	m_mutex.unlock();
	return re;
}

AVPacket MyFFmpeg::Read()
{
	AVPacket pkt;
	memset(&pkt, 0, sizeof(AVPacket));

	m_mutex.lock();
	if (!m_afc)
	{
		m_mutex.unlock();
		return pkt;
	}

	int err = av_read_frame(m_afc, &pkt);
	if (err != 0)
	{
		av_strerror(err, m_errbuf, sizeof(m_errbuf));
	}
	m_mutex.unlock();

	return  pkt;
}

//解码
int MyFFmpeg::Decode(const AVPacket *pkt)
{
	m_mutex.lock();

	if (!m_afc)
	{
		m_mutex.unlock();
		return NULL;
	}
	if (m_yuv == NULL)
	{
		m_yuv = av_frame_alloc();
	}

	if (m_pcm == NULL)
	{
		m_pcm = av_frame_alloc();
	}

	AVFrame *frame = m_yuv;
	if (pkt->stream_index == m_audioStream)
	{
		frame = m_pcm;
	}

	int re = avcodec_send_packet(m_afc->streams[pkt->stream_index]->codec, pkt);
	if (re != 0)
	{
		m_mutex.unlock();
		return NULL;
	}

	re = avcodec_receive_frame(m_afc->streams[pkt->stream_index]->codec, frame);
	if (re != 0)
	{
		m_mutex.unlock();
		return NULL;
	}

	m_mutex.unlock();
	int p = (frame->pts * r2d(m_afc->streams[pkt->stream_index]->time_base)) * 1000; //毫秒数
	if (pkt->stream_index == m_audioStream)
	{
		this->m_pts = p;
	}

	return m_pts;
}

bool MyFFmpeg::ToRGB(char *out, int outweight, int outheight)
{
	m_mutex.lock();
	if (!m_afc || !m_yuv) //如果视频没有打开
	{
		m_mutex.unlock();
		return false;
	}

	AVCodecContext *videoCtx = m_afc->streams[this->m_videoStream]->codec;
	m_cCtx = sws_getCachedContext(m_cCtx, videoCtx->width, videoCtx->height,
		videoCtx->pix_fmt,  //像素点的格式
		outweight, outheight,  //目标宽度与高度
		AV_PIX_FMT_BGRA,  //输出的格式
		SWS_BICUBIC,  //算法标记
		NULL, NULL, NULL
		);

	if (!m_cCtx)
	{
		m_mutex.unlock();
		return false;
	}

	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
	data[0] = (uint8_t *)out;  
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outweight * 4;  //每一行转码的宽度

    //返回转码后的高度
	int h = sws_scale(m_cCtx, m_yuv->data, m_yuv->linesize, 0, videoCtx->height,
		data,
		linesize
		);
	
	m_mutex.unlock();
}

int MyFFmpeg::ToPCM(char *out)
{
	m_mutex.lock();
	if (!m_afc || !m_pcm || !out)
	{
		m_mutex.unlock();
		return 0;
	}

	AVCodecContext *ctx = m_afc->streams[m_audioStream]->codec;
	if (m_aCtx == NULL)
	{
		m_aCtx = swr_alloc();

		//可能会出问题， 16位音频
		swr_alloc_set_opts(m_aCtx, ctx->channel_layout, 
			AV_SAMPLE_FMT_S16,
			ctx->sample_rate, 
			ctx->channels, 
			ctx->sample_fmt,
			ctx->sample_rate, 
			0, 0);

		swr_init(m_aCtx); //初始化样本转换
	}

	uint8_t *data[1];
	data[0] = (uint8_t *)out;
	int len = swr_convert(m_aCtx, data, 10000, (const uint8_t **)m_pcm->data, m_pcm->nb_samples);
	if (len <= 0)
	{
		m_mutex.unlock();
		return 0;
	}
	int outsize = av_samples_get_buffer_size(NULL, ctx->channels, m_pcm->nb_samples, AV_SAMPLE_FMT_S16, 0);

	//音量调节
	SetVolume(out, outsize, 1, m_VolumeRatio);

	m_mutex.unlock();

	return outsize;
}

bool MyFFmpeg::Seek(float pos)
{
	m_mutex.lock();

	if (!m_afc)
	{
		m_mutex.unlock();
		return false;
	}
	
	int64_t stamp = 0;
	stamp = pos * m_afc->streams[m_videoStream]->duration;
	int re = av_seek_frame(m_afc, m_videoStream, stamp, AVSEEK_FLAG_BACKWARD|AVSEEK_FLAG_FRAME); //向后|关键帧

	//清除之前的解码缓冲
	avcodec_flush_buffers(m_afc->streams[m_videoStream]->codec);
	m_mutex.unlock();
	if (re >= 0)
	{
		return true;
	}
	
	return false;
}

int MyFFmpeg::GetPts(const AVPacket *pkt)
{
	m_mutex.lock();
	if (!m_afc)
	{
		m_mutex.unlock();
		return -1;
	}
	int pts = (pkt->pts * r2d(m_afc->streams[pkt->stream_index]->time_base)) * 1000; //毫秒数
	m_mutex.unlock();
	return pts;
}

/*
* @Func   : SetVolume
* @brief  : 音量调节
* @author : linghuzhangmen
* @[in]   : buf 为需要调节音量的音频数据块首地址指针
* @[in]   : size为长度
* @[in]   : uRepeat为重复次数，通常设为1
* @[in]   : vol为增益倍数,可以小于1
*/
void MyFFmpeg::SetVolume(char* buf, UINT32 size, UINT32 uRepeat, double vol)
{
	if (!size)
	{
		return;
	}
	for (int i = 0; i < size; i += 2)
	{
		short wData;
		wData = MAKEWORD(buf[i], buf[i + 1]);
		long dwData = wData;
		for (int j = 0; j < uRepeat; j++)
		{
			dwData = dwData * vol;
			if (dwData < -0x8000)
			{
				dwData = -0x8000;
			}
			else if (dwData > 0x7FFF)
			{
				dwData = 0x7FFF;
			}
		}
		wData = LOWORD(dwData);
		buf[i] = LOBYTE(wData);
		buf[i + 1] = HIBYTE(wData);
	}
}

