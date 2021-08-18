#include "Leveldb.cpp"

int main()
{
	/***************  begin  *****************/
	// DBpediaVB 数据集
	/*
	string edgeFile="/home/zhangzf/program/SPSLGraph/data/DBpediaVB/edgeDBpediaVB.txt";
	string keywordFile="/home/zhangzf/program/SPSLGraph/data/DBpediaVB/nidKeywordsListMapDBpediaVB.txt";
	string pidCoordFile="/home/zhangzf/program/SPSLGraph/data/DBpediaVB/pidCoordDBpediaVB.txt";
	string SLFileName="/home/zhangzf/program/SPSLGraph/db/SLdb";
	string SPFileName="/home/zhangzf/program/SPSLGraph/db/SPdb";
	*/
	// 测试数据集
	string edgeFile="../data/edge.txt";
	string keywordFile="../data/keyword.txt";
	string pidCoordFile="../data/coordinate.txt";
	string SLFileName="../db/TLdb";
	string SPFileName="../db/TPdb";
	
  	vector<string> fileNames;
	fileNames.push_back(edgeFile);
	fileNames.push_back(keywordFile);
 	fileNames.push_back(pidCoordFile);
	// 计算最大节点数
	int nodeNum = Util::getMaxNodeNum(fileNames) + 1;
	Graph* graph = new Graph(nodeNum);
 	cout<< "the max num of graph is"<< nodeNum <<endl;
	// 读取边数据集文件
	vector<string> rows = Util::readFile(edgeFile);
  	cout<< "get text edgeDBpediaVB accomplish!" <<endl;
	// 构建图的点和边
	graph->createGraph(rows);
 	cout<< "build graph accomplish!" <<endl;
	// 读取nidKeywordsListMapYagoVB文件
	rows = Util::readFile(keywordFile);
  	cout<< "get text nidKeywordsListMapDBpediaVB accomplish!" <<endl;
	// 构建图的关键词信息
	graph->createKeys(rows);
  	cout<< "build graph`s keyword accomplish!" <<endl;
	// 读取pidCoordYagoVB文件
	rows = Util::readFile(pidCoordFile);
  	cout<< "get text pidCoordDBpediaVB accomplish!" <<endl;
  	// 构建图的坐标信息
	graph->createCoordinate(rows);
 	cout<< "build graph`s Coord accomplish!" <<endl;
	// 输出图数据
	//graph->showGraph();
	// 构建SPSkyline对象
	SPSkyline* spskyline= new SPSkyline();
	// 初始化
	spskyline->init(rows);
  	cout<< "spskyline init accomplish!" <<endl;
	// 计算带关键字最短路径树
	spskyline->calculate(*graph);
  	cout<< "spskyline calculate accomplish!" <<endl;
	//	输出语义节点信息
	// spskyline->show();
  	// 将运行的中间结果写入文件
  	// spskyline->write("/home/zhangzf/program/SPSLGraph/0616/spskyline.txt");
	// spskyline->read("/home/zhangzf/program/SPSLGraph/0616/test.txt","/home/zhangzf/program/SPSLGraph/db/TESTPdb");
  	// cout<<"spskyline read accomplish!" <<endl;
  	// spskyline->show();
  	// 构建Table对象
	Table *table = new Table();
 	 cout<< "table init accomplish!" <<endl;
	// 生成倒排索引
	table->calculate(*spskyline);
	cout<< "table calculate accomplish!" <<endl;
	// 输出倒排索引信息
	// table->show();
	// 将倒排索引信息写入文件
	// 构建Leveldb对象
	Leveldb* leveldb = new Leveldb();
	// 将倒排索引信息写入文件
	leveldb->writeSL(*table,SLFileName);
  	cout<<"write into SL db accomplsh!"<< endl;
  	leveldb->writeSP(*spskyline,SPFileName);
  	cout<<"write into SP db accomplsh!"<< endl;

	return 0;

   
   
}

