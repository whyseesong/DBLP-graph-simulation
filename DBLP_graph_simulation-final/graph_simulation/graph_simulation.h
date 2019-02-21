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


//��Ʈ�������� �߰�=================================================
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
//��Ʈ�������� �߰�=================================================



class graph_simulation : public QMainWindow
{
	Q_OBJECT

public:
	graph_simulation(QWidget *parent = 0);
	~graph_simulation();
	

	//�� ����� ǥ���ϴ� â
	//1. �����ͷε�
	//2. top-k
	//3. ���� 1�� �˻�
	//4. ���� 2�� �˻�
	LoadWindow* lw;
	Top_k_window* tkw;
	Search_one_window* Sow;
	Search_two_window* Stw;
	Search_one_window* rc;
	animation_window* ani;
	//�޴��� �׼�
	//asdf//QMenu* fileMenu;
	//asdf//QMenu* functionMenu;
	//asdf//QMenu* searchMenu;
	//asdf//QAction* load_File;
	//asdf//QAction* top_k;
	//asdf//QAction* search_one;
	//asdf//QAction* search_two;
	//asdf//QAction* animation;

	//�޴��� �׼� ����
	void createAction();
	void createMenu();

	

	//���Ե�
	//�׼��� ������ �� �� â ����
	public slots:
	void main_loadFile_Slot();
	void main_topk_author_Slot();
	void main_search_one_author_Slot();
	void main_search_two_author_Slot();
	void main_animation_Slot();
	void main_recommend_Slot();
	//load�޴� Ŭ���� ������ �׷����� ����
	Graph read_coauthor_graph(std::ifstream& in)  throw(std::exception);

	//==========================================================================================================��Ʈ�������� ����
	void dataStreamConfirmBtn_clicked();
	void tictoc_Slot();
	//void dataPorting();

private:
	Ui::graph_simulationClass ui;

	//�׷���
	Graph* graph;
	Graph tempgraph;
	typedef boost::bimap<string, int> bm_type;
	
	int node_cnt;										//vertex num
	int depth;
	string inputName;

	int sourseIndex;					//���� ���(����) �ε���
	int desindex;




	bm_type g_node_ids;									//�� ���ڿ� �ش� ���ڿ� 1��1�����ϴ� index�� �̷���� bimap
	vector<simple_edge> g_edges_indexes;				//int�� ��ȯ�� edge
	vector<int> g_edges_weight;							//edge weight vector : ���� �� �ۼ� Ƚ��
	vector<pair<string, string>> g_edges_list;			//edge list			 : ���� ���� ����(pair<string, string>)
	vector<int> g_vertex_weight;						//vertex weight list : ������ ���ۼ� Ƚ��

//��Ʈ�������� �߰�=================================================
	GraphData* addGraph;
	QThread streamTrd;
	streamObject* streamObj;
	QTimer *streamTimer;
	int countdown;

	QString loaddata;
	QTextCursor statuscursor;
};

#endif // GRAPH_SIMULATION_H
