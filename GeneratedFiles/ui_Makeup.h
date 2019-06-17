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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MakeupClass
{
public:
    QLabel *label;
    QListWidget *listWidgetLeft;
    QPushButton *bhat;
    QPushButton *beardrop;
    QPushButton *bnecklace;
    QPushButton *bbracelet;
    QPushButton *bback;
    QPushButton *bexit;

    void setupUi(QWidget *MakeupClass)
    {
        if (MakeupClass->objectName().isEmpty())
            MakeupClass->setObjectName(QString::fromUtf8("MakeupClass"));
        MakeupClass->resize(746, 543);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(64);
        sizePolicy.setVerticalStretch(53);
        sizePolicy.setHeightForWidth(MakeupClass->sizePolicy().hasHeightForWidth());
        MakeupClass->setSizePolicy(sizePolicy);
        MakeupClass->setMinimumSize(QSize(742, 542));
        MakeupClass->setMouseTracking(true);
        MakeupClass->setTabletTracking(true);
        MakeupClass->setInputMethodHints(Qt::ImhNone);
        label = new QLabel(MakeupClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 737, 539));
        label->setMouseTracking(false);
        label->setContextMenuPolicy(Qt::DefaultContextMenu);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("background-color:transparent;"));
        listWidgetLeft = new QListWidget(MakeupClass);
        listWidgetLeft->setObjectName(QString::fromUtf8("listWidgetLeft"));
        listWidgetLeft->setGeometry(QRect(0, 0, 111, 541));
        listWidgetLeft->setContextMenuPolicy(Qt::DefaultContextMenu);
        listWidgetLeft->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));
        listWidgetLeft->setInputMethodHints(Qt::ImhNone);
        listWidgetLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidgetLeft->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidgetLeft->setProperty("showDropIndicator", QVariant(false));
        listWidgetLeft->setDragDropMode(QAbstractItemView::NoDragDrop);
        listWidgetLeft->setModelColumn(0);
        listWidgetLeft->setItemAlignment(Qt::AlignCenter);
        bhat = new QPushButton(MakeupClass);
        bhat->setObjectName(QString::fromUtf8("bhat"));
        bhat->setGeometry(QRect(650, 0, 91, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Black"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        bhat->setFont(font);
        bhat->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));
        beardrop = new QPushButton(MakeupClass);
        beardrop->setObjectName(QString::fromUtf8("beardrop"));
        beardrop->setGeometry(QRect(650, 70, 91, 71));
        beardrop->setFont(font);
        beardrop->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));
        bnecklace = new QPushButton(MakeupClass);
        bnecklace->setObjectName(QString::fromUtf8("bnecklace"));
        bnecklace->setGeometry(QRect(650, 140, 91, 71));
        bnecklace->setFont(font);
        bnecklace->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));
        bbracelet = new QPushButton(MakeupClass);
        bbracelet->setObjectName(QString::fromUtf8("bbracelet"));
        bbracelet->setGeometry(QRect(650, 210, 91, 71));
        bbracelet->setFont(font);
        bbracelet->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));
        bback = new QPushButton(MakeupClass);
        bback->setObjectName(QString::fromUtf8("bback"));
        bback->setGeometry(QRect(650, 280, 91, 71));
        bback->setFont(font);
        bback->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));
        bexit = new QPushButton(MakeupClass);
        bexit->setObjectName(QString::fromUtf8("bexit"));
        bexit->setGeometry(QRect(650, 350, 91, 71));
        bexit->setFont(font);
        bexit->setStyleSheet(QString::fromUtf8("background-color:rgba(255,255,255,50%);"));

        retranslateUi(MakeupClass);

        QMetaObject::connectSlotsByName(MakeupClass);
    } // setupUi

    void retranslateUi(QWidget *MakeupClass)
    {
        MakeupClass->setWindowTitle(QApplication::translate("MakeupClass", "Makeup", nullptr));
        label->setText(QString());
        bhat->setText(QApplication::translate("MakeupClass", "Hat", nullptr));
        beardrop->setText(QApplication::translate("MakeupClass", "Eardrop", nullptr));
        bnecklace->setText(QApplication::translate("MakeupClass", "Necklace", nullptr));
        bbracelet->setText(QApplication::translate("MakeupClass", "bracelet", nullptr));
        bback->setText(QApplication::translate("MakeupClass", "back", nullptr));
        bexit->setText(QApplication::translate("MakeupClass", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MakeupClass: public Ui_MakeupClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKEUP_H
