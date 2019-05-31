#pragma once

#include <QtWidgets/QWidget>
#include "ui_Makeup.h"

class Makeup : public QWidget
{
	Q_OBJECT

public:
	Makeup(QWidget *parent = Q_NULLPTR);

private:
	Ui::MakeupClass ui;
};
