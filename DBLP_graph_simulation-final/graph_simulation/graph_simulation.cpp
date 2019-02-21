#include "graph_simulation.h"
#include <QMessageBox>
#include <QInputDialog>


//const char* COAUTHORSHIP_FILENAME = "dblp-coauthor.txt";
string COAUTHORSHIP_FILENAME = "dblp-coauthor";

graph_simulation::graph_simulation(QWidget *parent)
	: QMainWindow(parent)
{
	//창들을 동적 할당
	lw = new LoadWindow();
	tkw = new Top_k_window();
	Sow = new Search_one_window();
	Stw = new Search_two_window();
	ani = new animation_window();
	rc = new Search_one_window();
	ui.setupUi(this);

	//액션과 메뉴 생성
	createAction();
	createMenu();

	//탭관련코드======================================================
	QTabWidget* tabwindow = new QTabWidget(ui.tabbox);
	tabwindow->setGeometry(QRect(0, 0, 901, 741));
	tabwindow->setTabsClosable(true);
	tabwindow->setMovable(true);
	tabwindow->insertTab(1, tkw->top_k_window, "Top-K");
	tabwindow->insertTab(2, Sow->search1_window, "Search 1 author");
	tabwindow->insertTab(3, Stw->search2_window , "Search 2 author");
	tabwindow->insertTab(4, ani->Animation_window, "Animation");
	tabwindow->insertTab(5, rc->search1_window, "Recommend");

	//ui.label_dataStatus->setSource(loaddata);
	//ui.label_dataStatus->setCursor()
	statuscursor = ui.label_dataStatus->cursorForPosition(ui.label_dataStatus->pos());

	

	node_cnt = 0;

	addGraph = new GraphData;

	//스트림데이터 관련 추가
	streamTimer = new QTimer(this);
	//datastream confirm clicker
	connect(ui.pushBtn_streamConfirm, SIGNAL(clicked()), this, SLOT(dataStreamConfirmBtn_clicked()));
	//timer
	connect(streamTimer, SIGNAL(timeout()), this, SLOT(tictoc_Slot()));
	



	addGraph->t_coauthorGraph = graph;
	addGraph->t_node_ids = &g_node_ids;
	addGraph->t_edges_indexes = &g_edges_indexes;
	addGraph->t_edges_weight = &g_edges_weight;
	addGraph->t_edges_list = &g_edges_list;
	addGraph->t_vertex_weight = &g_vertex_weight;
	addGraph->t_node_cnt = &node_cnt;

	streamObj = new streamObject(addGraph);

	streamObj->threadingSetup(streamTrd);
	streamObj->moveToThread(&streamTrd);



}

graph_simulation::~graph_simulation()
{
	//동적할당 해제
	delete lw;
	delete tkw;
	delete Sow;
	delete Stw;
	delete ani;
	delete graph;
}

