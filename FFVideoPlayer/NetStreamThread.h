/*

网络流播放线程

*/

#pragma once

#include <QThread>
#include <QImage>

class NetStreamThread : public QThread
{
	Q_OBJECT

public:
	static NetStreamThread* getInstance();
	~NetStreamThread();

	void startPlay(QString url);
	void run();

signals:
	void sig_GetOneFrame(QImage);

private:
	NetStreamThread();

	//内部类，释放单例内存
	class GC
	{
	public:
		~GC()
		{
			if (m_Net != NULL)
			{
				NetStreamThread::getInstance()->terminate();

				delete m_Net;
				m_Net = NULL;
			}
		}
	};

	

private:
	QString m_Url;    //网络流地址
	static GC m_gc;
	static NetStreamThread *m_Net;
};
