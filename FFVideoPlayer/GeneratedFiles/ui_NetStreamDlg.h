/********************************************************************************
** Form generated from reading UI file 'NetStreamDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETSTREAMDLG_H
#define UI_NETSTREAMDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NetStreamDlg
{
public:
    QLabel *label;
    QLineEdit *lineEdit_IP;

    void setupUi(QDialog *NetStreamDlg)
    {
        if (NetStreamDlg->objectName().isEmpty())
            NetStreamDlg->setObjectName(QString::fromUtf8("NetStreamDlg"));
        NetStreamDlg->resize(495, 124);
        NetStreamDlg->setStyleSheet(QString::fromUtf8("QDialog\n"
"{\n"
"    background:rgb(53,53,53);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	color:white;\n"
"    font:13px;\n"
"}"));
        label = new QLabel(NetStreamDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(42, 53, 41, 16));
        lineEdit_IP = new QLineEdit(NetStreamDlg);
        lineEdit_IP->setObjectName(QString::fromUtf8("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(90, 50, 371, 20));

        retranslateUi(NetStreamDlg);

        QMetaObject::connectSlotsByName(NetStreamDlg);
    } // setupUi

    void retranslateUi(QDialog *NetStreamDlg)
    {
        NetStreamDlg->setWindowTitle(QApplication::translate("NetStreamDlg", "\350\256\276\347\275\256\347\275\221\347\273\234\346\265\201", nullptr));
        label->setText(QApplication::translate("NetStreamDlg", "\346\265\201\345\234\260\345\235\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NetStreamDlg: public Ui_NetStreamDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETSTREAMDLG_H
