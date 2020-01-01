/*

关于本软件对话框

*/

#include "AboutDlg.h"


AboutDlg::AboutDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setFixedSize(this->width(), this->height());
}

AboutDlg::~AboutDlg()
{
}
