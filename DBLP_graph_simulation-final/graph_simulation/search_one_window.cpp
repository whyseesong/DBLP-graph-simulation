#include "search_one_window.h"
#include <QWidget>
#include <QDebug>
#include <QMessageBox>

const int SCREEN_SIZE = 150;
const int LAYOUT_MODE = GRAPH_LAYOUT::CIRCLE_LAYOUT;

Search_one_window::Search_one_window(QObject *parent)
	: QObject(parent)
{
	search1_window = new QWidget();

	scene = new QGraphicsScene(this);

	View *view = new View("temp view");
	view->view()->setScene(scene);
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	search1_window->setLayout(layout);

	search1_window->setWindowTitle("1 author graph");
}

Search_one_window::~Search_one_window()
{

}

bool compare(simple_edge a1, simple_edge a2);

pair<Graph,bool> Search_one_window::makeGraph(const Graph& graph, const  bm_type& bimap, vector<simple_edge> edges_index, int depth, vector<pair<string, string>> g_edges_list, string inputName)
{
	vertex_iterator vi, vi_end;
	edge_iterator ei, ei_end;

	pair<Graph, bool> temp;

	scene->clear();
	int i = 0, j = 0, k = 0;
	int depth_cnt = 0;
	int node_cnt = 0;

	int tokens[2];

	int authorIndex; // �Է��� ������ index ��

	bm_type*  real_node_ids = new bm_type[depth + 1]; // depth + 1��ŭ ���� �Ҵ� (�ӽ÷� ����)

	bm_type node_ids; // ���� ������ bm_type

	vector<simple_edge> sub_edges_list; // ���� ������ simple_edge ����

	auto author_iter = bimap.left.find(inputName);

	// Ž��
	if (author_iter != bimap.left.end())
	{
		authorIndex = author_iter->second;
		real_node_ids[0].insert(bm_type::value_type(inputName, authorIndex));
	}
	else
	{
		//cout << "cant find author" << endl;
		QMessageBox::information(this->search1_window, "error", "can't find author");
		temp.first = graph;
		temp.second = false;
		return temp;
	}
	bool isOverlap = false; // �ߺ� üũ

	while (depth_cnt != depth) // ���� ���� ��ŭ �ݺ�
	{
		int edges_index_size = edges_index.size();
		int real_node_ids_size = real_node_ids[depth_cnt].size();
		for (i = 0; i < edges_index_size; i++)
		{
			tokens[0] = edges_index[i].first;
			tokens[1] = edges_index[i].second;

			for (j = 0; j < real_node_ids_size; j++)
			{
				auto it_author1 = real_node_ids[depth_cnt].right.find(tokens[0]);
				auto it_author2 = real_node_ids[depth_cnt].right.find(tokens[1]);
				isOverlap = false;

				if (it_author1 != real_node_ids[depth_cnt].right.end()) {

					for (k = 0; k < depth_cnt; k++)
					{
						auto it1 = real_node_ids[k].right.find(tokens[1]);
						if (it1 != real_node_ids[k].right.end())
						{
							isOverlap = true;
							break;
						}
					}
					if (!isOverlap)
					{
						real_node_ids[depth_cnt + 1].insert(new_bm_type::value_type(bimap.right.find(tokens[1])->get_left(), tokens[1]));
						sub_edges_list.push_back({ tokens[0],tokens[1] });
						break;
					}
				}
				if (it_author2 != real_node_ids[depth_cnt].right.end()) {
					for (k = 0; k < depth_cnt; k++)
					{
						auto it2 = real_node_ids[k].right.find(tokens[0]);
						if (it2 != real_node_ids[k].right.end())
						{
							isOverlap = true;
							break;
						}
					}
					if (!isOverlap)
					{
						real_node_ids[depth_cnt + 1].insert(new_bm_type::value_type(bimap.right.find(tokens[0])->get_left(), tokens[0]));
						sub_edges_list.push_back({ tokens[0],tokens[1] });
						break;
					}
				}
			}
		}

		depth_cnt++;
	}

	for (i = 0; i < depth + 1; i++) // �ӽ÷� ������ bm_type�� 1�������� ����
	{
		for (auto it = real_node_ids[i].begin(); it != real_node_ids[i].end(); ++it) {
			node_ids.insert(new_bm_type::value_type(it->left, it->right));
		}
	}

	int num = 0;
	for (i = 0; i < edges_index.size(); i++) // �߰��� �� index�� ������ ����
	{
		for (int j = 0; j < sub_edges_list.size(); j++)
		{
			if (sub_edges_list[j].first == i || sub_edges_list[j].second == i)
			{
				for (int k = 0; k < sub_edges_list.size(); k++)
				{
					if (sub_edges_list[k].first == i)
						sub_edges_list[k].first = num;
					else if (sub_edges_list[k].second == i)
						sub_edges_list[k].second = num;
				}
				num++;
				break;
			}
		}
	}

	num = 0;
	for (i = 0; i < edges_index.size(); i++) // �߰��� �� index�� ������ ����
	{
		for (auto it = node_ids.begin(); it != node_ids.end(); ++it) {
			if (it->get_right() == i)
			{
				for (auto it2 = node_ids.begin(); it2 != node_ids.end(); ++it2) {
					if (it2->get_right() == i)
						node_ids.replace_right(it2, num);
				}
				num++;
				break;
			}
		}
	}

	sort(sub_edges_list.begin(), sub_edges_list.end(), compare); // ����

	Graph new_graph(sub_edges_list.begin(), sub_edges_list.end(), node_ids.size());


	i = 0;

	for (boost::tie(vi, vi_end) = vertices(new_graph); vi != vi_end; ++vi) {
		//Vertex Property ����
		//index: 0 ~ ...
		//name : map�� value(i) �������� ã�� Key
		//		map --> map<string, int> (boost bidirectional map)


		//*********************************************�����ؾ��Ұ�

		boost::put(vertex_priority, new_graph, *vi, 2);
		boost::put(vertex_index, new_graph, *vi, i);
		boost::put(vertex_name, new_graph, *vi, node_ids.right.find(i)->get_left());
		if (node_ids.right.find(i)->get_left() == inputName)
		{
			boost::put(vertex_color, new_graph, *vi, Qt::red);
		}
		else
			boost::put(vertex_color, new_graph, *vi, Qt::black);
		++i;
	}

	i = 0;
	for (boost::tie(ei, ei_end) = edges(new_graph); ei != ei_end; ++ei) {
		boost::put(edge_weight, new_graph, *ei, 1);
		boost::put(edge_color, new_graph, *ei, Qt::black);
		boost::put(edge_index, new_graph, *ei, i);
		++i;
	}


	auto position = get(vertex_position, new_graph);
	auto label = get(vertex_name, new_graph);

	minstd_rand gen;
	Topology topology(gen, (double)SCREEN_SIZE);
	Topology::point_type origin;
	origin[0] = origin[1] = (double)SCREEN_SIZE;
	Topology::point_difference_type extent;
	extent[0] = extent[1] = (double)SCREEN_SIZE;
	rectangle_topology<> rect_top(gen,
		-SCREEN_SIZE / 2, -SCREEN_SIZE / 2,
		SCREEN_SIZE / 2, SCREEN_SIZE / 2);

	switch (LAYOUT_MODE) {
	case GRAPH_LAYOUT::RANDOM_LAYOUT:
		random_graph_layout(new_graph, get(vertex_position, new_graph), rect_top);
		break;

	case GRAPH_LAYOUT::CIRCLE_LAYOUT:
		circle_graph_layout(new_graph, get(vertex_position, new_graph), SCREEN_SIZE / 2);
		break;

		//case GRAPH_LAYOUT::KAMADA_KAWAI_LAYOUT:
		//	kamada_kawai_spring_layout(graph,
		//		get(vertex_position, graph),
		//		get(edge_weight, graph),
		//		topology,
		//		side_length((double)SCREEN_SIZE)
		//	);
		//	break;

	case GRAPH_LAYOUT::FRUCHTERMAN_REINGOLD_LAYOUT:
		fruchterman_reingold_force_directed_layout(new_graph,
			get(vertex_position, new_graph),
			topology,
			attractive_force(square_distance_attractive_force())
			.cooling(linear_cooling<double>(50))
		);
		break;
	}
	temp.first = new_graph;
	temp.second = true;
	return temp;
}

