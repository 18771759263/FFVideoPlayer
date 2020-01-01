#include "VideoThread.h"
#include "MyFFmpeg.h"
#include "AudioPlay.h"
#include <list>

using namespace std;

static list<AVPacket> g_videos;
static int g_apts = -1;


VideoThread::VideoThread()
{

}


VideoThread::~VideoThread()
{

}

void VideoThread::run()
{
	char out[10000] = { 0 };
	while (1)
	{
		if (!MyFFmpeg::Get()->m_isPlay)
		{
			msleep(10);
			continue;
		}

		while (g_videos.size() > 0)
		{
			AVPacket pack = g_videos.front();
			int pts = MyFFmpeg::Get()->GetPts(&pack);

			/*
            if (pts > g_apts)  //不注释这儿, 滑动可能会有问题
			{
				break;
            }
			*/

			MyFFmpeg::Get()->Decode(&pack);
			av_packet_unref(&pack);
			g_videos.pop_front();
		}

		int free = AudioPlay::Get()->GetFree();

		if (free < 10000)  
		{
			msleep(1);
			continue;
		}

		//这时视频已经打开了
		AVPacket pkt = MyFFmpeg::Get()->Read();  //读取视频帧
		if (pkt.size <= 0)
		{
			msleep(10);
		}

		if (pkt.stream_index == MyFFmpeg::Get()->m_audioStream)
		{
			g_apts = MyFFmpeg::Get()->Decode(&pkt);
			av_packet_unref(&pkt);
			int len = MyFFmpeg::Get()->ToPCM(out);
			AudioPlay::Get()->Write(out, len);
			continue;
		}

		if (pkt.stream_index != MyFFmpeg::Get()->m_videoStream)
		{
			av_packet_unref(&pkt);
			continue;
		}

		g_videos.push_back(pkt);
	}
}
