#include "Makeup.h"
#include <Kinect.h>
#include <qtimer.h>
#include<iostream>
#include<time.h>

/******************************************************/
//global variable
const	double	OK_LEVEL = 0.15;	//judge the hand
const	int	HAND_UP = 150;		//the fingertip pos
const	int	HAND_LEFT_RIGHT = 100;	
const	int	OK_MOUSE = 2;		//threshold value of mouse movement
const   double PIX_RATE = 0.5;

const   int HEAD_PIX = 120;//calculate the pos of hat
const   int HAT_PIX = 150;//the size of the hat
const   int EAR_PIX = 60;//the pos of ear
const   int EARDROP_PIX = 20;//the size of eardrop
const   int BRACELET_PIX = 50;//the sieze of wrist
const   int NECKLACE_PIX = 100;//the size of necklace
const   int NECK_PIX = 20;
/******************************************************/
//global function
bool	level_check(const CameraSpacePoint & hand, const CameraSpacePoint & temp)
{
	if (fabs(temp.Z - hand.Z) <= OK_LEVEL)
		return	true;
	return	false;
}

bool	distance_check(const CameraSpacePoint & hand, const CameraSpacePoint & temp)
{
	double	ans = sqrt(pow(hand.X - temp.X, 2) + pow(hand.Y - temp.Y, 2) + pow(hand.Z - temp.Z, 2));
	if (ans <= 0.2 && ans >= 0.06)
		return	true;
	return	false;
}

bool	depth_rage_check(int x, int y, int depthWidth, int depthHeight)
{
	if (x >= 0 && x < depthWidth && y >= 0 && y < depthHeight)
		return	true;
	return	false;
}

bool	check_new_point(DepthSpacePoint & front, DepthSpacePoint & now, int height, int width)
{
	if (now.X == width - 1 && now.Y == height - 1 && (front.X || front.Y))
		return	false;
	else	if (fabs(now.X - front.X) <= OK_MOUSE && fabs(now.Y - front.Y) <= OK_MOUSE)
		return	false;
	return	true;
}

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

Makeup::Makeup(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	/************************************************************************/
	//This part is for the mouse usage of the listWidget
	ui.listWidgetLeft->setDragEnabled(false);
	ui.listWidgetLeft->setAcceptDrops(false);
	ui.listWidgetLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.listWidgetLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.listWidgetLeft->setVerticalScrollMode(QListWidget::ScrollPerPixel);
	ui.listWidgetLeft->setFrameShape(QListWidget::NoFrame);
	ui.listWidgetLeft->setViewMode(QListView::IconMode);
	ui.listWidgetLeft->setIconSize(QSize(ui.listWidgetLeft->width(), ui.listWidgetLeft->width()));
	QScroller::grabGesture(ui.listWidgetLeft, QScroller::LeftMouseButtonGesture);
	/************************************************************************/
	//add things
	hat = new QLabel(this);
	hat->clear();
	hat->setScaledContents(true);
	hat->setGeometry(-200, -200, 50, 50);
	earDropLeft = new QLabel(this);
	earDropRight = new QLabel(this);
	earDropLeft->clear();
	earDropLeft->setScaledContents(true);
	earDropRight->clear();
	earDropRight->setScaledContents(true);
	earDropLeft->setGeometry(-200, -200, 50, 50);
	earDropRight->setGeometry(-200, -200, 50, 50);
	bracelet = new QLabel(this);
	bracelet->clear();
	bracelet->setScaledContents(true);
	bracelet->setGeometry(-200, -200, 50, 50);
	necklace = new QLabel(this);
	necklace->clear();
	necklace->setScaledContents(true);
	necklace->setGeometry(-200, -200, 50, 50);
	/************************************************************************/

	m_pKinectSensor = NULL;
	m_pColorFrameReader = NULL;
	m_pDepthReader = NULL;//depth reader
	m_pBodyIndexReader = NULL;//body index reader
	m_pBodyReader = NULL;//body reader
	m_pMapper = NULL;//mapper
	pDepthFrame = NULL;
	pBodyIndexFrame = NULL;
	pBodyFrame = NULL;
	m_pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];// create heap storage for color pixel data in RGBX format
	connect(ui.listWidgetLeft, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(widgetList(QListWidgetItem *)));
	connect(ui.bhat, SIGNAL(clicked()), SLOT(hatList()));
	connect(ui.beardrop, SIGNAL(clicked()), SLOT(eardropList()));
	connect(ui.bnecklace, SIGNAL(clicked()), SLOT(necklaceList()));
	connect(ui.bbracelet, SIGNAL(clicked()), SLOT(braceletList()));
	connect(ui.bback, SIGNAL(clicked()), SLOT(back()));
	connect(ui.bexit, SIGNAL(clicked()), SLOT(exitM()));
	init();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateKinectData()));
	timer->start(33);
	/*************************************************************/
	//For mouse control
}

