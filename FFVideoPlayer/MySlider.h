/*

重载QSlider类

*/

#pragma once
#include <QtWidgets/QSlider>
#include <QtGui/QMouseEvent>

class MySlider:public QSlider
{
	Q_OBJECT

public:
	MySlider(QWidget *p = NULL);  //改构造函数
	~MySlider();

	void mousePressEvent(QMouseEvent *e); //重写该函数
};

