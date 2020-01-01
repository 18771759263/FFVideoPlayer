#include "VideoWidget.h"
#include <QtGui/QPainter>
#include "MyFFmpeg.h"
#include "VideoThread.h"
#include "NetStreamThread.h"

extern int g_NetStream;

VideoWidget::VideoWidget(QWidget *p):QOpenGLWidget(p)
{
	startTimer(20); //刷新视频
	
	VideoThread::Get()->start(); //启动线程，在线程中读取，让视频不卡
	
	connect(NetStreamThread::getInstance(), SIGNAL(sig_GetOneFrame(QImage)), this, SLOT(ReceiveImage(QImage)));
}

VideoWidget::~VideoWidget()
{
}

//重写重绘函数
void VideoWidget::paintEvent(QPaintEvent *e)
{
	if (g_NetStream == 1)
	{
		QPainter painter;

		//显示网络流
		painter.begin(this);
		painter.drawImage(QPoint(448, 170), m_Image);
		painter.end();
	}
	else
	{
		static QImage *image = NULL;
		static int w = 0; //记录之前的窗口大小
		static int h = 0;
		if (w != width() || h != height())
		{
			//如果窗口大小发生变化，删除内存
			if (image)
			{
				delete image->bits();  //删除QImage的内部空间
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

		//开始绘图，视频播放
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