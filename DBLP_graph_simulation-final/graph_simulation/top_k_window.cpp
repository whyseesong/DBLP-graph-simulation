#include "top_k_window.h"
#include <QWidget>
#include <algorithm>
#include <windows.h>

Top_k_window::Top_k_window(QObject *parent)
	: QObject(parent)
{
	//�����Ҵ�
	top_k_window = new QWidget();
	scene = new QGraphicsScene(this);
	pg = new printGraph();
	View *view = new View("temp view");
	//view�� scene ����
	view->view()->setScene(scene);
	
	//layout ����
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	top_k_window->setLayout(layout);

	top_k_window->setWindowTitle("top-10 authors graph");
}

Top_k_window::~Top_k_window()
{

}

void Top_k_window::show(Graph graph, vector<int> vertex_weight, vector<pair<string, string>> g_edges_list) {
	const int rect_sz = 4;
	auto position = get(vertex_position, graph);
	auto label = get(vertex_name, graph);
	auto index = get(vertex_index, graph);
	auto v_color = get(vertex_color, graph);
	auto e_color = get(edge_color, graph);
	auto e_weight = get(edge_weight, graph);

	vector<int> topIndex;
	int size = vertex_weight.size();
	int i = 0;

	user_vertex_weight* uvw = new user_vertex_weight[size];												  // vertex�� index�� weight ���� ������ �ִ� Ŭ����

	priority_queue<user_vertex_weight, vector<user_vertex_weight>, greater<user_vertex_weight>> min_heap; // paper ���� ū �� 10�� ���� �ϱ� ���� minheap

	//uvw ����
	for (i = 0; i < size; i++)
	{
		uvw[i].setIndex(i);
		uvw[i].setWeight(vertex_weight[i]);
	}

	//minheap�� ����
	for (i = 0; i < size; i++)
	{
		if(min_heap.size() < 10)
			min_heap.push(uvw[i]);
		else
		{
			if (min_heap.top() < uvw[i])
			{
				min_heap.pop();
				min_heap.push(uvw[i]);
			}
		}
	}

	user_vertex_weight temp1; // �ӽ� ����
	for (i = 0; i < 10; i++)
	{
		temp1 = min_heap.top();
		topIndex.push_back(temp1.getIndex());
		min_heap.pop();
	}

	std::sort(topIndex.begin(), topIndex.end());
	vertex_iterator vi, vi_end;

	i = 0;

	//top_k�� �ش��ϴ� vertex���� ���� Qt::red�� ����
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		if (index[*vi] == topIndex[i]) {
			boost::put(vertex_color, graph,*vi, Qt::red);
			i++;
		}
		if (i > 9)
			break;
	}

	//�׷��� ���
	//int a;
	pg->print(graph, scene, g_edges_list);
	top_k_window->show();
	top_k_window->repaint();


	/*
	cout << "2�ʸ���" << endl;
	top_k_window->repaint();
	scene->clear();
	top_k_window->show();*/
}

