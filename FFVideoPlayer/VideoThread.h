#pragma once
#include <QtCore/QThread>

class VideoThread : public QThread
{
public:
	static VideoThread *Get()
	{
		static VideoThread vt;
		return &vt;
	}

	~VideoThread();

	void run(); //��дQThread��run()

protected:
	VideoThread();
};

