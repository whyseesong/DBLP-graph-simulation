#include "search_two_window.h"
#include <QWidget>
#include <algorithm>
#include <QInputDialog>
Search_two_window::Search_two_window(QObject *parent)
	: QObject(parent)
{
	//�����Ҵ�
	search2_window = new QWidget();
	scene = new QGraphicsScene(this);
	pg = new printGraph();
	View *view = new View("temp view");
	//view�� scene ����
	view->view()->setScene(scene);
	
	//layout ����
	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(view);
	search2_window->setLayout(layout);
	search2_window->setWindowTitle("graph between two authors");
}

Search_two_window::~Search_two_window()
{

}

void Search_two_window::show(Graph graph,const  bm_type& bimap, vector<int> edges_weight, vector<pair<string, string>> g_edges_list,int s,int d) {

	

	int i = 0;

	const int rect_sz = 4;
	auto position = get(vertex_position, graph); // ����� ��ǥ
	auto label = get(vertex_name, graph); // ����� �̸�
	auto index = get(vertex_index, graph); // ����� �ε���
	auto e_weight = get(edge_weight, graph); //edge weight

	//type define
	//*****************************************************************************************************
	
	//*****************************************************************************************************
	//end type define	
	int sourseIndex = s;					//���� ���(����) �ε���
	int desindex = d;		
	

	//��ǥ ���(����) �ε���
	
	edge_iterator ei, ei_end; //graph edge iterator

	VertexDescriptor u, v; //graph vertex descriptor
	vertex_iterator vi, vi_end;  //graph vertex iterator


		//shortest path�� ã������ dijkstra�˰����� ����ϴµ�
		//�� �˰����� weight�� ���� �ּҰ� �Ǵ� path�� ã�´�
		//���� �׷����� weight�� �������� Ƚ���̹Ƿ� dijkstra�˰��� ���Ǳ⿡�� ���������ʴ�
		//�׷��� ��� edge�� weight�� ������ ��ȯ�� �� dijkstra�˰����� ����Ѵ�

		for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
			boost::put(edge_weight, graph, *ei, double(1/e_weight[*ei]));
		}

		std::vector<Vertex> predecessors(num_vertices(graph)); // To store parents
		std::vector<int> distances(num_vertices(graph)); // To store distances

		vertex_Index_Map indexMap = get(vertex_index, graph); // ���(����)�� �ε����� �����ϴ� property_map 
		PredecessorMap predecessorMap(&predecessors[0], indexMap); // iterator_property_map
		DistanceMap distanceMap(&distances[0], indexMap); // distance_property_map
		 
		Vertex start = vertex(sourseIndex, graph); 	// ���� ���(����)

		//dijkstra �˰��� ����

		dijkstra_shortest_paths(graph, start, boost::distance_map(distanceMap).predecessor_map(predecessorMap));
		vertex_name_Map nameMap = get(boost::vertex_name, graph); // ���(����)�� �̸��� �����ϴ� property_map


		typedef vector<Graph::edge_descriptor> PathType;

		PathType path;
		vector<int> path_index;

			Vertex end = vertex(desindex, graph);
			//��ǥ ������ ���� ����� �������� �������
			for (Vertex u = predecessorMap[end]; // Start by setting 'u' to the destintaion node's predecessor
				u != end; // Keep tracking the path until we get to the source
				end = u, u = predecessorMap[end]) // Set the current vertex to the current predecessor, and the predecessor to one level up
			{
				std::pair<Edge, bool> edgePair = edge(u, end, graph);
				Edge edge = edgePair.first;
				path.push_back(edge);
			}

			std::cout << "Shortest path" << endl;



			vector<Vertex> path_vec;
			//�������� ����� ��θ� ���������� ������
			int totalDistance = 0;
			i = 0;
			for (PathType::reverse_iterator pathIterator = path.rbegin(); pathIterator != path.rend(); ++pathIterator)
			{
				std::cout << nameMap[source(*pathIterator, graph)] << " -> " << nameMap[target(*pathIterator, graph)]
					<< " = " << get(edge_weight, graph, *pathIterator) << std::endl;
				path_index.push_back(get(edge_index, graph, *pathIterator));
			}

			std::sort(path_index.begin(), path_index.end());


			std::cout << std::endl;

			auto e_index = get(edge_index, graph);

			//��λ� �ִ� edge���� edge_color(��) = Qt::red, edge_weight(����) = 3
			i = 0;
			for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
				if (path_index[i] == e_index[*ei]) {
					boost::put(edge_color, graph, *ei, Qt::red);
					boost::put(edge_weight, graph, *ei, 3);
					i++;
				}
				if (i > path_index.size() - 1)
					break;
			}

			//���۳��,��ǥ����� vertex_color(��) = Qt::red
			auto v_index = get(vertex_index, graph);
			i = 0;
			for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
				if (v_index[*vi] == sourseIndex || v_index[*vi] == desindex) {
					boost::put(vertex_color, graph, *vi, Qt::red);
					i++;
				}
				if (i == 2)
					break;
			}
			pg->print(graph, scene, g_edges_list);

	search2_window->show();
}