#include "animation_window.h"
#include <QWidget>
#include <algorithm>
animation_window::animation_window(QObject *parent)
	: QObject(parent)
{
	//�����Ҵ�
	Animation_window = new QWidget();
	
	scene = new QGraphicsScene(this);
	pg = new printGraph();
	View *view = new View("temp view");
	//view�� scene ����
	view->view()->setScene(scene);
	//layout ����
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	Animation_window->setLayout(layout);
	button = new QPushButton(view);
	button->setText("Button1");
	
	connect(button, SIGNAL(clicked()), this, SLOT(clickedSlot()));
	
	
	
	Animation_window->setWindowTitle("node over 1");
}

animation_window::~animation_window()
{

}

void animation_window::show(Graph graph, const  bm_type& bimap, vector<int> edges_weight, vector<pair<string, string>> g_edges_list) {
	//��� ����ġ�� 2,3,4....�̻��ΰ͵鸸 ���ʷ� ���!
	//��� ����ġ�� ���ع̴��̸� �ش����� ����ġ�� 0���� >>��� ǥ�þȵ�
	//�ش� ���� ������ ���� ����ġ�� 0�� >> ��ǥ�� �ȵ�

	cnt = 2;
	temp = graph;
	g_edges_list_tmp = g_edges_list;
	
	edge_iterator ei, ei_end;
	for (boost::tie(ei, ei_end) = edges(temp); ei != ei_end; ++ei) {
		boost::put(edge_weight, temp, *ei, -1);
	}
	pg->print(temp, scene, g_edges_list_tmp);

	Animation_window->show();
}


void animation_window::clickedSlot() {
	cnt++;

	auto v_weight = get(vertex_priority, temp);
	
	vertex_iterator vi, vi_end;
	for (boost::tie(vi, vi_end) = vertices(temp); vi != vi_end; ++vi) {
		if(v_weight[*vi] < cnt)
		boost::put(vertex_priority, temp, *vi, -1);
	}
	pg->print(temp, scene, g_edges_list_tmp);
	string name = "node over" + cnt;
	QString qstr = QString::fromStdString(name);
	Animation_window->setWindowTitle(qstr);
	Animation_window->show();
}