#ifndef SEARCH_TWO_WINDOW_H
#define SEARCH_TWO_WINDOW_H

#include <QObject>

#include <QGraphicsScene>
#include <QtWidgets/QWidget>

#include "NodeItem.h"
#include "GraphicsView.h"

#include "Graph.h"

#include <iostream>
#include <string>

#include <printGraph.h>

using namespace std;

//���ڸ� �θ� �˻��ϰ�, �˻��� �� ���� ������ ��θ� �����ִ� â
class Search_two_window : public QObject
{
	Q_OBJECT

	typedef boost::bimap<string, int> bm_type;

public:
	Search_two_window(QObject *parent = 0);
	~Search_two_window();
	QWidget *search2_window;												//â
	void show(Graph graph, const bm_type &bimap, vector<int> edge_weight, vector<pair<string, string>> g_edges_list,int s,int d);	//âǥ��
private:
	QGraphicsScene *scene;													//â ������ QGrapgicsScene
	printGraph* pg;															//�׷����� ������ִ� ��ü
};

#endif // SEARCH_TWO_WINDOW_H