//액션 생성
void graph_simulation::createAction() {
	
	//파일 로드
	//1. 액션 동적 할당
	//asdf//load_File = new QAction(tr("load"), this);
	//2. status tip 설정
	//asdf//load_File->setStatusTip(tr("load data"));
	//3. SINAL,SLOT 설정
	//asdf//connect(load_File, SIGNAL(triggered()), this, SLOT(main_loadFile_Slot()));
	connect(ui.actionLoad_Data_File, SIGNAL(triggered()), this, SLOT(main_loadFile_Slot()));
	ui.actionLoad_Data_File->setStatusTip(tr("load data"));
	//top k
	//asdf//top_k = new QAction(tr("top-10"), this);
	//asdf//top_k->setStatusTip(tr("top-10 author graph"));
	//asdf//connect(top_k, SIGNAL(triggered()), this, SLOT(main_topk_author_Slot()));
	connect(ui.actionTop_10_Authors_colored_graph, SIGNAL(triggered()), this, SLOT(main_topk_author_Slot()));
	ui.actionTop_10_Authors_colored_graph->setStatusTip(tr("top-10 author graph"));


	//animation
	//asdf//animation = new QAction(tr("Animation"), this);
	//asdf//animation->setStatusTip(tr("graph animation"));
	//asdf//connect(animation, SIGNAL(triggered()), this, SLOT(main_animation_Slot()));
	connect(ui.actionAuthor_filtering_animation, SIGNAL(triggered()), this, SLOT(main_animation_Slot()));
	ui.actionAuthor_filtering_animation->setStatusTip(tr("graph animation"));


	//저자 한명 검색
	//asdf//search_one = new QAction(tr("search one author"), this);
	//asdf//search_one->setStatusTip(tr("search one author"));
	//asdf//connect(search_one, SIGNAL(triggered()), this, SLOT(main_search_one_author_Slot()));
	connect(ui.actionSearch_one_Author, SIGNAL(triggered()), this, SLOT(main_search_one_author_Slot()));
	ui.actionSearch_one_Author->setStatusTip(tr("search one author"));

	//협업자 추천
	connect(ui.actionRecommend, SIGNAL(triggered()), this, SLOT(main_recommend_Slot()));
	ui.actionRecommend->setStatusTip(tr("recommend"));
	//저자 두명 검색
	//asdf//search_two = new QAction(tr("search two authors"), this);
	//asdf//search_two->setStatusTip(tr("search two authors"));
	//asdf//connect(search_two, SIGNAL(triggered()), this, SLOT(main_search_two_author_Slot()));
	connect(ui.actionSearch_two_Authors, SIGNAL(triggered()), this, SLOT(main_search_two_author_Slot()));
	ui.actionSearch_two_Authors->setStatusTip(tr("search two authors"));

}
//메뉴 생성
void graph_simulation::createMenu() {
	//file 메뉴생성
	//file 메뉴에 load_File액션 추가
	//asdf//fileMenu = menuBar()->addMenu(tr("file"));
	//asdf//fileMenu->addAction(load_File);

	//function 메뉴생성
	//function 메뉴에 top-k액션 추가
	//asdf//functionMenu = menuBar()->addMenu(tr("function"));
	//asdf//functionMenu->addAction(top_k);
	//asdf//functionMenu->addAction(animation);

	//search메뉴를 function메뉴에 추가
	//search메뉴에 search_one, search_two 액션 추가
	//asdf//searchMenu = functionMenu->addMenu(tr("search"));
	//asdf//searchMenu->addAction(search_one);
	//asdf//searchMenu->addAction(search_two);


	
}


//액션을 클릭했을 때 반응하는 슬롯
//각 액션에 해당하는 새 창을 보여준다
void graph_simulation::main_loadFile_Slot() {
	string fileName = COAUTHORSHIP_FILENAME + ".txt";

	ifstream fin(fileName);
	graph = new Graph(read_coauthor_graph(fin));

	lw->show(*graph,g_edges_list);
	QMessageBox::information(this, "Load data status", "Load complete!");
}

void graph_simulation::main_topk_author_Slot() {
	tkw->show(*graph, g_vertex_weight, g_edges_list);
}
void graph_simulation::main_search_one_author_Slot() {
	QString qname;
	depth = QInputDialog::getInt(this, "input", "Input depth(2~10)", 2, 2, 10);
	qname = QInputDialog::getText(this, "input", "Input Autohr name");
	inputName = qname.toStdString().c_str();


	Sow->show(*graph, g_node_ids, g_edges_indexes, depth, g_edges_list, inputName);
}
void graph_simulation::main_search_two_author_Slot() {
	QString qname1 = QInputDialog::getText(this, "input source", "Input Source Autohr name");
	QString qname2 = QInputDialog::getText(this, "input destination", "Input Destination Autohr name");
	string inputSourceName = qname1.toStdString().c_str();
	string inputDestinationName = qname2.toStdString().c_str();
	bool check = false;
	//bimap에서 저자의 이름을 찾고 있으면 해당 위치의 iterator반환, 없으면 end()반환
	auto sourceName_iter = g_node_ids.left.find(inputSourceName);
	auto DestinationName_iter = g_node_ids.left.find(inputDestinationName);

	//시작,목표 노드(저자)가 bimap에 있으면 해당 인덱스를 저장한다
	if ((sourceName_iter != g_node_ids.left.end()) && (DestinationName_iter != g_node_ids.left.end())) {
		sourseIndex = sourceName_iter->second;
		desindex = DestinationName_iter->second;
		check = true;
	}

	if (!check){
		QMessageBox::information(this, "error", "can't find author!");
	return;
	}

	else
	Stw->show(*graph, g_node_ids, g_edges_weight, g_edges_list, sourseIndex, desindex);
}


