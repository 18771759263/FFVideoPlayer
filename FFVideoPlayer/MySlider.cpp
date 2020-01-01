#include "MySlider.h"



MySlider::MySlider(QWidget *p):QSlider(p)
{
}


MySlider::~MySlider()
{
}

void MySlider::mousePressEvent(QMouseEvent *e)
{
	int value = ((float)(e->pos().x()) / (float)(this->width())) * (this->maximum() + 1);
	this->setValue(value);
	QSlider::mousePressEvent(e);
}
