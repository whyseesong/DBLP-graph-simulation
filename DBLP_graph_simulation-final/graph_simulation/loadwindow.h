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

//DBLP 데이터를 읽는 기능을 표시하는 창
class LoadWindow : public QObject
{
	Q_OBJECT

public:
	LoadWindow(QObject *parent = 0);
	~LoadWindow();
	QWidget *load_Window;									//창
	void show(const Graph& graph, vector<pair<string, string>> g_edges_list);							//창 표시

private:
	QGraphicsScene *scene;									//창 내부의 QGrapgicsScene
	printGraph* pg;											//그래프를 출력해주는 객체
};

#endif // LOADWINDOW_H
