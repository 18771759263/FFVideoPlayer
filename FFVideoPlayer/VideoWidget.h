/*

 ”∆µœ‘ æ¿‡

*/

#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/QOpenGLWidget>

class VideoWidget : public QOpenGLWidget
{
	Q_OBJECT

public:
	VideoWidget(QWidget *p = NULL);
	void paintEvent(QPaintEvent *e);
	void timerEvent(QTimerEvent *e);

	~VideoWidget();

private slots:
	void ReceiveImage(QImage img);

private:
	QImage m_Image;
};

