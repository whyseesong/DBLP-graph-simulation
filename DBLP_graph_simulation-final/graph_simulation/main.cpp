#include "graph_simulation.h"
#include <QtWidgets>
#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	graph_simulation w;
	try
	{
		w.show();
	}
	catch (const std::exception& e) {
		qDebug() << "Error: " << e.what();
		return EXIT_FAILURE;
	}

	return a.exec();
}