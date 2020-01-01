/********************************************************************************
** Form generated from reading UI file 'AboutDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDLG_H
#define UI_ABOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AboutDlg
{
public:
    QLabel *label;

    void setupUi(QDialog *AboutDlg)
    {
        if (AboutDlg->objectName().isEmpty())
            AboutDlg->setObjectName(QString::fromUtf8("AboutDlg"));
        AboutDlg->resize(389, 131);
        AboutDlg->setStyleSheet(QString::fromUtf8("QDialog\n"
"{\n"
"    background:rgb(53,53,53);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	color:white;\n"
"    font:13px;\n"
"}"));
        label = new QLabel(AboutDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 40, 181, 31));

        retranslateUi(AboutDlg);

        QMetaObject::connectSlotsByName(AboutDlg);
    } // setupUi

    void retranslateUi(QDialog *AboutDlg)
    {
        AboutDlg->setWindowTitle(QApplication::translate("AboutDlg", "About", nullptr));
        label->setText(QApplication::translate("AboutDlg", "\345\237\272\344\272\216FFmpeg\345\274\200\345\217\221\347\232\204\350\247\206\351\242\221\346\222\255\346\224\276\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDlg: public Ui_AboutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDLG_H
