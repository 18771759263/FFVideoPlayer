#pragma once
#include <iostream>
#include <string>
#include <QtCore/QMutex>

extern "C" 
{
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
    #include <libswresample/swresample.h>
}

#include <Windows.h>

using namespace std;

/*

ffmpeg 打开视频，音视频解码，资源释放等

*/

class MyFFmpeg
{
public:
	//单例模式，对象的销毁用内部类实现，后续修改
	static MyFFmpeg *Get()
	{
		static MyFFmpeg ff;
		return &ff;
	}

	int Open(const char *path); //打开视频,直接返回文件的总时长
	void Close();
	int Decode(const AVPacket *pkt); //返回 pts

	AVPacket Read();
	bool ToRGB(char *out, int outweight, int outheight);
	int ToPCM(char *out);
	bool Seek(float pos); //pos 0--1

	int GetPts(const AVPacket *pkt);

	void SetVolume(char* buf, UINT32 size, UINT32 uRepeat, double vol); //设置音量
	


	string GetError();

	virtual ~MyFFmpeg();

public:
	int m_totalMs;
	int m_videoStream = 0;
	int m_fps = 0;
	int m_pts; //当前视频播放进度
	bool m_isPlay = false;
	int m_audioStream = 1;

	int m_sampleRate = 48000;
	int m_sampleSize = 16;
	int m_channel = 2;

	double m_VolumeRatio = 1.00; //音量比例

protected:
	MyFFmpeg();

	char m_errbuf[1024];
	QMutex m_mutex; //线程同步
	AVFormatContext* m_afc;
	AVFrame *m_yuv = NULL;
	AVFrame *m_pcm = NULL; //存放解码后的音频
	
	SwsContext *m_cCtx = NULL; //转换器
	SwrContext *m_aCtx = NULL; //音频
};

