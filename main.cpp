#include "Makeup.h"
#include "sliderpicture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SliderPicture w;
	Makeup s;
	w.show();
	QObject::connect(&w, SIGNAL(quit()), &s, SLOT(exit()));
	QObject::connect(&w, SIGNAL(kinectWindow(int, int)), &s, SLOT(recieveMode(int,int)));
	QObject::connect(&s, SIGNAL(backToMain()), &w, SLOT(nowWindow()));
	QObject::connect(&s, SIGNAL(quit()), &w, SLOT(exit()));
	return a.exec();
}
