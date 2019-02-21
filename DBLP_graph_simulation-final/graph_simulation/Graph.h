#ifndef GRAPH_H
#define GRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topology.hpp>
#include <boost/graph/graph_traits.hpp>

#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/circle_layout.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/bimap.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <QColor>
using namespace std;
using namespace boost;

enum vertex_position_t { vertex_position };

namespace boost {
	BOOST_INSTALL_PROPERTY(vertex, position);
}

typedef square_topology<>::point_type point;

struct simple_edge {
	int first, second;
};

typedef property<vertex_index_t, int,
		property<vertex_name_t, std::string,
		property<vertex_position_t, point,
		property<vertex_color_t,QColor,
		property<vertex_priority_t,int>>>>
	> VertexProperties;

typedef adjacency_list<
	listS,	//outEdgeList
	listS,	//VertexList
	undirectedS,
	//vertex properties
	VertexProperties,
	//edge properties
	property<edge_weight_t, double,
	property<edge_color_t, QColor,
	property<edge_index_t,int>>>
> Graph;

//typedef
//*******************************************************************************************************
typedef bimap<std::string, int> bm_type;
typedef bimap<std::string, int> new_bm_type;
typedef typename graph_traits<Graph>::edge_iterator edge_iterator;
typedef typename graph_traits<Graph>::vertex_iterator vertex_iterator;

typedef graph_traits < Graph >::vertex_descriptor Vertex;
typedef graph_traits < Graph >::edge_descriptor Edge;

typedef property_map<Graph, vertex_name_t>::type vertex_name_Map;
typedef property_map<Graph, edge_weight_t>::type edge_weight_Map;
typedef property_map < Graph, vertex_index_t >::type vertex_Index_Map;

typedef property<edge_weight_t, int> WeightProperty;
typedef property<vertex_name_t, std::string> NameProperty;

typedef iterator_property_map < Vertex*, vertex_Index_Map, Vertex, Vertex& > PredecessorMap;
typedef iterator_property_map < int*, vertex_Index_Map, int, int& > DistanceMap;
typedef graph_traits<Graph>::vertex_descriptor VertexDescriptor;

typedef square_topology<> Topology;
typedef typename Topology::point_type Point;
//typedef end
//******************************************************************************************************

struct GraphData {
	Graph* t_coauthorGraph;
	bm_type* t_node_ids;
	std::vector<simple_edge>* t_edges_indexes;	//int로 변환된 edge
	std::vector<int>* t_edges_weight;			//edge weight vector
	std::vector<pair<string, string>>* t_edges_list;
	std::vector<int>* t_vertex_weight;
	int* t_node_cnt;
};

#endif //GRAPH_H