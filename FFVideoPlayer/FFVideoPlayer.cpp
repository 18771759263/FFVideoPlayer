/*

������

*/

#include "FFVideoPlayer.h"
#include <QFileDialog>
#include "MyFFmpeg.h"
#include <QMessageBox>
#include "AudioPlay.h"
#include <string>
#include <iostream>
#include "VideoThread.h"
#include <QCursor>
#include "AboutDlg.h"
#include "NetStreamThread.h"
#include "MyLog.h"
#include <QDesktopServices>


using namespace std;

//ȫ�־�̬����ֻ�ڸ�cpp�ļ�����Ч
static bool ispressSlider = false;

static bool g_isPlay = true;
int g_NetStream;

FFVideoPlayer::FFVideoPlayer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_Hour = 0;
	m_Min = 0;
	m_Second = 0;
	m_isMute = false;

	showMaximized(); //�����ʾ   
	setMinimumSize(QSize(800, 512)); //���ô�����С�ߴ�

	LOG4CPLUS_INFO(MyLog::getInstance()->logger, "Program Start, init UI");
	initUI();

#ifdef _DEBUG
	setWindowTitle("FFVideoPlayer_D");
#else
	setWindowTitle("FFVideoPlayer");
#endif

	startTimer(40);
	allConnect();
}

void FFVideoPlayer::initUI()
{
	//MainWindow����ɫ
	setStyleSheet("background-color: rgb(53, 53, 53);");

	//�˵���ɫ
	ui.menuBar->setStyleSheet("background-color:rgb(53,53,53); border:1px solid gray; color:white; padding: 1px;");

	ui.label_Playtime->clear();
	ui.label_Playtime->setText("00:00:00/00:00:00");

	//������ť��ͼ
	setButtonBackImage(ui.btnPlayVideo, "./Resources/play.png");
	setButtonBackImage(ui.btnSetVolume, "./Resources/volume.png");
	setButtonBackImage(ui.btnFullScreen, "./Resources/fullscreen.png");
}

void FFVideoPlayer::allConnect()
{
	connect(ui.btnPlayVideo, SIGNAL(clicked()), this, SLOT(slotPlay()));
	connect(ui.timeSlider, SIGNAL(sliderPressed()), this, SLOT(slotSliderPressed()));
	connect(ui.timeSlider, SIGNAL(sliderReleased()), this, SLOT(soltSliderReleased()));

	//�˵�
	connect(ui.action_OpenLocalFiles, SIGNAL(triggered()), this, SLOT(OpenLocalVideo()));
	connect(ui.action_OpenNetStream, SIGNAL(triggered()), this, SLOT(OpenNetStreamDlg()));
	connect(ui.action_About, SIGNAL(triggered()), this, SLOT(PopAboutDlg()));
	connect(ui.action_GetSourceCode, SIGNAL(triggered()), this, SLOT(GetSourceCode()));

	//��������
	connect(ui.sliderVolume, SIGNAL(sliderReleased()), this, SLOT(volumeAdjust()));
	connect(ui.btnSetVolume, SIGNAL(clicked()), this, SLOT(setMute()));

	connect(&m_NetDlg, SIGNAL(PushStream(QString)), this, SLOT(slotPushStream(QString)));
}

