/********************************************************************************
** Form generated from reading UI file 'FFVideoPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FFVIDEOPLAYER_H
#define UI_FFVIDEOPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "MySlider.h"
#include "videowidget.h"

QT_BEGIN_NAMESPACE

class Ui_FFVideoPlayerClass
{
public:
    QAction *action_OpenLocalFiles;
    QAction *action_OpenNetStream;
    QAction *action_OpenCamera;
    QAction *action_About;
    QAction *action_GetSourceCode;
    QWidget *centralWidget;
    VideoWidget *openGLWidget;
    QSlider *sliderVolume;
    QLabel *label_Playtime;
    QPushButton *btnPlayVideo;
    QPushButton *btnFullScreen;
    MySlider *timeSlider;
    QPushButton *btnSetVolume;
    QPushButton *btnCutImage;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QMenu *menu_Set;

    void setupUi(QMainWindow *FFVideoPlayerClass)
    {
        if (FFVideoPlayerClass->objectName().isEmpty())
            FFVideoPlayerClass->setObjectName(QString::fromUtf8("FFVideoPlayerClass"));
        FFVideoPlayerClass->resize(800, 512);
        FFVideoPlayerClass->setMinimumSize(QSize(0, 0));
        FFVideoPlayerClass->setStyleSheet(QString::fromUtf8(""));
        action_OpenLocalFiles = new QAction(FFVideoPlayerClass);
        action_OpenLocalFiles->setObjectName(QString::fromUtf8("action_OpenLocalFiles"));
        action_OpenNetStream = new QAction(FFVideoPlayerClass);
        action_OpenNetStream->setObjectName(QString::fromUtf8("action_OpenNetStream"));
        action_OpenCamera = new QAction(FFVideoPlayerClass);
        action_OpenCamera->setObjectName(QString::fromUtf8("action_OpenCamera"));
        action_About = new QAction(FFVideoPlayerClass);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_GetSourceCode = new QAction(FFVideoPlayerClass);
        action_GetSourceCode->setObjectName(QString::fromUtf8("action_GetSourceCode"));
        centralWidget = new QWidget(FFVideoPlayerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openGLWidget = new VideoWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 800, 450));
        openGLWidget->setStyleSheet(QString::fromUtf8(""));
        sliderVolume = new QSlider(centralWidget);
        sliderVolume->setObjectName(QString::fromUtf8("sliderVolume"));
        sliderVolume->setGeometry(QRect(630, 455, 80, 30));
        sliderVolume->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal \n"
"{\n"
"        height: 3px;\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71));\n"
"}\n"
"\n"
"QSlider::handle:horizontal \n"
"{\n"
"        width: 8px;\n"
"        background: rgb(0, 255, 255);\n"
"        margin: -3px 0px -3px 0px;\n"
"        border-radius: 4px;\n"
"}\n"
""));
        sliderVolume->setOrientation(Qt::Horizontal);
        label_Playtime = new QLabel(centralWidget);
        label_Playtime->setObjectName(QString::fromUtf8("label_Playtime"));
        label_Playtime->setGeometry(QRect(10, 455, 291, 30));
        label_Playtime->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	font-family: \"Microsoft YaHei\";\n"
"    font-size: 18px;\n"
"    color: white;\n"
"	background-color: rgb(53,53,53);\n"
"}\n"
""));
        btnPlayVideo = new QPushButton(centralWidget);
        btnPlayVideo->setObjectName(QString::fromUtf8("btnPlayVideo"));
        btnPlayVideo->setGeometry(QRect(385, 455, 30, 30));
        btnFullScreen = new QPushButton(centralWidget);
        btnFullScreen->setObjectName(QString::fromUtf8("btnFullScreen"));
        btnFullScreen->setGeometry(QRect(770, 455, 30, 30));
        timeSlider = new MySlider(centralWidget);
        timeSlider->setObjectName(QString::fromUtf8("timeSlider"));
        timeSlider->setGeometry(QRect(0, 430, 800, 20));
        timeSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"        height: 3px;\n"
"        background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71));\n"
"}\n"
"QSlider::handle:horizontal {\n"
"        width: 8px;\n"
"        background: rgb(255, 255, 255);\n"
"        margin: -3px 0px -3px 0px;\n"
"}\n"
""));
        timeSlider->setMaximum(999);
        timeSlider->setPageStep(10);
        timeSlider->setOrientation(Qt::Horizontal);
        btnSetVolume = new QPushButton(centralWidget);
        btnSetVolume->setObjectName(QString::fromUtf8("btnSetVolume"));
        btnSetVolume->setGeometry(QRect(600, 455, 30, 30));
        btnCutImage = new QPushButton(centralWidget);
        btnCutImage->setObjectName(QString::fromUtf8("btnCutImage"));
        btnCutImage->setGeometry(QRect(550, 455, 30, 30));
        FFVideoPlayerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FFVideoPlayerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu_Set = new QMenu(menuBar);
        menu_Set->setObjectName(QString::fromUtf8("menu_Set"));
        FFVideoPlayerClass->setMenuBar(menuBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Set->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_OpenLocalFiles);
        menu_File->addAction(action_OpenNetStream);
        menu_File->addAction(action_OpenCamera);
        menu_Help->addAction(action_About);
        menu_Help->addAction(action_GetSourceCode);

        retranslateUi(FFVideoPlayerClass);

        QMetaObject::connectSlotsByName(FFVideoPlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *FFVideoPlayerClass)
    {
        FFVideoPlayerClass->setWindowTitle(QApplication::translate("FFVideoPlayerClass", "FFVideoPlayer", nullptr));
        action_OpenLocalFiles->setText(QApplication::translate("FFVideoPlayerClass", "\346\211\223\345\274\200\346\234\254\345\234\260\350\247\206\351\242\221", nullptr));
        action_OpenNetStream->setText(QApplication::translate("FFVideoPlayerClass", "\346\211\223\345\274\200\347\275\221\347\273\234\346\265\201", nullptr));
        action_OpenCamera->setText(QApplication::translate("FFVideoPlayerClass", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        action_About->setText(QApplication::translate("FFVideoPlayerClass", "\345\205\263\344\272\216\346\234\254\350\275\257\344\273\266", nullptr));
        action_GetSourceCode->setText(QApplication::translate("FFVideoPlayerClass", "\350\216\267\345\217\226\346\272\220\344\273\243\347\240\201", nullptr));
        label_Playtime->setText(QString());
        btnPlayVideo->setText(QString());
        btnFullScreen->setText(QString());
        btnSetVolume->setText(QString());
        btnCutImage->setText(QString());
        menu_File->setTitle(QApplication::translate("FFVideoPlayerClass", "\346\226\207\344\273\266", nullptr));
        menu_Help->setTitle(QApplication::translate("FFVideoPlayerClass", "\345\270\256\345\212\251", nullptr));
        menu_Set->setTitle(QApplication::translate("FFVideoPlayerClass", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FFVideoPlayerClass: public Ui_FFVideoPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FFVIDEOPLAYER_H