void Search_one_window::show(const Graph& graph, const  bm_type& bimap, vector<simple_edge> edges_index, int depth, vector<pair<string, string>> g_edges_list, string inputName) {

	pair<Graph,bool> temp = makeGraph(graph, bimap, edges_index, depth, g_edges_list, inputName);
	if (!temp.second)
		return;

	Graph new_graph = temp.first;

	pg->print(new_graph, scene, g_edges_list);

	search1_window->show();
}

void Search_one_window::recommendCoauthor(const Graph& graph, const  bm_type& bimap, vector<simple_edge> edges_index, int depth, vector<pair<string, string>> g_edges_list, string inputName)
{
	pair<Graph, bool> tmp = makeGraph(graph, bimap, edges_index, depth, g_edges_list, inputName);
	if (!tmp.second)
		return;

	Graph new_graph = tmp.first;
	vertex_iterator vi, vi_end;

	int i = 0;
	int edges_index_size = g_edges_list.size();

	int authorIndex;
	string temp;

	auto author_iter = bimap.left.find(inputName);
	authorIndex = author_iter->second;

	auto label = get(vertex_name, new_graph);
	auto v_color = get(vertex_color, new_graph);

	auto v_weight = get(vertex_priority, new_graph);

	for (boost::tie(vi, vi_end) = vertices(new_graph); vi != vi_end; ++vi) {
		boost::put(vertex_color, new_graph, *vi, Qt::yellow);
		v_weight[*vi] = 3;
	}



	for (i; i < edges_index_size; i++)
	{
		if (g_edges_list[i].first == inputName)
		{
			temp = g_edges_list[i].second;
		}
		else if (g_edges_list[i].second == inputName)
		{
			temp = g_edges_list[i].first;
		}
		else
			continue;
		for (boost::tie(vi, vi_end) = vertices(new_graph); vi != vi_end; ++vi) {
			if (label[*vi] == temp) {
				boost::put(vertex_color, new_graph, *vi, Qt::black);
			}
		}
	}

	for (boost::tie(vi, vi_end) = vertices(new_graph); vi != vi_end; ++vi) {
		if (label[*vi] == inputName)
			boost::put(vertex_color, new_graph, *vi, Qt::red);
	}

	pg->print(new_graph, scene, g_edges_list);

	search1_window->show();
}

bool compare(simple_edge a1, simple_edge a2)
{
	return a1.first < a2.first;
}