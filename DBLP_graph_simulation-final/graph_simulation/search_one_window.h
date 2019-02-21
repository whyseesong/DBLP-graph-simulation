#ifndef SEARCH_ONE_WINDOW_H
#define SEARCH_ONE_WINDOW_H

#include <QObject>

#include <QGraphicsScene>
#include <QtWidgets/QWidget>

#include "NodeItem.h"
#include "GraphicsView.h"

#include "Graph.h"
#include "printGraph.h"

#include <iostream>
#include <string>

using namespace std;

enum GRAPH_LAYOUT {
	RANDOM_LAYOUT,
	CIRCLE_LAYOUT,
	//KAMADA_KAWAI_LAYOUT,
	FRUCHTERMAN_REINGOLD_LAYOUT	//slow
};

//���ڸ� �Ѹ� �˻��ϰ� �׸� ���������ϴ� �׷����� �����ִ� â
class Search_one_window : public QObject
{
	Q_OBJECT

public:
	Search_one_window(QObject *parent = 0);
	~Search_one_window();
	QWidget *search1_window;					//â
	void show(const Graph& graph, const  bm_type& bimap, vector<simple_edge> edges_index, int depth, vector<pair<string, string>> g_edges_list, string inputName);								//âǥ��
	pair<Graph,bool> makeGraph(const Graph& graph, const  bm_type& bimap, vector<simple_edge> edges_index, int depth, vector<pair<string, string>> g_edges_list, string inputName);
	void recommendCoauthor(const Graph& graph, const  bm_type& bimap, vector<simple_edge> edges_index, int depth, vector<pair<string, string>> g_edges_list, string inputName);
private:
	QGraphicsScene *scene;
	printGraph* pg;
};

#endif // SEARCH_ONE_WINDOW_H