void Makeup::paintEvent(QPaintEvent * event)
{
	int w = width();
	int h = height();
	int width = w / 7;
	int height = h / 6;
	ui.bhat->setGeometry(w - width, 0, width, height);
	ui.beardrop->setGeometry(w - width, height, width, height);
	ui.bnecklace->setGeometry(w - width, height*2, width, height);
	ui.bbracelet->setGeometry(w - width, height*3, width, height);
	ui.bback->setGeometry(w - width, height * 4, width, height);
	ui.bexit->setGeometry(w - width, height * 5, width, height);
	ui.listWidgetLeft->setGeometry(0, 0, width, h);
	ui.listWidgetLeft->setIconSize(QSize(width, width));
	ui.label->resize(this->size());
}


Makeup::~Makeup()
{
	if (m_pColorRGBX)
	{
		delete[] m_pColorRGBX;
		m_pColorRGBX = NULL;
	}

	SafeRelease(m_pColorFrameReader);// done with color frame reader
	SafeRelease(m_pDepthReader);
	SafeRelease(m_pBodyIndexReader);
	SafeRelease(m_pBodyReader);
	SafeRelease(m_pMapper);

	if (m_pKinectSensor)
	{
		m_pKinectSensor->Close();// close the Kinect Sensor
	}
	SafeRelease(m_pKinectSensor);
}


