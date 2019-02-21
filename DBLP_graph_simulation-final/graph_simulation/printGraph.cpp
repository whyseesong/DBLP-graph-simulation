#include <printGraph.h>

printGraph::printGraph() {

}

printGraph::~printGraph() {

}


void printGraph::print(const Graph& graph, QGraphicsScene *scene, vector<pair<string, string>> g_edges_list) {
	scene->clear();
	
	
	//print graph
	typedef square_topology<> Topology;
	typedef typename Topology::point_type Point;
	const int rect_sz = 4;
	auto position = get(vertex_position, graph);
	auto label = get(vertex_name, graph);
	auto v_color = get(vertex_color, graph);
	auto v_weight = get(vertex_priority, graph);
	auto e_color = get(edge_color, graph);
	auto e_weight = get(edge_weight, graph);
	


	//print edges
	edge_iterator ei, ei_end;
	Vertex u, v;
	for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
		if (e_weight[*ei] == 0)
			continue;

		u = source(*ei, graph);
		v = target(*ei, graph);

		Point p1 = position[u];
		Point p2 = position[v];
		scene->addLine(p1[0], p1[1], p2[0], p2[1], QPen(e_color[*ei], (e_weight[*ei]-1)/2));
		//scene->addLine(p1[0], p1[1], p2[0], p2[1], QPen(e_color[*ei], -1));
	}

	//print nodes
	vertex_iterator vi, vi_end;
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		if (v_weight[*vi] == -1)
			continue;

		Point p = position[*vi];
		std::string name = label[*vi];
		QGraphicsItem *node = new NodeItem(p[0], p[1],name.c_str(), v_color[*vi],v_weight[*vi], g_edges_list);
		node->setPos(QPointF(p[0], p[1]));
		scene->addItem(node);
	}
}