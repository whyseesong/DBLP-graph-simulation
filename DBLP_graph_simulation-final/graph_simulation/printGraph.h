#pragma once
#include <QObject>

#include <QGraphicsScene>
#include <QtWidgets/QWidget>

#include "NodeItem.h"
#include "GraphicsView.h"

#include "Graph.h"

class printGraph {
public:
	printGraph();
	 ~printGraph();
	void print(const Graph& graph, QGraphicsScene *scene);
	void print(const Graph& graph, QGraphicsScene *scene, vector<pair<string, string>> g_edges_list);
};
