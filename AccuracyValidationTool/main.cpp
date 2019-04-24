#include "accuracyvalidationtool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AccuracyValidationTool w;
	w.show();
	return a.exec();
}
