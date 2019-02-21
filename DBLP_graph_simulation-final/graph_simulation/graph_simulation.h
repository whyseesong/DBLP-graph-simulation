#ifndef GRAPH_SIMULATION_H
#define GRAPH_SIMULATION_H

#include "ui_graph_simulation.h"
#include "QMenu"
#include "top_k_window.h"
#include "loadwindow.h"
#include "search_one_window.h"
#include "search_two_window.h"
#include "animation_window.h"

#include <fstream>
#include <string>

#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QtCore>
#include <QDebug>

const int LAYOUT_MODE = GRAPH_LAYOUT::RANDOM_LAYOUT;
const int SCREEN_SIZE = 150;
const int NODE_LIMIT = 500;
const int NODE_LIMIT2 = 500;

using namespace std;


//스트림데이터 추가=================================================
class streamObject : public QObject {
	Q_OBJECT

public:
	explicit streamObject(QObject *parent = 0) : QObject(parent) {}
	streamObject(GraphData* initdata);
	void load_stream_data();
	void threadingSetup(QThread &trd);
	Graph read_coauthor_graph(std::ifstream& in)  throw(std::exception);
	GraphData* getData() { return gphData; };

	public slots :
	void loadByThread_Slot();

private:
	GraphData* gphData;
	int filenum;
	int totalfilenum;
};
//스트림데이터 추가=================================================



class graph_simulation : public QMainWindow
{
	Q_OBJECT

public:
	graph_simulation(QWidget *parent = 0);
	~graph_simulation();
	

	//각 기능을 표현하는 창
	//1. 데이터로드
	//2. top-k
	//3. 저자 1명 검색
	//4. 저자 2명 검색
	LoadWindow* lw;
	Top_k_window* tkw;
	Search_one_window* Sow;
	Search_two_window* Stw;
	Search_one_window* rc;
	animation_window* ani;
	//메뉴와 액션
	//asdf//QMenu* fileMenu;
	//asdf//QMenu* functionMenu;
	//asdf//QMenu* searchMenu;
	//asdf//QAction* load_File;
	//asdf//QAction* top_k;
	//asdf//QAction* search_one;
	//asdf//QAction* search_two;
	//asdf//QAction* animation;

	//메뉴와 액션 생성
	void createAction();
	void createMenu();

	

	//슬롯들
	//액션을 눌렀을 때 새 창 생성
	public slots:
	void main_loadFile_Slot();
	void main_topk_author_Slot();
	void main_search_one_author_Slot();
	void main_search_two_author_Slot();
	void main_animation_Slot();
	void main_recommend_Slot();
	//load메뉴 클릭시 공저자 그래프를 생성
	Graph read_coauthor_graph(std::ifstream& in)  throw(std::exception);

	//==========================================================================================================스트림데이터 슬롯
	void dataStreamConfirmBtn_clicked();
	void tictoc_Slot();
	//void dataPorting();

private:
	Ui::graph_simulationClass ui;

	//그래프
	Graph* graph;
	Graph tempgraph;
	typedef boost::bimap<string, int> bm_type;
	
	int node_cnt;										//vertex num
	int depth;
	string inputName;

	int sourseIndex;					//시작 노드(저자) 인덱스
	int desindex;




	bm_type g_node_ids;									//논문 저자와 해당 저자와 1대1대응하는 index로 이루어진 bimap
	vector<simple_edge> g_edges_indexes;				//int로 변환된 edge
	vector<int> g_edges_weight;							//edge weight vector : 공동 논문 작성 횟수
	vector<pair<string, string>> g_edges_list;			//edge list			 : 공동 저자 관계(pair<string, string>)
	vector<int> g_vertex_weight;						//vertex weight list : 저자의 논문작성 횟수

//스트림데이터 추가=================================================
	GraphData* addGraph;
	QThread streamTrd;
	streamObject* streamObj;
	QTimer *streamTimer;
	int countdown;

	QString loaddata;
	QTextCursor statuscursor;
};

#endif // GRAPH_SIMULATION_H
