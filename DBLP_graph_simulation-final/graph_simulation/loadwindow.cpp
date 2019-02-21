#include "loadwindow.h"
#include <QWidget>
#include <QDebug>

LoadWindow::LoadWindow(QObject *parent)
	: QObject(parent)
{
	//�����Ҵ�
	load_Window = new QWidget();
	scene = new QGraphicsScene(this);
	printGraph* pg = new printGraph();
	View *view = new View("temp view");
	//view�� scene ����
	view->view()->setScene(scene);
	
	//layout ����
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	load_Window->setLayout(layout);

	load_Window->setWindowTitle("coauthor graph");
}

LoadWindow::~LoadWindow()
{
	
}

//�׷��� ���
void LoadWindow::show(const Graph& graph, vector<pair<string, string>> g_edges_list) {
	pg->print(graph, scene, g_edges_list);
	//load_Window->show();
}