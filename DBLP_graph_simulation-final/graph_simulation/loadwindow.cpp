#include "loadwindow.h"
#include <QWidget>
#include <QDebug>

LoadWindow::LoadWindow(QObject *parent)
	: QObject(parent)
{
	//동적할당
	load_Window = new QWidget();
	scene = new QGraphicsScene(this);
	printGraph* pg = new printGraph();
	View *view = new View("temp view");
	//view의 scene 설정
	view->view()->setScene(scene);
	
	//layout 설정
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	load_Window->setLayout(layout);

	load_Window->setWindowTitle("coauthor graph");
}

LoadWindow::~LoadWindow()
{
	
}

//그래프 출력
void LoadWindow::show(const Graph& graph, vector<pair<string, string>> g_edges_list) {
	pg->print(graph, scene, g_edges_list);
	//load_Window->show();
}