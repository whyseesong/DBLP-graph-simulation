#ifndef TOP_K_WINDOW_H
#define TOP_K_WINDOW_H

#include <QObject>
#include <QGraphicsScene>
#include <QtWidgets/QWidget>
#include <QDebug>

#include <vector>
#include <queue>
#include <functional>
#include <QPushbutton>
#include "NodeItem.h"
//#include "GraphicsView.h"

#include "user_vertex_weight.h"

#include "Graph.h"
#include "printGraph.h"

using namespace std;

//top-k ���ڵ��� �������� �ϴ� �׷����� �����ִ� â
class Top_k_window : public QObject
{
	Q_OBJECT

public:
	Top_k_window(QObject *parent = 0);
	~Top_k_window();
	QWidget *top_k_window;								//â
	void show(Graph graph, vector<int> vertex_weight, vector<pair<string, string>> g_edges_list);	//âǥ��

private:
	QGraphicsScene *scene;								//â ������ QGrapgicsScene
	printGraph* pg;										//�׷����� ������ִ� ��ü
	QPushButton *button;
};

#endif // TOP_K_WINDOW_H