void graph_simulation::main_animation_Slot() {
	ani->show(*graph, g_node_ids, g_edges_weight, g_edges_list);
}

void  graph_simulation::main_recommend_Slot() {
	QString qname;
	qname = QInputDialog::getText(this, "input", "Input Autohr name");
	inputName = qname.toStdString().c_str();
	rc->recommendCoauthor(*graph, g_node_ids, g_edges_indexes, 3, g_edges_list, inputName);
}


Graph graph_simulation::read_coauthor_graph(std::ifstream& in)  throw(std::exception) {
	std::string line;
	vector<std::string> tokens;

	vector<pair<string, string>> edges_list;
	new_bm_type new_node_ids;

	vector<simple_edge> edges_indexes;	//int로 변환된 edge
	vector<int> edges_weight;			//edge weight vector
	vector<int> vertex_weight;			//vertex(author)의 논문수

	//qDebug() << "* graph reading start";
	ui.label_dataStatus->append("* graph reading start");
	//한 줄씩 읽어서 Parse
	while (std::getline(in, line) && !line.empty()) {
		//boost::split 이용해 문자열 분리
		//tokens[0]: Author1
		//tokens[1]: Author2

		boost::split(tokens, line, boost::is_any_of("||"), boost::token_compress_on);

		const string& author1 = tokens[0];
		const string& author2 = tokens[1];
		pair<string, int> temp;

		auto it_author1 = new_node_ids.left.find(author1);
		auto it_author2 = new_node_ids.left.find(author2);


		//author1, author2를 찾아보고 없으면 new_node_ids에 추가하고 vertex_weight에 1 푸쉬백
		//있으면 해당 vertex_weight[인덱스]++; >> weight++

		if (it_author1 == new_node_ids.left.end()) {
			new_node_ids.insert(new_bm_type::value_type(author1, node_cnt++));
			vertex_weight.push_back(1);
		}
		else {
			vertex_weight[it_author1->second]++;
		}

		if (it_author2 == new_node_ids.left.end()) {
			new_node_ids.insert(new_bm_type::value_type(author2, node_cnt++));
			vertex_weight.push_back(1);
		}

		else {
			vertex_weight[it_author2->second]++;
		}


		bool check = false;
		int index = 0;
		//edges 중복검사후 삽입
		//중복된것이 없으면 false
		//있으면 true
		for (auto i = edges_list.begin(); i < edges_list.end(); ++i) {
			if (i->first == author1 && i->second == author2)
			{
				check = true; break;
			}
			if (i->first == author2 && i->second == author1)
			{
				check = true; break;
			}
			index++;
		}
		//중복된것이 없으면
		//edges_list에 푸쉬백
		//edges_weight에 1 푸쉬백
		if (!check) {
			edges_list.push_back(pair<string, string>(author1, author2));
			edges_weight.push_back(1);
		}
		//중복된것이 있으면
		//edges_weight[index]에 추가!
		else
			edges_weight[index]++;


		//qDebug() << node_cnt << endl;
		/*ui.label_dataStatus->append(QString::fromStdString(to_string(node_cnt)));
		statuscursor = ui.label_dataStatus->cursorForPosition(ui.label_dataStatus->pos());*/



		//NODE_LIMIT에 걸리면 break
		if (node_cnt > NODE_LIMIT) break;
	}

	//qDebug() << "* graph reading complete";
	//qDebug() << "* # of nodes: " << node_cnt;
	//qDebug() << "* # of edges: " << edges_list.size();
	ui.label_dataStatus->append("* graph reading complete\n");
	ui.label_dataStatus->append("* number of nodes: "+ QString::fromStdString(to_string(node_cnt)));
	ui.label_dataStatus->append("* number of edges: "+ QString::fromStdString(to_string(edges_list.size())));
	ui.label_dataStatus->append("\n\n");
	//ui.label_dataStatus->setText(loaddata);
	//ui.label_dataStatus->moveCursor(QTextCursor::End);
	statuscursor = ui.label_dataStatus->cursorForPosition(ui.label_dataStatus->pos());


	//vertex정보
	//qDebug() << "**************node info print*******************" << endl;
	ui.label_dataStatus->append("<node info>");
	int paper_index = 0;
	for (auto it = new_node_ids.begin(); it != new_node_ids.end(); ++it) {
		//qDebug() << paper_index<< "name : " << it->left.c_str() << " index :" << it->right << " paper :" << vertex_weight[paper_index] << endl;
		
		ui.label_dataStatus->append("index :"+ QString::fromStdString(to_string(paper_index)));
		ui.label_dataStatus->append("name  : " + QString::fromStdString(it->left.c_str()));
		ui.label_dataStatus->append("index : " + QString::fromStdString(to_string(it->right)));
		ui.label_dataStatus->append("paper : " + QString::fromStdString(to_string(vertex_weight[paper_index])));

		paper_index++;
	}

	//qDebug() << "**************node info print end****************" << endl;
	ui.label_dataStatus->append("</node info>");
	statuscursor = ui.label_dataStatus->cursorForPosition(ui.label_dataStatus->pos());



	//edge정보
	//qDebug() << "**************edge info print ****************" << endl;
	ui.label_dataStatus->append("<edge info>");

	for (int i = 0; i < edges_list.size(); i++) {
		//qDebug() << i << "   " << edges_list[i].first.c_str() << "-------" << edges_list[i].second.c_str() << "   weight" << edges_weight[i] << endl;
		//ui.label_dataStatus->append(QString::fromStdString(to_string(i))+". ");
		ui.label_dataStatus->append("\n");
		ui.label_dataStatus->append(QString::fromStdString(edges_list[i].first.c_str()) +"-" + edges_list[i].second.c_str());
		ui.label_dataStatus->append("weight : " + QString::fromStdString(to_string(edges_weight[i])));
		statuscursor = ui.label_dataStatus->cursorForPosition(ui.label_dataStatus->pos());

	}

	//qDebug() << "**************edge info print end****************" << endl;
	ui.label_dataStatus->append("</edge info> \n");
	std::cout << endl<<endl;

	ui.label_dataStatus->append("* # of nodes: " + QString::fromStdString(to_string(node_cnt)));
	ui.label_dataStatus->append("* # of edges: "+ QString::fromStdString(to_string(edges_list.size())));
	statuscursor = ui.label_dataStatus->cursorForPosition(ui.label_dataStatus->pos());



	//<string, string> : edges_list to <int, int> : edges_indexes
	//using boost::bimap (bidirectional map)
	//edges_list vector에 있는 first,second는 author의 이름이다
	//author의 이름을 node_ids bi_map에서 찾고 그 인덱스<int>를 받아온다
	for (auto edge : edges_list) {
		edges_indexes.push_back({
			new_node_ids.left.find(edge.first)->get_right(),
			new_node_ids.left.find(edge.second)->get_right()
		});
	}
	//Graph --> defined in "Graph.h"
	Graph graph(edges_indexes.begin(), edges_indexes.end(), new_node_ids.size());





	//set index property
	ui.label_dataStatus->append("* set vertex property start");
	

	vertex_iterator vi, vi_end;
	int i = 0;
	//vertex property를 설정
	//vertex_index(저자 인덱스), vertex_name(저자 이름), vertex_color(저자노드의 색)
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		boost::put(vertex_index, graph, *vi, i);
		boost::put(vertex_name, graph, *vi, new_node_ids.right.find(i)->get_left());
		boost::put(vertex_color, graph, *vi, Qt::black);
		boost::put(vertex_priority, graph, *vi, vertex_weight[i]);
		++i;
	}

	vertex_name_Map vertexName = get(vertex_name, graph);

	ui.label_dataStatus->append("* set vertex property end");

	edge_iterator ei, ei_end;


	//edge property를 설정
	//edge_weight(공저 횟수), edge_color(엣지 색), edge_index(엣지 인덱스)
	int num = 0;
	for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
		boost::put(edge_weight, graph, *ei, edges_weight[num]);
		boost::put(edge_color, graph, *ei, Qt::black);
		boost::put(edge_index, graph, *ei, num);
		num++;
	}

	
	//graph layout calculation
	//using boost::random_graph_layout and boost::kamada_kawai_spring_layout
	//vertex마다 계산된 좌표를 property에 적용
	//예제 코드: http://www.boost.org/doc/libs/1_63_0/libs/graph/test/layout_test.cpp
	//(-> 콘솔 기반)
	ui.label_dataStatus->append("* make graph layout start");

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
		random_graph_layout(graph, get(vertex_position, graph), rect_top);
		break;

	case GRAPH_LAYOUT::CIRCLE_LAYOUT:
		circle_graph_layout(graph, get(vertex_position, graph), SCREEN_SIZE / 2);
		break;
	case GRAPH_LAYOUT::FRUCHTERMAN_REINGOLD_LAYOUT:
		fruchterman_reingold_force_directed_layout(graph,
			get(vertex_position, graph),
			topology,
			attractive_force(square_distance_attractive_force())
			.cooling(linear_cooling<double>(50))
		);
		break;
	}
	ui.label_dataStatus->append("* make graph layout end");

	g_node_ids = new_node_ids;
	g_edges_indexes = edges_indexes;
	g_edges_weight = edges_weight;
	g_edges_list = edges_list;
	g_vertex_weight = vertex_weight;

	return graph;
}


