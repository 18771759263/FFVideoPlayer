#pragma once

#include <QDialog>
#include "ui_NetStreamDlg.h"

class NetStreamDlg : public QDialog
{
	Q_OBJECT

public:
	NetStreamDlg(QWidget *parent = Q_NULLPTR);
	~NetStreamDlg();

	void closeEvent(QCloseEvent * e);

signals:
	void PushStream(QString address);

private:
	Ui::NetStreamDlg ui;
	QString m_iniPath;
	QString m_iniKey;
};