void Makeup::updateKinectData()
{
	int windowPosX = this->geometry().x();
	int windowPosY = this->geometry().y();
	if (!m_pColorFrameReader)
	{
		return;
	}

	IColorFrame* pColorFrame = NULL;//color frame
	IDepthFrame* pDepthFrame = NULL;//depth frame
	IBodyIndexFrame* pBodyIndexFrame = NULL;//body index frame
	IBodyFrame* pBodyFrame = NULL;//body frame
	
	HRESULT hr = m_pColorFrameReader->AcquireLatestFrame(&pColorFrame);

	if (SUCCEEDED(hr))
	{
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		ColorImageFormat imageFormat = ColorImageFormat_None;
		UINT nBufferSize = 0;
		RGBQUAD *pBuffer = NULL;

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_FrameDescription(&pFrameDescription);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_RawColorImageFormat(&imageFormat);
		}

		if (SUCCEEDED(hr))
		{
			if (imageFormat == ColorImageFormat_Bgra)
			{
				hr = pColorFrame->AccessRawUnderlyingBuffer(&nBufferSize, reinterpret_cast<BYTE**>(&pBuffer));
			}
			else if (m_pColorRGBX)
			{
				pBuffer = m_pColorRGBX;
				nBufferSize = cColorWidth * cColorHeight * sizeof(RGBQUAD);
				hr = pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, reinterpret_cast<BYTE*>(pBuffer), ColorImageFormat_Bgra);
			}
			else
			{
				hr = E_FAIL;
			}
		}

		if (SUCCEEDED(hr))
		{
			ui.label->setScaledContents(true);
			ui.label->setWindowFlag(Qt::WindowStaysOnBottomHint);
			ui.label->setPixmap(QPixmap::fromImage(QImage((uchar*)pBuffer, nWidth, nHeight, QImage::Format_RGB32)).scaled(ui.label->size(), Qt::KeepAspectRatio));
			//ProcessColor(pBuffer, nWidth, nHeight);
		}

		SafeRelease(pFrameDescription);
	}

	int wait_time = 1000;
	while (m_pDepthReader->AcquireLatestFrame(&pDepthFrame) != S_OK);//读取Depth数据
	UINT	depthBufferSize = 0;
	UINT16	* depthBuffer = nullptr;
	pDepthFrame->AccessUnderlyingBuffer(&depthBufferSize, &depthBuffer);


	while (m_pBodyIndexReader->AcquireLatestFrame(&pBodyIndexFrame) != S_OK);	//读取BodyIndex数据
	UINT	bodyIndexBufferSize = 0;
	BYTE	* bodyIndexBuffer = nullptr;
	pBodyIndexFrame->AccessUnderlyingBuffer(&bodyIndexBufferSize, &bodyIndexBuffer);

	while (m_pBodyReader->AcquireLatestFrame(&pBodyFrame) != S_OK);			//读取Body数据
	int	bodyBufferSize = 0;
	pBodySource->get_BodyCount(&bodyBufferSize);
	IBody	** bodyArray = new IBody *[bodyBufferSize];
	for (int i = 0; i < bodyBufferSize; i++)
	{
		bodyArray[i] = nullptr;
		SafeRelease(bodyArray[i]);
	}
	pBodyFrame->GetAndRefreshBodyData(bodyBufferSize, bodyArray);


	for (int i = 0; i < bodyBufferSize; i++)					//遍历6个人
	{
		BOOLEAN	result = false;
		if (bodyArray[i]->get_IsTracked(&result) == S_OK && result)
		{
			Joint jointArray[JointType_Count];				//将关节点输出，正式开始处理
			bodyArray[i]->GetJoints(JointType_Count, jointArray);
			if (jointArray[JointType_Neck].TrackingState != TrackingState_Tracked || jointArray[JointType_Head].TrackingState != TrackingState_Tracked)
				continue;
			bool leftHand = false;						//用来判断最高的手指是左手还是右手
			//开始检测右手
			DepthSpacePoint	highestPoint = { depthWidth - 1,depthHeight - 1 };
			if (jointArray[JointType_HandRight].TrackingState == TrackingState_Tracked)
			{
				CameraSpacePoint cameraHandRight = jointArray[JointType_HandRight].Position;
				DepthSpacePoint	depthHandRight;
				m_pMapper->MapCameraPointToDepthSpace(cameraHandRight, &depthHandRight);
				for (int i = depthHandRight.Y; i > depthHandRight.Y - HAND_UP; i--)
					for (int j = depthHandRight.X - HAND_LEFT_RIGHT; j < depthHandRight.X + HAND_LEFT_RIGHT; j++)	//确定要检查的范围
					{
						if (!depth_rage_check(j, i, depthWidth, depthHeight))					//判断坐标是否合法
							continue;
						int	index = i * depthWidth + j;
						CameraSpacePoint	cameraTemp;
						DepthSpacePoint		depthTemp = { j,i };
						m_pMapper->MapDepthPointToCameraSpace(depthTemp, depthBuffer[index], &cameraTemp);

						if (bodyIndexBuffer[index] > 5 || (bodyIndexBuffer[index] <= 5 && !level_check(cameraHandRight, cameraTemp)))	//看此像素是否不属于人体(指尖上方一点)，或者属于人体但是和手不在同一平面(手在胸前）
						{
							bool	flag = true;
							for (int k = 1; k <= 5; k++)	//看时候此点下面连续5个像素都属于人体，且和手腕在同一平面,且距离合适
							{
								int	index_check = (i + k) * depthWidth + j;
								depthTemp.X = j;
								depthTemp.Y = i + k;
								m_pMapper->MapDepthPointToCameraSpace(depthTemp, depthBuffer[index_check], &cameraTemp);
								if (bodyIndexBuffer[index_check] <= 5 && level_check(cameraHandRight, cameraTemp) && distance_check(cameraHandRight, cameraTemp))
									continue;
								else
								{
									flag = false;
									break;
								}
							}
							if (flag && i < highestPoint.Y)
							{
								highestPoint.X = j;
								highestPoint.Y = i;
								leftHand = false;		//记录为右手
							}
						}
					}
			}

			//开始检测左手,方法与检测右手手指是一样的
			if (jointArray[JointType_HandLeft].TrackingState == TrackingState_Tracked)
			{
				CameraSpacePoint	cameraHandLeft = jointArray[JointType_HandLeft].Position;
				DepthSpacePoint		depthHandLeft;
				m_pMapper->MapCameraPointToDepthSpace(cameraHandLeft, &depthHandLeft);

				for (int i = depthHandLeft.Y; i > depthHandLeft.Y - HAND_UP; i--)
					for (int j = depthHandLeft.X - HAND_LEFT_RIGHT; j < depthHandLeft.X + HAND_LEFT_RIGHT; j++)
					{
						if (!depth_rage_check(j, i, depthWidth, depthHeight))
							continue;
						int	index = i * depthWidth + j;
						CameraSpacePoint	cameraTemp;
						DepthSpacePoint		depthTemp = { j,i };
						m_pMapper->MapDepthPointToCameraSpace(depthTemp, depthBuffer[index], &cameraTemp);

						if (bodyIndexBuffer[index] > 5 || (bodyIndexBuffer[index] <= 5 && !level_check(cameraHandLeft, cameraTemp)))
						{
							bool	flag = true;
							for (int k = 1; k <= 5; k++)
							{
								int	index_check = (i + k) * depthWidth + j;
								depthTemp.X = j;
								depthTemp.Y = i + k;
								m_pMapper->MapDepthPointToCameraSpace(depthTemp, depthBuffer[index_check], &cameraTemp);
								if (bodyIndexBuffer[index_check] <= 5 && level_check(cameraHandLeft, cameraTemp) && distance_check(cameraHandLeft, cameraTemp))
									continue;
								else
								{
									flag = false;
									break;
								}
							}
							if (flag && i < highestPoint.Y)
							{
								highestPoint.X = j;
								highestPoint.Y = i;
								leftHand = true;	//记录为左手
							}
						}
					}
			}


			//开始检测头部
			if (jointArray[JointType_Head].TrackingState == TrackingState_Tracked)
			{
				CameraSpacePoint cameraHead = jointArray[JointType_Head].Position;
				if (hatFlag != -1) {
					int width,height;
					QPoint hatPos = HeadToHat(cameraHead, &width,&height);
					hat->setGeometry(hatPos.x(), hatPos.y(), width, height); 
				}
				if (earFlag != -1)
				{
					DepthSpacePoint depthPoint;
					m_pMapper->MapCameraPointToDepthSpace(cameraHead, &depthPoint);
					int width, height;
					int bias = HeadToEar(cameraHead, &width, &height);
					int screenPointX = static_cast<int>((depthPoint.X * this->geometry().width()) / cDepthWidth);
					int screenPointY = static_cast<int>((depthPoint.Y * this->geometry().height()) / cDepthHeight);
					earDropLeft->setGeometry(screenPointX - bias*2/5, screenPointY+10, width, height);
					earDropRight->setGeometry(screenPointX + bias*6/5, screenPointY+10, width, height);
				}
			}
			//开始检测右手腕
			if (jointArray[JointType_WristRight].TrackingState == TrackingState_Tracked)
			{
				if (braceletFlag != -1) {
					CameraSpacePoint cameraWristRight = jointArray[JointType_WristRight].Position;
					int width;
					int height;
					WristSize(cameraWristRight, &width, &height);
					DepthSpacePoint depthPoint;
					m_pMapper->MapCameraPointToDepthSpace(cameraWristRight, &depthPoint);
					int screenPointX = static_cast<int>((depthPoint.X * this->geometry().width()) / cDepthWidth - width);
					int screenPointY = static_cast<int>((depthPoint.Y * this->geometry().height()) / cDepthHeight-height/3);
					bracelet->setGeometry(screenPointX + width/4, screenPointY, width, height);
				}
			}
			//检测两肩与脊柱相交点
			if (jointArray[JointType_SpineShoulder].TrackingState == TrackingState_Tracked)
			{
				if (neckFlag != -1) 
				{
					CameraSpacePoint cameraSpineShoulder = jointArray[JointType_SpineShoulder].Position;
					int width;
					int height;
					QPoint pos = NecklaceSize(cameraSpineShoulder, &width, &height);
					necklace->setGeometry(pos.x()-width/7, pos.y()+ width / 4, width, height);
				}
			}
			//以下为确定操作窗口的左上角和右下角。以Head关节到Neck关节的距离作为单位长度.最后用的深度数据，所以要转换
			CameraSpacePoint	cameraNeck = jointArray[JointType_Neck].Position;
			CameraSpacePoint	cameraHead = jointArray[JointType_Head].Position;
			double	unite = sqrt(pow(cameraNeck.X - cameraHead.X, 2) + pow(cameraNeck.Y - cameraHead.Y, 2) + pow(cameraNeck.Z - cameraHead.Z, 2));

			if (!leftHand)	//确定右手的操作窗口
			{
				CameraSpacePoint	cameraUpLeft = { cameraNeck.X + unite * 0.5,cameraNeck.Y + unite * 3,cameraNeck.Z };
				CameraSpacePoint	cameraDownRight = { cameraNeck.X + unite * 4,cameraNeck.Y + unite,cameraNeck.Z };
				m_pMapper->MapCameraPointToDepthSpace(cameraUpLeft, &depthUpLeft);
				m_pMapper->MapCameraPointToDepthSpace(cameraDownRight, &depthDownRight);
			}
			else		//确定左手的操作窗口
			{
				CameraSpacePoint	cameraUpLeft = { cameraNeck.X - unite * 4,cameraNeck.Y + unite * 3,cameraNeck.Z };
				CameraSpacePoint	cameraDownRight = { cameraNeck.X - unite * 0.5,cameraNeck.Y + unite,cameraNeck.Z };
				m_pMapper->MapCameraPointToDepthSpace(cameraUpLeft, &depthUpLeft);
				m_pMapper->MapCameraPointToDepthSpace(cameraDownRight, &depthDownRight);
			}

			int	windowWidth = (int)depthDownRight.X - (int)depthUpLeft.X;	//计算操作窗口的尺寸
			int	windowHeight = (int)depthDownRight.Y - (int)depthUpLeft.Y;

			bool	control = true;
			HandState handstateRight;
			bodyArray[i]->get_HandRightState(&handstateRight);
			HandState handstateLeft;
			bodyArray[i]->get_HandLeftState(&handstateLeft);
			if (check_new_point(front, highestPoint, depthHeight, depthWidth))	//让鼠标碰到边缘就停止，不反弹
			{
				if (highestPoint.X < depthUpLeft.X)
					control = false;
				if (highestPoint.X > depthDownRight.X)
					control = false;
				if (highestPoint.Y > depthDownRight.Y)
					control = false;
				if (highestPoint.Y < depthUpLeft.Y)
					control = false;
				int	mouseX = fabs(highestPoint.X - depthUpLeft.X);
				int	mouseY = fabs(highestPoint.Y - depthUpLeft.Y);
				if (control)
				{
					if (leftHand)
					{
						if (handstateLeft != HandState_Closed)
						{
							mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 65535 * mouseX / windowWidth, 65535 * mouseY / windowHeight, 0, 0);	//计算公式：小窗口的点/小窗口尺寸 = 大窗口的点/大
							front = highestPoint;
						}
					}
					else
					{

						if (handstateRight != HandState_Closed)
						{
							mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 65535 * mouseX / windowWidth, 65535 * mouseY / windowHeight, 0, 0);	//计算公式：小窗口的点/小窗口尺寸 = 大窗口的点/大
							front = highestPoint;
						}
					}
				}
			}
			else									//抖动消除，如果和上一帧相比移动的幅度小于阈值，则保持上一帧的状态
			{
				int	mouseX = fabs(front.X - depthUpLeft.X);
				int	mouseY = fabs(front.Y - depthUpLeft.Y);
				if (leftHand)
				{
					
					if (handstateRight == HandState_Open)
					{
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					}
					else
					{
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
					if (handstateLeft != HandState_Closed)
					{
						mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 65535 * mouseX / windowWidth, 65535 * mouseY / windowHeight, 0, 0);
					}
				}
				else
				{
					if (handstateLeft == HandState_Open)
					{
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					}
					else
					{
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
					if (handstateRight != HandState_Closed)
					{
						mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 65535 * mouseX / windowWidth, 65535 * mouseY / windowHeight, 0, 0);
					}
				}
			}
		}
	}

	SafeRelease(pColorFrame);
	SafeRelease(pDepthFrame);
	SafeRelease(pBodyIndexFrame);
	SafeRelease(pBodyFrame);
	delete[] bodyArray;
}

