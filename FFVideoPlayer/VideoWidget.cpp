#include "VideoWidget.h"
#include <QtGui/QPainter>
#include "MyFFmpeg.h"
#include "VideoThread.h"
#include "NetStreamThread.h"

extern int g_NetStream;

VideoWidget::VideoWidget(QWidget *p):QOpenGLWidget(p)
{
	startTimer(20); //ˢ����Ƶ
	
	VideoThread::Get()->start(); //�����̣߳����߳��ж�ȡ������Ƶ����
	
	connect(NetStreamThread::getInstance(), SIGNAL(sig_GetOneFrame(QImage)), this, SLOT(ReceiveImage(QImage)));
}

VideoWidget::~VideoWidget()
{
}

//��д�ػ溯��
void VideoWidget::paintEvent(QPaintEvent *e)
{
	if (g_NetStream == 1)
	{
		QPainter painter;

		//��ʾ������
		painter.begin(this);
		painter.drawImage(QPoint(448, 170), m_Image);
		painter.end();
	}
	else
	{
		static QImage *image = NULL;
		static int w = 0; //��¼֮ǰ�Ĵ��ڴ�С
		static int h = 0;
		if (w != width() || h != height())
		{
			//������ڴ�С�����仯��ɾ���ڴ�
			if (image)
			{
				delete image->bits();  //ɾ��QImage���ڲ��ռ�
				delete image;
				image = NULL;
			}
		}

		if (image == NULL)
		{
			uchar *buf = new uchar[width() * height() * 4];
			image = new QImage(buf, width(), height(), QImage::Format_ARGB32);
		}

		MyFFmpeg::Get()->ToRGB((char *)(image->bits()), width(), height());

		QPainter painter;

		//��ʼ��ͼ����Ƶ����
		painter.begin(this);
		painter.drawImage(QPoint(0, 0), *image);
		painter.end();
	}
}

void VideoWidget::timerEvent(QTimerEvent *e)
{
	this->update();
}

void VideoWidget::ReceiveImage(QImage img)
{
	m_Image = img;
	this->update();
}