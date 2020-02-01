#include "StreamInfoDlg.h"

StreamInfoDlg::StreamInfoDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setFixedSize(this->width(), this->height());
}

StreamInfoDlg::~StreamInfoDlg()
{
}