void Makeup::init()
{
	HRESULT hr;

	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	BOOLEAN ready;
	qDebug() << ready;
	if (FAILED(hr))
	{
		QMessageBox::warning(NULL, "Wrong", "Fail to open Kinect!", QMessageBox::Yes);
		QApplication* app;
		app->exit(0);
		return;
	}
	if (m_pKinectSensor)
	{
		// Initialize the Kinect and get the color reader
		IColorFrameSource* pColorFrameSource = NULL;
		IFrameDescription* pDescription = NULL;
		IDepthFrameSource* pDepthSource = NULL;
		IBodyIndexFrameSource* pBodyIndexSource = NULL;
		hr = m_pKinectSensor->Open();
		//open color reader
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
		}
		if (SUCCEEDED(hr))
		{
			hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
		}
		//open detpth reader
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_DepthFrameSource(&pDepthSource);
			
		}
		if (SUCCEEDED(hr))
		{
			hr = pDepthSource->get_FrameDescription(&pDescription);
			pDescription->get_Height(&depthHeight);
			pDescription->get_Width(&depthWidth);
		}
		if (SUCCEEDED(hr))
		{
			hr = pDepthSource->OpenReader(&m_pDepthReader); ;
		}
		//open BodyIndex reader
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_BodyIndexFrameSource(&pBodyIndexSource);
		}
		if (SUCCEEDED(hr))
		{
			hr = pBodyIndexSource->OpenReader(&m_pBodyIndexReader);
		}
		//open Body reader
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_BodyFrameSource(&pBodySource);
		}
		if (SUCCEEDED(hr))
		{
			hr = pBodySource->OpenReader(&m_pBodyReader);;
		}
		//open Mapper
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_CoordinateMapper(&m_pMapper);;
		}

		SafeRelease(pColorFrameSource);
		SafeRelease(pDepthSource);
		SafeRelease(pBodyIndexSource);
		SafeRelease(pDescription);
		return;
	}
	QMessageBox::warning(NULL, "Wrong", "No kinect connected!", QMessageBox::Yes);
	QApplication* app;
	app->exit(0);
}

