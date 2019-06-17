#pragma once

#include <QtWidgets/QWidget>
#include "ui_Makeup.h"
#include <Kinect.h>
#include <qpixmap.h>
#include <qscroller.h>
#include <qdir.h>
#include <qmessagebox.h>
#include<qdebug.h>

class Makeup : public QWidget
{
	Q_OBJECT

public:
	static const int        cDepthWidth = 512;
	static const int        cDepthHeight = 424;
	Makeup(QWidget *parent = Q_NULLPTR);
	~Makeup();
private slots:
	void updateKinectData();
	void hatList();
	void eardropList();
	void necklaceList();
	void braceletList();
	void back();

public slots:
	void exitM();
	void widgetList(QListWidgetItem * item);
	void recieveMode(int mode,int number);//���ӣ�ֻ��һ��signal������emit����
	void exit();

signals:
	void backToMain();
	void quit();

private:
	Ui::MakeupClass ui;
	void paintEvent(QPaintEvent * event);
	QPoint BodyToScreen(const CameraSpacePoint& bodyPoint, int width, int height);
	QPoint HeadToHat(const CameraSpacePoint& bodyPoint, int* width,int* height);
	int HeadToEar(const CameraSpacePoint& bodyPoint, int* width,int* height);
	void WristSize(const CameraSpacePoint& bodyPoint, int* width, int* height);
	QPoint NecklaceSize(const CameraSpacePoint& bodyPoint, int* width, int* height);

	static const int        cColorWidth = 1920;
	static const int        cColorHeight = 1080;
	IKinectSensor*          m_pKinectSensor;// Current Kinect
	IColorFrameReader*      m_pColorFrameReader;// Color reader
	IDepthFrameReader*		m_pDepthReader;//depth reader
	IBodyIndexFrameReader*  m_pBodyIndexReader;//body index reader
	IBodyFrameReader*		m_pBodyReader;//body reader
	ICoordinateMapper*		m_pMapper;//mapper
	IDepthFrame*			pDepthFrame;
	IBodyIndexFrame*		pBodyIndexFrame;
	IBodyFrame*				pBodyFrame;
	IBodyFrameSource*		pBodySource = NULL;

	DepthSpacePoint		front = { 0,0 };//������¼��һ������λ��
	DepthSpacePoint		depthUpLeft = { 1,1 };//�������ڵ����ϽǺ����½ǣ�Ҫע��������X��X��Y��Y�Ĳ����Ϊ���������Բ��ܶ�Ϊ0
	DepthSpacePoint		depthDownRight = { 0,0 };

	int	depthHeight = 0, depthWidth = 0;
	RGBQUAD*                m_pColorRGBX;
	void init();

	//�������ֵ�ͼƬָ��
	QLabel* hat = NULL;
	int hatFlag = -1;
	double hatRate;
	QLabel* earDropLeft = NULL;
	QLabel* earDropRight = NULL;
	int earFlag = -1;
	double earRate;
	QLabel* bracelet = NULL;
	int braceletFlag = -1;
	double wristRate;
	QLabel* necklace = NULL;
	int neckFlag = -1;
	double neckRate;

	//���ܴ������ڴ�����ģʽֵ:1-hat,2-eardrop,3-necklace,4-bracelet,�ػ����б�
	int mode = 0;
	int number = 0;//���
	void paintList(std::string dir);
};
