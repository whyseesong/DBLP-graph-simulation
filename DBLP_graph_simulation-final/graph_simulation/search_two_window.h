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

//저자를 두명 검색하고, 검색된 두 저자 사이의 경로를 보여주는 창
class Search_two_window : public QObject
{
	Q_OBJECT

	typedef boost::bimap<string, int> bm_type;

public:
	Search_two_window(QObject *parent = 0);
	~Search_two_window();
	QWidget *search2_window;												//창
	void show(Graph graph, const bm_type &bimap, vector<int> edge_weight, vector<pair<string, string>> g_edges_list,int s,int d);	//창표시
private:
	QGraphicsScene *scene;													//창 내부의 QGrapgicsScene
	printGraph* pg;															//그래프를 출력해주는 객체
};

#endif // SEARCH_TWO_WINDOW_H
