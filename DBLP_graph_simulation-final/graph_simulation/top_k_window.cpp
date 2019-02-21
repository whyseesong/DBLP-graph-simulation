#include "top_k_window.h"
#include <QWidget>
#include <algorithm>
#include <windows.h>

Top_k_window::Top_k_window(QObject *parent)
	: QObject(parent)
{
	//동적할당
	top_k_window = new QWidget();
	scene = new QGraphicsScene(this);
	pg = new printGraph();
	View *view = new View("temp view");
	//view의 scene 설정
	view->view()->setScene(scene);
	
	//layout 설정
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

	user_vertex_weight* uvw = new user_vertex_weight[size];												  // vertex의 index와 weight 값만 가지고 있는 클래스

	priority_queue<user_vertex_weight, vector<user_vertex_weight>, greater<user_vertex_weight>> min_heap; // paper 값이 큰 값 10개 저장 하기 위한 minheap

	//uvw 설정
	for (i = 0; i < size; i++)
	{
		uvw[i].setIndex(i);
		uvw[i].setWeight(vertex_weight[i]);
	}

	//minheap에 넣음
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

	user_vertex_weight temp1; // 임시 저장
	for (i = 0; i < 10; i++)
	{
		temp1 = min_heap.top();
		topIndex.push_back(temp1.getIndex());
		min_heap.pop();
	}

	std::sort(topIndex.begin(), topIndex.end());
	vertex_iterator vi, vi_end;

	i = 0;

	//top_k에 해당하는 vertex들의 색을 Qt::red로 변경
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		if (index[*vi] == topIndex[i]) {
			boost::put(vertex_color, graph,*vi, Qt::red);
			i++;
		}
		if (i > 9)
			break;
	}

	//그래프 출력
	//int a;
	pg->print(graph, scene, g_edges_list);
	top_k_window->show();
	top_k_window->repaint();


	/*
	cout << "2초멈춤" << endl;
	top_k_window->repaint();
	scene->clear();
	top_k_window->show();*/
}

