#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <QObject>

#include <QGraphicsScene>
#include <QtWidgets/QWidget>

#include "NodeItem.h"
#include "GraphicsView.h"

#include "Graph.h"
#include "printGraph.h"

#include "string"
#include "vector"

//DBLP �����͸� �д� ����� ǥ���ϴ� â
class LoadWindow : public QObject
{
	Q_OBJECT

public:
	LoadWindow(QObject *parent = 0);
	~LoadWindow();
	QWidget *load_Window;									//â
	void show(const Graph& graph, vector<pair<string, string>> g_edges_list);							//â ǥ��

private:
	QGraphicsScene *scene;									//â ������ QGrapgicsScene
	printGraph* pg;											//�׷����� ������ִ� ��ü
};

#endif // LOADWINDOW_H
