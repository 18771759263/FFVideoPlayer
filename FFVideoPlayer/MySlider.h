/*

����QSlider��

*/

#pragma once
#include <QtWidgets/QSlider>
#include <QtGui/QMouseEvent>

class MySlider:public QSlider
{
	Q_OBJECT

public:
	MySlider(QWidget *p = NULL);  //�Ĺ��캯��
	~MySlider();

	void mousePressEvent(QMouseEvent *e); //��д�ú���
};

