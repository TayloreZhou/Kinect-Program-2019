/********************************************************************************
** Form generated from reading UI file 'Makeup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKEUP_H
#define UI_MAKEUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeupClass
{
public:
    QLabel *label;
    QListWidget *listWidgetLeft;
    QListWidget *listWidgetRight;

    void setupUi(QWidget *MakeupClass)
    {
        if (MakeupClass->objectName().isEmpty())
            MakeupClass->setObjectName(QString::fromUtf8("MakeupClass"));
        MakeupClass->resize(746, 542);
        MakeupClass->setMinimumSize(QSize(742, 542));
        label = new QLabel(MakeupClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 737, 539));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        listWidgetLeft = new QListWidget(MakeupClass);
        listWidgetLeft->setObjectName(QString::fromUtf8("listWidgetLeft"));
        listWidgetLeft->setGeometry(QRect(0, 0, 111, 541));
        listWidgetLeft->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));
        listWidgetLeft->setInputMethodHints(Qt::ImhNone);
        listWidgetRight = new QListWidget(MakeupClass);
        listWidgetRight->setObjectName(QString::fromUtf8("listWidgetRight"));
        listWidgetRight->setGeometry(QRect(635, 0, 111, 541));
        listWidgetRight->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));

        retranslateUi(MakeupClass);

        QMetaObject::connectSlotsByName(MakeupClass);
    } // setupUi

    void retranslateUi(QWidget *MakeupClass)
    {
        MakeupClass->setWindowTitle(QApplication::translate("MakeupClass", "Makeup", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MakeupClass: public Ui_MakeupClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKEUP_H