QPoint Makeup::BodyToScreen(const CameraSpacePoint& bodyPoint, int width, int height)
{
	DepthSpacePoint depthPoint = { 0 };
	m_pMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);

	int screenPointX = static_cast<int>(depthPoint.X * width) / cDepthWidth;
	int screenPointY = static_cast<int>(depthPoint.Y * height) / cDepthHeight;

	return QPoint(screenPointX, screenPointY);
}

QPoint Makeup::HeadToHat(const CameraSpacePoint& bodyPoint, int* width, int* height)
{
	DepthSpacePoint depthPoint = { 0 };
	m_pMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);
	float wrate = float(this->geometry().width()) / cDepthWidth;
	float hrate = float(this->geometry().height()) / cDepthHeight;
	int bias = static_cast<int>(HEAD_PIX * PIX_RATE * hrate / bodyPoint.Z);
	int w = static_cast<int>(HAT_PIX * PIX_RATE*wrate* 6 / (5*bodyPoint.Z));
	int h = w * hatRate;
	int screenPointX = static_cast<int>((depthPoint.X * this->geometry().width()) / cDepthWidth- w/4);
	int screenPointY = static_cast<int>((depthPoint.Y * this->geometry().height()) / cDepthHeight - h/3);
	*width = w;
	*height = h;
	return QPoint(screenPointX, screenPointY-bias);
}

