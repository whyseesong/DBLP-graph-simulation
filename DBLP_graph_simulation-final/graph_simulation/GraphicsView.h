#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QFrame>
#include <QGraphicsView>
#include <QGridLayout>

//pre-declare
class View;


class GraphicsView
	: public QGraphicsView
{
	Q_OBJECT
private:
	View* view;

public:
	GraphicsView(View *v) : QGraphicsView(), view(v) {};
};


class View
	: public QFrame
{
	Q_OBJECT
private:
	GraphicsView *graphicsView;

public:
	explicit View(const QString& name, QWidget *parent = 0);
	QGraphicsView *view() const;

	public slots:
	void setupMatrix();
};

#endif // GRAPHICSVIEW_H