void FFVideoPlayer::OpenLocalVideo()
{
	LOG4CPLUS_INFO(MyLog::getInstance()->logger, "Open Local Video File");
	QString filename = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ����Ƶ�ļ�"));
	if (filename.isEmpty())
	{
		return;
	}

	string videoPath = string((const char *)filename.toLocal8Bit()); //QStringתstring
	int n1 = videoPath.find_last_of('/');
	int n2 = videoPath.find_last_of('\0');
	string sname = videoPath.substr(n1 + 1, n2);
	QString qstr = QString(QString::fromLocal8Bit(sname.c_str())); //stringתQString
	this->setWindowTitle(qstr);

	int totalMs = MyFFmpeg::Get()->Open(filename.toLocal8Bit());
	if (totalMs <= 0)
	{
		QMessageBox::information(this, "err", "file open failed!");
		LOG4CPLUS_INFO(MyLog::getInstance()->logger, "Open Local Video File Failed");
		return;
	}

	AudioPlay::Get()->sampleRate = MyFFmpeg::Get()->m_sampleRate;
	AudioPlay::Get()->channel = MyFFmpeg::Get()->m_channel;
	AudioPlay::Get()->sampleSize = 16;

	AudioPlay::Get()->Start();

	char buf[1024] = { 0 };
	int seconds = totalMs / 1000;
	m_Hour = seconds / 3600;
	m_Min = (seconds - m_Hour * 3600) / 60;
	m_Second = seconds - m_Hour * 3600 - m_Min * 60;

	g_isPlay = false;
	slotPlay();
}

/**
 * @brief ��ʱ���¼�
 * @param e
 */
void FFVideoPlayer::timerEvent(QTimerEvent *e)
{
	int playseconds = MyFFmpeg::Get()->m_pts / 1000;
	int hour = playseconds / 3600;
	int min = (playseconds - hour * 3600) / 60;
	int sec = playseconds - hour * 3600 - min * 60;
	char buf[1024] = { 0 };
	sprintf(buf, "%02d:%02d:%2d/%02d:%02d:%2d", hour, min, sec,m_Hour, m_Min, m_Second);
	this->ui.label_Playtime->setText(buf);  //��ǰ����ʱ��

	if (MyFFmpeg::Get()->m_totalMs > 0)
	{
		float rate = MyFFmpeg::Get()->m_pts / (float(MyFFmpeg::Get()->m_totalMs));

		//ֻ�а����ˣ��Ų���ʾ������
		if (!ispressSlider)
		{
			this->ui.timeSlider->setValue(rate * 1000); //������
		}

		//        if(ui.timeSlider->geometry().contains(this->mapFromGlobal(QCursor::pos())))
		//        {
		//            ui.timeSlider->show();
		//            ui.timeSlider->setValue(rate * 1000); //������
		//        }
		//        else
		//        {
		//            ui.timeSlider->hide();
		//        }
	}
}

/**
 * @brief ��Ӧ���������µ��ź�
 */
void FFVideoPlayer::slotSliderPressed()
{
	ispressSlider = true;
}

/**
 * @brief ��Ӧ����ɿ����������ź�
 */
void FFVideoPlayer::soltSliderReleased()
{
	ispressSlider = false;
	float pos = 0;
	pos = this->ui.timeSlider->value() / static_cast<float>(ui.timeSlider->maximum() + 1); //��0��ʼ�ģ������÷�ĸΪ0
	MyFFmpeg::Get()->Seek(pos);
}

/**
 * @brief ������Ƶ
 */
void FFVideoPlayer::slotPlay()
{
	g_isPlay = !g_isPlay;
	MyFFmpeg::Get()->m_isPlay = g_isPlay;

	if (g_isPlay)
	{
		setButtonBackImage(ui.btnPlayVideo, "./Resources/stop.png");
	}
	else
	{
		setButtonBackImage(ui.btnPlayVideo, "./Resources/play.png");
	}
}

/**
 * @brief ���ڹر�ʱ�Ĳ���
 * @param e
 */
void FFVideoPlayer::closeEvent(QCloseEvent * e)
{
	//�����߳�
	VideoThread::Get()->terminate();
}

