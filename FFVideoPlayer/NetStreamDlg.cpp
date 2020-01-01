/*

ÍøÂçÁ÷´°¿Ú

*/

#include "NetStreamDlg.h"
#include "CommonUtils.h"


NetStreamDlg::NetStreamDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	m_iniPath = qApp->applicationDirPath() + "\\config\\StreamAddress.ini";
	m_iniKey = "/rtmp/ip";

	setFixedSize(this->width(), this->height());
	ui.lineEdit_IP->setText(CommonUtils::readIni(m_iniPath, m_iniKey));
}

NetStreamDlg::~NetStreamDlg()
{
}

void NetStreamDlg::closeEvent(QCloseEvent * e)
{
	QString address = ui.lineEdit_IP->text();
	CommonUtils::writeIni(m_iniPath, m_iniKey, address);
	emit(PushStream(address));
}
