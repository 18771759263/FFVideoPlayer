#include "FFVideoPlayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FFVideoPlayer w;
	w.show();
	return a.exec();
}