//스트림데이터 추가======================================================================================================graph_simulation

void graph_simulation::dataStreamConfirmBtn_clicked() {
	if (ui.radioBtn_streamOn->isChecked()) {
		ui.label_dataStatus->clear();
		ui.label_dataStatus->append("datastream on!!");

		countdown = 5;
		streamTimer->start(1000);

	}
	else if (ui.radioBtn_streamOff->isChecked()) {
		ui.label_dataStatus->append("datastream off!!");
		streamTimer->stop();
	}
}

void graph_simulation::tictoc_Slot() {
	streamTimer->stop();

	if (countdown > 0) {
		countdown--;
		//ui.streamInfo->
		ui.label_dataStatus->append(QString::fromStdString(to_string(countdown)));
		streamTimer->start(1000);

		//5초 쉴동안 각 기능 새로그리기
		tkw->show(*graph, g_vertex_weight, g_edges_list);
		Sow->show(*graph, g_node_ids, g_edges_indexes, depth, g_edges_list,inputName);
		Stw->show(*graph, g_node_ids, g_edges_weight, g_edges_list, sourseIndex,desindex);
		ani->show(*graph, g_node_ids, g_edges_weight, g_edges_list);
		rc->recommendCoauthor(*graph, g_node_ids, g_edges_indexes, 3, g_edges_list, inputName);
	}
	else {
		//qDebug() << "thread run loadbythread";
		countdown = 9999999;
		//streamObj.threadingSetup(streamTrd);
		//streamObj.moveToThread(&streamTrd);

		streamTrd.start();
		//여기서 thread가 수행
		streamTrd.quit();
		streamTrd.wait();
		//쓰레드가 끝나고 GraphData컨테이너에 원하는 자료를 다 로드한 후
		//graph_simulation객체에 읽은 데이터를 옮긴다.
		//dataPorting();
		//데이터를 다 읽어온 후 카운트다운 초기화&타이머 재시작
		delete graph;

		graph = new Graph(g_edges_indexes.begin(), g_edges_indexes.end(), g_node_ids.size());





		//set index property
		ui.label_dataStatus->append("* set vertex property start");


		vertex_iterator vi, vi_end;
		int i = 0;
		//vertex property를 설정
		//vertex_index(저자 인덱스), vertex_name(저자 이름), vertex_color(저자노드의 색)
		for (tie(vi, vi_end) = vertices(*graph); vi != vi_end; ++vi) {
			boost::put(vertex_index, *graph, *vi, i);
			boost::put(vertex_name, *graph, *vi, g_node_ids.right.find(i)->get_left());
			boost::put(vertex_color, *graph, *vi, Qt::black);
			boost::put(vertex_priority, *graph, *vi, g_vertex_weight[i]);
			++i;
		}

		vertex_name_Map vertexName = get(vertex_name, *graph);

		ui.label_dataStatus->append("* set vertex property end");

		edge_iterator ei, ei_end;


		//edge property를 설정
		//edge_weight(공저 횟수), edge_color(엣지 색), edge_index(엣지 인덱스)
		int num = 0;
		for (boost::tie(ei, ei_end) = edges(*graph); ei != ei_end; ++ei) {
			boost::put(edge_weight, *graph, *ei, g_edges_weight[num]);
			boost::put(edge_color, *graph, *ei, Qt::black);
			boost::put(edge_index, *graph, *ei, num);
			num++;
		}


		//graph layout calculation
		//using boost::random_graph_layout and boost::kamada_kawai_spring_layout
		//vertex마다 계산된 좌표를 property에 적용
		//예제 코드: http://www.boost.org/doc/libs/1_63_0/libs/graph/test/layout_test.cpp
		//(-> 콘솔 기반)
		ui.label_dataStatus->append("* make graph layout start");

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
			random_graph_layout(*graph, get(vertex_position, *graph), rect_top);
			break;

		case GRAPH_LAYOUT::CIRCLE_LAYOUT:
			circle_graph_layout(*graph, get(vertex_position, *graph), SCREEN_SIZE / 2);
			break;
		case GRAPH_LAYOUT::FRUCHTERMAN_REINGOLD_LAYOUT:
			fruchterman_reingold_force_directed_layout(*graph,
				get(vertex_position, *graph),
				topology,
				attractive_force(square_distance_attractive_force())
				.cooling(linear_cooling<double>(50))
			);
			break;
		}
		ui.label_dataStatus->append("* make graph layout end");






		if (!streamTrd.isRunning()) {
			streamTrd.terminate();
			ui.label_dataStatus->append("timer restart");
			countdown = 5;
			streamTimer->start(1000);

		}
	}
}

