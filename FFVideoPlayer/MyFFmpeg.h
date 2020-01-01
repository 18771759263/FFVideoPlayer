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

ffmpeg ����Ƶ������Ƶ���룬��Դ�ͷŵ�

*/

class MyFFmpeg
{
public:
	//����ģʽ��������������ڲ���ʵ�֣������޸�
	static MyFFmpeg *Get()
	{
		static MyFFmpeg ff;
		return &ff;
	}

	int Open(const char *path); //����Ƶ,ֱ�ӷ����ļ�����ʱ��
	void Close();
	int Decode(const AVPacket *pkt); //���� pts

	AVPacket Read();
	bool ToRGB(char *out, int outweight, int outheight);
	int ToPCM(char *out);
	bool Seek(float pos); //pos 0--1

	int GetPts(const AVPacket *pkt);

	void SetVolume(char* buf, UINT32 size, UINT32 uRepeat, double vol); //��������
	


	string GetError();

	virtual ~MyFFmpeg();

public:
	int m_totalMs;
	int m_videoStream = 0;
	int m_fps = 0;
	int m_pts; //��ǰ��Ƶ���Ž���
	bool m_isPlay = false;
	int m_audioStream = 1;

	int m_sampleRate = 48000;
	int m_sampleSize = 16;
	int m_channel = 2;

	double m_VolumeRatio = 1.00; //��������

protected:
	MyFFmpeg();

	char m_errbuf[1024];
	QMutex m_mutex; //�߳�ͬ��
	AVFormatContext* m_afc;
	AVFrame *m_yuv = NULL;
	AVFrame *m_pcm = NULL; //��Ž�������Ƶ
	
	SwsContext *m_cCtx = NULL; //ת����
	SwrContext *m_aCtx = NULL; //��Ƶ
};

