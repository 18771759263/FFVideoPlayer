#include "NetStreamThread.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
}

#include<iostream>
using namespace std;

NetStreamThread* NetStreamThread::m_Net = NULL;
NetStreamThread::GC NetStreamThread::m_gc;

//获取网络流线程对象
NetStreamThread* NetStreamThread::getInstance()
{
	if (m_Net == NULL)
	{
		m_Net = new NetStreamThread();
	}

	return m_Net;
}

NetStreamThread::NetStreamThread()
{
}

NetStreamThread::~NetStreamThread()
{
}

void NetStreamThread::startPlay(QString url)
{
	m_Url = url;
	this->start();   //启动线程
}

void NetStreamThread::run()
{
	AVFormatContext *pFormatCtx;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
	AVFrame *pFrame, *pFrameRGB;
	AVPacket *packet;
	uint8_t *out_buffer;

	static struct SwsContext *img_convert_ctx;
	int videoStream;
	int i;
	int numBytes;
	int got_picture;

	av_register_all();
	avformat_network_init();

	pFormatCtx = avformat_alloc_context();

	AVDictionary* avdic = NULL;
	av_dict_set(&avdic, "buffer_size", "108000", 0); //设置缓存大小，1080p可将值调大
	av_dict_set(&avdic, "rtsp_transport", "udp", 0); //以udp方式打开，如果以tcp方式打开将udp替换为tcp
	av_dict_set(&avdic, "stimeout", "2000000", 0);   //设置超时断开连接时间，单位微秒
	av_dict_set(&avdic, "max_delay", "500000", 0);   //设置最大时延

	if (avformat_open_input(&pFormatCtx, m_Url.toStdString().c_str(), NULL, &avdic) != 0) 
	{
		return;
	}

	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) 
	{
		return;
	}

	videoStream = -1;

	for (i = 0; i < pFormatCtx->nb_streams; i++) 
	{
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) 
		{
			videoStream = i;
		}
	}

	if (videoStream == -1) 
	{
		return;
	}

	//查找解码器
	pCodecCtx = pFormatCtx->streams[videoStream]->codec;
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

	pCodecCtx->bit_rate = 0;   
	pCodecCtx->time_base.num = 1;  
	pCodecCtx->time_base.den = 10;
	pCodecCtx->frame_number = 1;  

	if (pCodec == NULL)
	{
		return;
	}

	//打开解码器
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		return;
	}

	pFrame = av_frame_alloc();
	pFrameRGB = av_frame_alloc();

	int outW = pCodecCtx->width;
	int outH = pCodecCtx->height;

	//将解码后的YUV数据转换成RGB32
	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
		pCodecCtx->pix_fmt, outW, outH,
		AV_PIX_FMT_RGB32, SWS_BICUBIC, NULL, NULL, NULL);

	numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, outW, outH);

	out_buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
	avpicture_fill((AVPicture *)pFrameRGB, out_buffer, AV_PIX_FMT_RGB32,
		outW, outH);

	int y_size = outW * outH;

	packet = (AVPacket *)malloc(sizeof(AVPacket)); //分配一个packet
	av_new_packet(packet, y_size); //分配packet的数据

	while (1)
	{
		if (av_read_frame(pFormatCtx, packet) < 0)
		{
			break; //这里认为视频读取完了
		}

		if (packet->stream_index == videoStream) 
		{
			int ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);

			if (ret < 0) 
			{
				return;
			}

			if (got_picture) 
			{
				sws_scale(img_convert_ctx,
					(uint8_t const * const *)pFrame->data,
					pFrame->linesize, 0, outH, pFrameRGB->data,
					pFrameRGB->linesize);

				//把这个RGB数据 用QImage加载
				QImage tmpImg((uchar *)out_buffer, outW, outH, QImage::Format_RGB32);
				QImage image = tmpImg.copy();  //把图像复制一份 传递给界面显示

				emit sig_GetOneFrame(image);  //发送图像
			}
		}

		av_free_packet(packet); //释放资源,否则内存会一直上升
		msleep(0.02); //停一停  不然放的太快了
	}

	av_free(out_buffer);
	av_free(pFrameRGB);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);
}