#include "NodeItem.h"
#include <QtWidgets>
#include <iostream>
#include <string>

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	qDebug() << QString(this->label.c_str()) <<"is chosen."<<endl;
	qDebug() <<"paper :" <<this->paper <<endl;
	qDebug() << "coauthor list" << endl;
	for (int i = 0; i < coauthor_list.size(); i++)
		qDebug() << i + 1 << ": " << coauthor_list[i].c_str() << endl;
}

void NodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
}

void NodeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
}

NodeItem::NodeItem(int x, int y, string label)
{
	this->x = x;
	this->y = y;
	this->color = QColor(Qt::darkBlue);
	this->label = label;
	setZValue(1);

	setFlags(ItemIsSelectable | ItemIsMovable);
	setAcceptHoverEvents(true);
}

NodeItem::NodeItem(int x, int y, string label, QColor uniqueColor)
{
	this->x = x;
	this->y = y;
	this->color = uniqueColor;
	this->label = label;
	setZValue(1);

	setFlags(ItemIsSelectable | ItemIsMovable);
	setAcceptHoverEvents(true);
}

NodeItem::NodeItem(int x, int y, string label, QColor uniqueColor, int paperNum)
{
	this->x = x;
	this->y = y;
	this->color = uniqueColor;
	this->label = label;
	this->paper = paperNum;
	setZValue(1);

	setFlags(ItemIsSelectable | ItemIsMovable);
	setAcceptHoverEvents(true);
}

NodeItem::NodeItem(int x, int y, string label, QColor uniqueColor, int paperNum, Graph graph)
{
	this->x = x;
	this->y = y;
	this->color = uniqueColor;
	this->label = label;
	this->paper = paperNum;


	setZValue(1);

	setFlags(ItemIsSelectable | ItemIsMovable);
	setAcceptHoverEvents(true);
}

NodeItem::NodeItem(int x, int y, string label, QColor uniqueColor, int paperNum, vector<pair<string, string>> g_edges_list)
{
	this->x = x;
	this->y = y;
	this->color = uniqueColor;
	this->label = label;
	this->paper = paperNum;
	for (int i = 0; i < g_edges_list.size(); i++) {
		if (g_edges_list[i].first == label.c_str())
			coauthor_list.push_back(g_edges_list[i].second);
		else if (g_edges_list[i].second == label.c_str())
			coauthor_list.push_back(g_edges_list[i].first);
		else
			;
	}

	setZValue(1);

	setFlags(ItemIsSelectable | ItemIsMovable);
	setAcceptHoverEvents(true);
}
QRectF NodeItem::boundingRect() const
{
	return QRectF(0, 0, paper, paper);
}

QPainterPath NodeItem::shape() const
{
	QPainterPath path;
	//path.addRect(14, 14, 82, 42);
	path.addRect(0, 0, paper, paper);
	return path;
}

void NodeItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	Q_UNUSED(widget);

	//label(이름) 출력
	QFont font("Gulim", 10);
	font.setStyleStrategy(QFont::ForceOutline);
	painter->setFont(font);
	painter->save();
	painter->scale(0.3, 0.3);
	painter->drawText(0, 0, QString(label.c_str()));
	painter->restore();


	//원(노드) 출력
	QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
	if (option->state & QStyle::State_MouseOver) fillColor = fillColor.light(125);
	QPen pen = painter->pen();
	pen.setWidth(0);
	pen.setColor(QColor(Qt::black));
	painter->setPen(pen);
	painter->setBrush(QBrush(fillColor));
	painter->drawEllipse(0, 0, paper, paper);
}