int Makeup::HeadToEar(const CameraSpacePoint& bodyPoint, int* width, int* height)
{
	float wrate = float(this->geometry().width()) / cDepthWidth;
	int bias = static_cast<int>(EAR_PIX * PIX_RATE *wrate / bodyPoint.Z);
	int w = static_cast<int>(EARDROP_PIX * PIX_RATE*wrate / bodyPoint.Z);
	int h = w * earRate;
	*width = w;
	*height = h;
	return bias;
}

void Makeup::WristSize(const CameraSpacePoint& bodyPoint, int* width, int* height)
{
	float rate = float(this->geometry().width()) / cDepthWidth;
	int w = static_cast<int>(BRACELET_PIX * PIX_RATE*rate / bodyPoint.Z);
	*width = w;
	*height = w*wristRate;
}

QPoint Makeup::NecklaceSize(const CameraSpacePoint& bodyPoint, int* width, int* height)
{
	DepthSpacePoint depthPoint = { 0 };
	m_pMapper->MapCameraPointToDepthSpace(bodyPoint, &depthPoint);
	float wrate = float(this->geometry().width()) / cDepthWidth;
	float hrate = float(this->geometry().height()) / cDepthHeight;
	int bias = hrate * NECK_PIX;
	int w = static_cast<int>(NECKLACE_PIX * PIX_RATE*wrate / bodyPoint.Z);
	int h = w * neckRate;
	int screenPointX = static_cast<int>((depthPoint.X * this->geometry().width()) / cDepthWidth);
	int screenPointY = static_cast<int>((depthPoint.Y * this->geometry().height()) / cDepthHeight);
	*width = w;
	*height = h;
	return QPoint(screenPointX, screenPointY-bias);
}
//SLOTS

