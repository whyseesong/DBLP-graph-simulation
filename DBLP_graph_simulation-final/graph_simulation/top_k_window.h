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

//top-k 저자들을 기준으로 하는 그래프를 보여주는 창
class Top_k_window : public QObject
{
	Q_OBJECT

public:
	Top_k_window(QObject *parent = 0);
	~Top_k_window();
	QWidget *top_k_window;								//창
	void show(Graph graph, vector<int> vertex_weight, vector<pair<string, string>> g_edges_list);	//창표시

private:
	QGraphicsScene *scene;								//창 내부의 QGrapgicsScene
	printGraph* pg;										//그래프를 출력해주는 객체
	QPushButton *button;
};

#endif // TOP_K_WINDOW_H
