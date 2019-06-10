#include "Makeup.h"
#include <Kinect.h>
#include <qtimer.h>
#include<iostream>

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
	ui.listWidgetLeft->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.listWidgetLeft->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.listWidgetLeft->setVerticalScrollMode(QListWidget::ScrollPerPixel);
	ui.listWidgetLeft->setFrameShape(QListWidget::NoFrame);
	ui.listWidgetLeft->setViewMode(QListView::IconMode);
	ui.listWidgetLeft->setIconSize(QSize(ui.listWidgetLeft->width(), ui.listWidgetLeft->width()));
	QScroller::grabGesture(ui.listWidgetLeft, QScroller::LeftMouseButtonGesture);
	ui.listWidgetRight->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.listWidgetRight->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.listWidgetRight->setVerticalScrollMode(QListWidget::ScrollPerPixel);
	ui.listWidgetRight->setFrameShape(QListWidget::NoFrame);
	ui.listWidgetRight->setViewMode(QListView::IconMode);
	ui.listWidgetRight->setIconSize(QSize(ui.listWidgetRight->width(), ui.listWidgetRight->width()));
	QScroller::grabGesture(ui.listWidgetRight, QScroller::LeftMouseButtonGesture);
	/************************************************************************/
	//add pictures
	QDir * imagePath = new QDir("./Resources/eardrop/");
	QStringList filter;
	filter << "*.png";
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
	for (auto tmp : fileNames)
	{
		ui.listWidgetLeft->addItem(new QListWidgetItem(QIcon(tmp), ""));
	}

	m_pKinectSensor = NULL;
	m_pColorFrameReader = NULL;
	m_pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];// create heap storage for color pixel data in RGBX format
	init();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateKinectData()));
	timer->start(33);
}

void Makeup::paintEvent(QPaintEvent * event)
{
	int w = width();
	int h = height();
	int width = w / 7;
	ui.listWidgetLeft->setGeometry(0, 0, width, h);
	ui.listWidgetLeft->setIconSize(QSize(width, width));
	ui.listWidgetRight->setGeometry(w - width, 0, width, h);
	ui.listWidgetRight->setIconSize(QSize(width, width));
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

	if (m_pKinectSensor)
	{
		m_pKinectSensor->Close();// close the Kinect Sensor
	}
	SafeRelease(m_pKinectSensor);
}


void Makeup::updateKinectData()
{
	if (!m_pColorFrameReader)
	{
		return;
	}

	IColorFrame* pColorFrame = NULL;

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
			ui.label->setPixmap(QPixmap::fromImage(QImage((uchar*)pBuffer, nWidth, nHeight, QImage::Format_RGB32)).scaled(ui.label->size(), Qt::KeepAspectRatio));
			//ProcessColor(pBuffer, nWidth, nHeight);
		}

		SafeRelease(pFrameDescription);
	}

	SafeRelease(pColorFrame);
}

void Makeup::init()
{
	HRESULT hr;

	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return;
	}
	if (m_pKinectSensor)
	{
		// Initialize the Kinect and get the color reader
		IColorFrameSource* pColorFrameSource = NULL;
		hr = m_pKinectSensor->Open();
		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
		}
		if (SUCCEEDED(hr))
		{
			hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
		}
		SafeRelease(pColorFrameSource);
	}

	if (!m_pKinectSensor || FAILED(hr))
	{
		printf("No ready Kinect found! \n");
		return;
	}
}