//���ڴ�С�����仯ʱ�����ؼ���С��λ�ü���С������
void FFVideoPlayer::resizeEvent(QResizeEvent *e)
{
	if (isFullScreen())
	{
		ui.openGLWidget->move(0, 0);
		ui.openGLWidget->resize(this->width(), this->height());
	}
	else
	{
		ui.openGLWidget->move(0, 0);
		ui.openGLWidget->resize(this->width(), this->height() - 62);

		ui.timeSlider->move(0, this->height() - 80);
		ui.timeSlider->resize(this->width(), 20);
		ui.label_Playtime->move(5, this->height() - 60);
		ui.btnPlayVideo->move(this->width() / 2 - 15, this->height() - 60);
		ui.btnSetVolume->move(this->width() * 4 / 5, this->height() - 60);
		ui.sliderVolume->move(this->width() * 4 / 5 + 31, this->height() - 60);
		ui.btnFullScreen->move(this->width() - 40, this->height() - 60);
	}
}

/**
 * @brief FFVideoPlayer::on_fullScreenBtn_clicked
 *        ȫ����ť
 */
void FFVideoPlayer::on_btnFullScreen_clicked()
{
	if (!isFullScreen())
	{
		fullShow();
	}
}

/**
 * @brief FFVideoPlayer::mouseDoubleClickEvent
 *        ���˫��
 */
void FFVideoPlayer::mouseDoubleClickEvent(QMouseEvent*)
{
	if (this->isFullScreen())
	{
		normalShow();
	}
	else
	{
		fullShow();
	}
}

/**
 * @brief ȫ��ʱ������ť����
 */
void FFVideoPlayer::fullShow()
{
	this->showFullScreen();

	ui.menuBar->hide();
	ui.timeSlider->hide();
	ui.label_Playtime->hide();
	ui.btnPlayVideo->hide();
	ui.btnSetVolume->hide();
	ui.sliderVolume->hide();
	ui.btnFullScreen->hide();
}

/**
 * @brief ������ʾʱ�����ؼ�����ʾ
 */
void FFVideoPlayer::normalShow()
{
	this->showNormal();

	ui.menuBar->show();
	ui.timeSlider->show();
	ui.label_Playtime->show();
	ui.btnPlayVideo->show();
	ui.btnSetVolume->show();
	ui.sliderVolume->show();
	ui.btnFullScreen->show();
}

//�˵�--��������
void FFVideoPlayer::OpenNetStreamDlg()
{
	//NetStreamDlg nDlg;
	
	m_NetDlg.exec();
}

void FFVideoPlayer::PopAboutDlg()
{
	AboutDlg dlg;
	dlg.exec();
}

//��������
void FFVideoPlayer::volumeAdjust()
{
	MyFFmpeg::Get()->m_VolumeRatio = (ui.sliderVolume->value()) * 1.00 / 100;
}

//��������
void FFVideoPlayer::setMute()
{
	m_isMute = !m_isMute;
	if (m_isMute)
	{
		MyFFmpeg::Get()->m_VolumeRatio = 0;
		setButtonBackImage(ui.btnSetVolume, "./Resources/mute.png");
	}
	else
	{
		MyFFmpeg::Get()->m_VolumeRatio = 0.5;
		setButtonBackImage(ui.btnSetVolume, "./Resources/volume.png");
	}
}

//���ð�ťͼ�꣬��ť��Ĭ�ϴ�С�� 30*30
void FFVideoPlayer::setButtonBackImage(QPushButton *button, QString image)
{  
	QPixmap pixmap(image);
	QPixmap fitpixmap = pixmap.scaled(30, 30).scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	button->setIcon(QIcon(fitpixmap));
	button->setIconSize(QSize(30, 30));
	button->setFlat(true);  //��ť͸��  
	button->setStyleSheet("border: 0px"); //�����߿�
}

void FFVideoPlayer::slotPushStream(QString address)
{
	LOG4CPLUS_INFO(MyLog::getInstance()->logger, "Push Net Stream");
	g_NetStream = 1;

	setWindowTitle(address);
	NetStreamThread::getInstance()->startPlay(address);
}

//��ȡԴ����
void FFVideoPlayer::GetSourceCode()
{
	QDesktopServices::openUrl(QUrl(QString("https://github.com/linghuzhangmen/FFVideoPlayer.git")));
}