#pragma once
#include <QObject>

#include <QGraphicsScene>
#include <QtWidgets/QWidget>
#include <QPushbutton>

#include "NodeItem.h"
#include "GraphicsView.h"

#include "Graph.h"

#include <iostream>
#include <string>

#include <printGraph.h>

using namespace std;

//���ڸ� �θ� �˻��ϰ�, �˻��� �� ���� ������ ��θ� �����ִ� â
class animation_window : public QObject
{
	Q_OBJECT

		typedef boost::bimap<string, int> bm_type;

public:
	animation_window(QObject *parent = 0);
	~animation_window();
	QWidget* Animation_window;	
	QPushButton* button;
	void show(Graph graph, const bm_type &bimap, vector<int> edge_weight, vector<pair<string, string>> g_edges_list);	//âǥ��
private:
	QGraphicsScene *scene;													//â ������ QGrapgicsScene
	printGraph* pg;															//�׷����� ������ִ� ��ü
	Graph temp;
	vector<pair<string, string>> g_edges_list_tmp;
	int cnt;

public slots:
	void clickedSlot();
};