void Makeup::widgetList(QListWidgetItem * item)
{
	std::string name;
	if (mode == 0) 
	{
		hatFlag = ui.listWidgetLeft->currentIndex().row();
		name = ":/Makeup/Resources/hat/hat_" + std::to_string(hatFlag) + "_.png";
		QPixmap P(name.c_str());
		hatRate = float(P.size().height()) / float(P.size().width());
		hat->setPixmap(QPixmap(name.c_str()));
	}
	else if (mode == 1)
	{
		earFlag = ui.listWidgetLeft->currentIndex().row();
		name = ":/Makeup/Resources/eardrop/eardrop_" + std::to_string(earFlag) + "_.png";
		QPixmap P(name.c_str());
		earRate = float(P.size().height()) / float(P.size().width());
		earDropRight->setPixmap(QPixmap(name.c_str()));
		earDropLeft->setPixmap(QPixmap(name.c_str()));
	}
	else if (mode == 2)
	{
		neckFlag = ui.listWidgetLeft->currentIndex().row();
		name = ":/Makeup/Resources/necklace/necklace_" + std::to_string(neckFlag) + "_.png";
		QPixmap P(name.c_str());
		neckRate = float(P.size().height()) / float(P.size().width());
		necklace->setPixmap(QPixmap(name.c_str()));
	}
	else if (mode == 3)
	{
		braceletFlag = ui.listWidgetLeft->currentIndex().row();
		name = ":/Makeup/Resources/bracelet/bracelet_" + std::to_string(braceletFlag) + "_.png";
		QPixmap P(name.c_str());
		wristRate = float(P.size().height()) / float(P.size().width());
		bracelet->setPixmap(QPixmap(name.c_str()));
	}
}

void Makeup::recieveMode(int mode,int number)
{
	this->mode = mode;
	this->show();
	std::string dir= "./Resources/";
	std::string name;
	switch (mode)
	{
	case 0:
		name = ":/Makeup/Resources/hat/hat_" + std::to_string(number) + "_.png";
		hat->setPixmap(QPixmap(name.c_str()));
		hatFlag = number;
		dir += "hat/";
		break;
	case 1:
		earFlag = number;
		name = ":/Makeup/Resources/eardrop/eardrop_" + std::to_string(number) + "_.png";
		dir += "eardrop/";
		break;
	case 2:
		neckFlag = number;
		name = ":/Makeup/Resources/necklace/necklace_" + std::to_string(number) + "_.png";
		dir += "necklace/";
		break;
	case 3:
		braceletFlag = number;
		name = ":/Makeup/Resources/bracelet/bracelet_" + std::to_string(number) + "_.png";
		dir += "bracelet/";
		break;
	}
	//add pictures
	paintList(dir);
}

void Makeup::hatList()
{
	mode = 0;
	std::string dir = "./Resources/hat/";
	paintList(dir);
}
void Makeup::eardropList()
{
	mode = 1;
	std::string dir = "./Resources/eardrop/";
	paintList(dir);
}
void Makeup::necklaceList()
{
	mode = 2;
	std::string dir = "./Resources/necklace/";
	paintList(dir);
}
void Makeup::braceletList()
{
	mode = 3;
	std::string dir = "./Resources/bracelet/";
	paintList(dir);
}

void Makeup::back()
{
	this->hide();
	emit backToMain();
}
void Makeup::exitM()
{
	this->close();
	emit quit();
}
void Makeup::exit()
{
	this->close();
}
//For repaint list
void Makeup::paintList(std::string dir)
{
	QDir * imagePath = new QDir(dir.c_str());
	QStringList filter;
	filter << "*_.png";
	QList<QFileInfo> *fileInfo = new QList<QFileInfo>(imagePath->entryInfoList(filter));
	int imageSum = fileInfo->count();
	QList<QString>  fileNames;
	fileNames.clear();
	if (imageSum == 0)
	{
		std::cout << "Error!There is no pictures";
	}
	for (int i = 0; i < imageSum; i++)
	{
		fileNames.append(fileInfo->at(i).filePath());
	}
	ui.listWidgetLeft->clear();
	for (auto tmp : fileNames)
	{
		ui.listWidgetLeft->addItem(new QListWidgetItem(QIcon(tmp), ""));
	}
}