//void graph_simulation::dataPorting() {
//	addGraph = streamObj.getData();
//
//	graph = addGraph->t_coauthorGraph;
//	g_node_ids = *addGraph->t_node_ids;
//	g_edges_indexes = *addGraph->t_edges_indexes;
//	g_edges_weight = *addGraph->t_edges_weight;
//	g_edges_list = *addGraph->t_edges_list;
//	g_vertex_weight = *addGraph->t_vertex_weight;
//}

//스트림데이터 추가==============================================================================================streamObject
streamObject::streamObject(GraphData* initdata) {
	filenum = 1;
	totalfilenum = 5;

	gphData = initdata;
}

void streamObject::load_stream_data() {
	string fileName = COAUTHORSHIP_FILENAME + to_string(filenum) + ".txt";
	ifstream fin(fileName);
	gphData->t_coauthorGraph = &read_coauthor_graph(fin);
	filenum++;

	return;
}

Graph streamObject::read_coauthor_graph(std::ifstream& in)  throw(std::exception) {
	std::string line;
	vector<std::string> tokens;

	vector<pair<string, string>> *edges_list = gphData->t_edges_list;
	new_bm_type *new_node_ids = gphData->t_node_ids;

	vector<simple_edge> *edges_indexes = gphData->t_edges_indexes;	//int로 변환된 edge
	vector<int> *edges_weight = gphData->t_edges_weight;			//edge weight vector
	vector<int> *vertex_weight = gphData->t_vertex_weight;			//vertex(author)의 논문수
	int* node_cnt = gphData->t_node_cnt;

	qDebug() << "* graph reading start";


	//한 줄씩 읽어서 Parse
	while (std::getline(in, line) && !line.empty()) {
		//boost::split 이용해 문자열 분리
		//tokens[0]: Author1
		//tokens[1]: Author2

		boost::split(tokens, line, boost::is_any_of("||"), boost::token_compress_on);

		const string& author1 = tokens[0];
		const string& author2 = tokens[1];
		pair<string, int> temp;

		auto it_author1 = new_node_ids->left.find(author1);
		auto it_author2 = new_node_ids->left.find(author2);


		//author1, author2를 찾아보고 없으면 new_node_ids에 추가하고 vertex_weight에 1 푸쉬백
		//있으면 해당 vertex_weight[인덱스]++; >> weight++

		if (it_author1 == new_node_ids->left.end()) {
			new_node_ids->insert(new_bm_type::value_type(author1, (*node_cnt)++));
			vertex_weight->push_back(1);
		}
		else {
			(*vertex_weight)[it_author1->second]++;
		}

		if (it_author2 == new_node_ids->left.end()) {
			new_node_ids->insert(new_bm_type::value_type(author2, (*node_cnt)++));
			vertex_weight->push_back(1);
		}

		else {
			(*vertex_weight)[it_author2->second]++;
		}


		bool check = false;
		int index = 0;
		//edges 중복검사후 삽입
		//중복된것이 없으면 false
		//있으면 true
		for (auto i = edges_list->begin(); i < edges_list->end(); ++i) {
			if (i->first == author1 && i->second == author2)
			{
				check = true; break;
			}
			if (i->first == author2 && i->second == author1)
			{
				check = true; break;
			}
			index++;
		}
		//중복된것이 없으면
		//edges_list에 푸쉬백
		//edges_weight에 1 푸쉬백
		if (!check) {
			edges_list->push_back(pair<string, string>(author1, author2));
			edges_weight->push_back(1);
		}
		//중복된것이 있으면
		//edges_weight[index]에 추가!
		else
			(*edges_weight)[index] = (*edges_weight)[index] + 1;


		qDebug() << *node_cnt << endl;

	}

	qDebug() << "* graph reading complete";
	qDebug() << "* # of nodes: " << *node_cnt;
	qDebug() << "* # of edges: " << edges_list->size();


	//vertex정보
	qDebug() << "**************node info print*******************" << endl;

	int paper_index = 0;
	for (auto it = new_node_ids->begin(); it != new_node_ids->end(); ++it) {
		qDebug() << paper_index << "name : " << it->left.c_str() << " index :" << it->right << " paper :" << (*vertex_weight)[paper_index] << endl;
		paper_index++;
	}

	qDebug() << "**************node info print end****************" << endl;



	//edge정보
	qDebug() << "**************edge info print ****************" << endl;
	for (int i = 0; i < edges_list->size(); i++)
		qDebug() << i << "   " << (*edges_list)[i].first.c_str() << "-------" << (*edges_list)[i].second.c_str() << "   weight" << (*edges_weight)[i] << endl;
	qDebug() << "**************edge info print end****************" << endl;

	std::cout << endl << endl;

	qDebug() << "* # of nodes: " << *node_cnt;
	qDebug() << "* # of edges: " << edges_list->size()<<endl;
	qDebug() << edges_weight->size() << endl;
	qDebug() << edges_indexes->size() << endl;


	//<string, string> : edges_list to <int, int> : edges_indexes
	//using boost::bimap (bidirectional map)
	//edges_list vector에 있는 first,second는 author의 이름이다
	//author의 이름을 node_ids bi_map에서 찾고 그 인덱스<int>를 받아온다
	edges_indexes->clear();
	for (auto edge : *edges_list) {
		edges_indexes->push_back({
			new_node_ids->left.find(edge.first)->get_right(),
			new_node_ids->left.find(edge.second)->get_right()
		});
	}
	//Graph --> defined in "Graph.h"
	Graph graph(edges_indexes->begin(), edges_indexes->end(), new_node_ids->size());





	//set index property
	qDebug() << "* set vertex property start";


	vertex_iterator vi, vi_end;
	int i = 0;
	//vertex property를 설정
	//vertex_index(저자 인덱스), vertex_name(저자 이름), vertex_color(저자노드의 색)
	for (boost::tie(vi, vi_end) = vertices(graph); vi != vi_end; ++vi) {
		boost::put(vertex_index, graph, *vi, i);
		boost::put(vertex_name, graph, *vi, new_node_ids->right.find(i)->get_left());
		boost::put(vertex_color, graph, *vi, Qt::black);
		boost::put(vertex_priority, graph, *vi, (*vertex_weight)[i]);
		++i;
	}

	vertex_name_Map vertexName = get(vertex_name, graph);

	qDebug() << "* set vertex property end";

	edge_iterator ei, ei_end;


	//edge property를 설정
	//edge_weight(공저 횟수), edge_color(엣지 색), edge_index(엣지 인덱스)
	int num = 0;
	for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
		if (num == 98)
			qDebug() << "num==98" << endl;
		boost::put(edge_weight, graph, *ei, (*edges_weight)[num]);
		boost::put(edge_color, graph, *ei, Qt::black);
		boost::put(edge_index, graph, *ei, num);
		num++;
	}


	//graph layout calculation
	//using boost::random_graph_layout and boost::kamada_kawai_spring_layout
	//vertex마다 계산된 좌표를 property에 적용
	//예제 코드: http://www.boost.org/doc/libs/1_63_0/libs/graph/test/layout_test.cpp
	//(-> 콘솔 기반)
	qDebug() << "* make graph layout start";

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
		random_graph_layout(graph, get(vertex_position, graph), rect_top);
		break;

	case GRAPH_LAYOUT::CIRCLE_LAYOUT:
		circle_graph_layout(graph, get(vertex_position, graph), SCREEN_SIZE / 2);
		break;
	case GRAPH_LAYOUT::FRUCHTERMAN_REINGOLD_LAYOUT:
		fruchterman_reingold_force_directed_layout(graph,
			get(vertex_position, graph),
			topology,
			attractive_force(square_distance_attractive_force())
			.cooling(linear_cooling<double>(50))
		);
		break;
	}
	qDebug() << "* make graph layout end";

	gphData->t_node_ids = new_node_ids;
	gphData->t_edges_indexes = edges_indexes;
	gphData->t_edges_weight = edges_weight;
	gphData->t_edges_list = edges_list;
	gphData->t_vertex_weight = vertex_weight;

	return graph;
}

void streamObject::threadingSetup(QThread &trd) {
	connect(&trd, SIGNAL(started()), this, SLOT(loadByThread_Slot()));
}

void streamObject::loadByThread_Slot() {
	if (filenum < totalfilenum) {
		load_stream_data();
	}
	return;
}
