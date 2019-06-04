#pragma once

#include <QtWidgets/QWidget>
#include "ui_Makeup.h"
#include <Kinect.h>
#include <qpixmap.h>

class Makeup : public QWidget
{
	Q_OBJECT

public:
	Makeup(QWidget *parent = Q_NULLPTR);
	~Makeup();
private slots:
	void updateKinectData();
private:
	Ui::MakeupClass ui;
	void paintEvent(QPaintEvent * event);
	static const int        cColorWidth = 1920;
	static const int        cColorHeight = 1080;
	IKinectSensor*          m_pKinectSensor;// Current Kinect
	IColorFrameReader*      m_pColorFrameReader;// Color reader
	RGBQUAD*                m_pColorRGBX;
	void init();
};
