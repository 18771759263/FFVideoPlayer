/********************************************************************************
** Form generated from reading UI file 'StreamInfoDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STREAMINFODLG_H
#define UI_STREAMINFODLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_StreamInfoDlg
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_VideoName;
    QLabel *label_wh;
    QLabel *label_FrameRate;
    QLabel *label_VEncodeFormat;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_sampleRate;
    QLabel *label_sampleSize;
    QLabel *label_AEncodeFormat;

    void setupUi(QDialog *StreamInfoDlg)
    {
        if (StreamInfoDlg->objectName().isEmpty())
            StreamInfoDlg->setObjectName(QString::fromUtf8("StreamInfoDlg"));
        StreamInfoDlg->resize(435, 283);
        groupBox = new QGroupBox(StreamInfoDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 411, 121));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 26, 54, 12));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 50, 54, 12));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 74, 54, 12));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 98, 54, 12));
        label_VideoName = new QLabel(groupBox);
        label_VideoName->setObjectName(QString::fromUtf8("label_VideoName"));
        label_VideoName->setGeometry(QRect(80, 26, 250, 12));
        label_wh = new QLabel(groupBox);
        label_wh->setObjectName(QString::fromUtf8("label_wh"));
        label_wh->setGeometry(QRect(80, 50, 250, 12));
        label_FrameRate = new QLabel(groupBox);
        label_FrameRate->setObjectName(QString::fromUtf8("label_FrameRate"));
        label_FrameRate->setGeometry(QRect(80, 74, 250, 12));
        label_VEncodeFormat = new QLabel(groupBox);
        label_VEncodeFormat->setObjectName(QString::fromUtf8("label_VEncodeFormat"));
        label_VEncodeFormat->setGeometry(QRect(80, 98, 250, 12));
        groupBox_2 = new QGroupBox(StreamInfoDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 160, 411, 111));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 30, 54, 12));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 54, 54, 12));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 78, 54, 12));
        label_sampleRate = new QLabel(groupBox_2);
        label_sampleRate->setObjectName(QString::fromUtf8("label_sampleRate"));
        label_sampleRate->setGeometry(QRect(90, 30, 250, 12));
        label_sampleSize = new QLabel(groupBox_2);
        label_sampleSize->setObjectName(QString::fromUtf8("label_sampleSize"));
        label_sampleSize->setGeometry(QRect(90, 54, 250, 12));
        label_AEncodeFormat = new QLabel(groupBox_2);
        label_AEncodeFormat->setObjectName(QString::fromUtf8("label_AEncodeFormat"));
        label_AEncodeFormat->setGeometry(QRect(90, 78, 250, 12));

        retranslateUi(StreamInfoDlg);

        QMetaObject::connectSlotsByName(StreamInfoDlg);
    } // setupUi

    void retranslateUi(QDialog *StreamInfoDlg)
    {
        StreamInfoDlg->setWindowTitle(QApplication::translate("StreamInfoDlg", "\346\265\201\344\277\241\346\201\257", nullptr));
        groupBox->setTitle(QApplication::translate("StreamInfoDlg", "\350\247\206\351\242\221\346\265\201", nullptr));
        label->setText(QApplication::translate("StreamInfoDlg", "\350\247\206\351\242\221\345\220\215\347\247\260\357\274\232", nullptr));
        label_2->setText(QApplication::translate("StreamInfoDlg", "\345\256\275    \351\253\230\357\274\232", nullptr));
        label_3->setText(QApplication::translate("StreamInfoDlg", "\345\270\247    \347\216\207\357\274\232", nullptr));
        label_4->setText(QApplication::translate("StreamInfoDlg", "\347\274\226\347\240\201\346\226\271\345\274\217\357\274\232", nullptr));
        label_VideoName->setText(QApplication::translate("StreamInfoDlg", "TextLabel", nullptr));
        label_wh->setText(QApplication::translate("StreamInfoDlg", "TextLabel", nullptr));
        label_FrameRate->setText(QApplication::translate("StreamInfoDlg", "TextLabel", nullptr));
        label_VEncodeFormat->setText(QApplication::translate("StreamInfoDlg", "TextLabel", nullptr));
        groupBox_2->setTitle(QApplication::translate("StreamInfoDlg", "\351\237\263\351\242\221\346\265\201", nullptr));
        label_5->setText(QApplication::translate("StreamInfoDlg", "\351\207\207\346\240\267\351\242\221\347\216\207\357\274\232", nullptr));
        label_6->setText(QApplication::translate("StreamInfoDlg", "\351\207\207\346\240\267\345\244\247\345\260\217\357\274\232", nullptr));
        label_7->setText(QApplication::translate("StreamInfoDlg", "\347\274\226\347\240\201\346\226\271\345\274\217\357\274\232", nullptr));
        label_sampleRate->setText(QApplication::translate("StreamInfoDlg", "TextLabel", nullptr));
        label_sampleSize->setText(QApplication::translate("StreamInfoDlg", "TextLabel", nullptr));
        label_AEncodeFormat->setText(QApplication::translate("StreamInfoDlg", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StreamInfoDlg: public Ui_StreamInfoDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STREAMINFODLG_H
