#pragma once

#include <QColor>
#include <QGraphicsItem>
#include <Graph.h>
#include <vector>
#include <string>

using namespace std;

//const int NODE_SIZE = 4;

class NodeItem :
	public QGraphicsItem
{
private:
	int x;
	int y;
	QColor color;
	string label;
	int paper;
	vector<string> coauthor_list;

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

public:
	NodeItem(int x, int y, string label);
	NodeItem(int x, int y, string label, QColor uniqueColor);
	NodeItem(int x, int y, string label, QColor uniqueColor,int paperNum);
	NodeItem(int x, int y, string label, QColor uniqueColor, int paperNum,Graph graph);
	NodeItem(int x, int y, string label, QColor uniqueColor, int paperNum, vector<pair<string, string>> g_edges_list);
	QRectF boundingRect() const override;
	QPainterPath shape() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

