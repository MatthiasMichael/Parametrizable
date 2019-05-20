#include <QApplication>

#include "ExampleWidget.h"


int main(int argc, char * argv[])
{
	QApplication app(argc, argv);

	ExampleWidget w;
	w.show();

	return app.exec();
}
