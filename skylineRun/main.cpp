#include "SPS.cpp"
#include "TL_pre_processing.cpp"
#pragma once

void show(int &v) { cout << v << ","; }

int main(int argc, char **argv) {
	// DBpediaVB 数据集
	
	string edgeFile="/home/zhangzf/program/SPSLGraph/data/DBpediaVB/edgeDBpediaVB.txt";
	string keywordFile="/home/zhangzf/program/SPSLGraph/data/DBpediaVB/nidKeywordsListMapDBpediaVB.txt";
	string pidCoordFile="/home/zhangzf/program/SPSLGraph/data/DBpediaVB/pidCoordDBpediaVB.txt";
	string SLFileName="/home/zhangzf/program/SPSLGraph/db/SLdb";
	string SPFileName="/home/zhangzf/program/SPSLGraph/db/SPdb";
	string conTableFileName="./conTable.csv";
	
	// 测试数据集
	/*
	string edgeFile="../data/edge.txt";
	string keywordFile="../data/keyword.txt";
	string pidCoordFile="../data/coordinate.txt";
	string SLFileName="../db/TLdb";
	string SPFileName="../db/TPdb";
	*/
	bool build=false;	// 判断命令中是否存在参数-build
	// 获取需要查询的关键字(通过命令行获取）
	vector<int> query;
	for (int i = 1; i < argc; i++) {
		if(strcmp("-build", argv[i]) == 0) {
			build=true;
			cout<<"执行了-build命令"<<endl;
		}else{
			query.push_back(atoi(argv[i]));
		}
	}
	// 获取需要查询的关键字（通过文件获取）
	/* 
	if(argv[i]=="-build"){
		build=true;
		cout<<"执行了-build命令"<<endl;
	}
	vector<string> queryStr = Util::readFile("./query.txt");	// 换行作为分隔符
	for (vector<string>::iterator it = queryStr.begin(); it < queryStr.end(); it++) {
		query.push_back(stoi(*it));
	}
	*/
	// 准备工作
	if(build){
		TL_pre_file tpf;
		tpf.readGraph(edgeFile, keywordFile,conTableFileName);	//	读取图，并对强连通分量进行处理
		tpf.write("./data.txt");	// 输出转化后的图（用于TL_LABEL预处理）
		// TL_LABEL预处理
		char filename[64], resfilename[64];
		strcpy(filename, "./data.txt");
		strcpy(resfilename, "../index/p2p_scc");
		pre_processing(filename,resfilename);
	}
	cout<<1<<endl;
	//	读取图
	Graph graph=Graph::getInstance();
	// 将关键字转化为图中的节点
	graph.readGraph(edgeFile, keywordFile,conTableFileName);
	 cout<<2<<endl;
	// *****第一次运行需要执行写入，将index写入硬盘中***** //

	// 准备工作结束

	/*******************测试部分***********************/
	/*******************随机获取三个关键词，求skyline***********************/
		/*
	unsigned seed;
	vector<double> runtimes;
	//	获取关键词序列
	vector<int> KL=graph.getKeyList();
	//	获取关键词序列的长度
	int KLS=graph.getKeyListSize();
	//	循环n次
	for(int i=0;i<10;i++){
		Leveldb ldb;
		//	清空query队列
		query.clear();
		//	设置随机数种子
		seed = time(0);
		srand(seed);
		cout<<"KLS :"<<KLS<<endl;
		//	从关键词序列中随机取三个数
		cout << "关键词：";
		for(int j=0;j<3;j++){
			int queryEl=KL[rand() % KLS ];
			query.push_back(queryEl);
			cout <<queryEl<<" ";
		}
		cout <<endl;
		
		vector<KeyRow> queryRes= ldb.SLGet(query,SLFileName);
		SPS sps;
		sps.init(queryRes,&graph);	// 初始化
		clock_t startTime,endTime;	// 计时
		startTime = clock();	//计时开始
		vector<int> Skyline=sps.SPS_calculate(query,SPFileName);	// 执行sps算法
		endTime = clock();	//计时结束
		double runtime=(double)(endTime - startTime) / CLOCKS_PER_SEC;
		runtimes.push_back(runtime);
		cout << "The run time is: " << runtime << "s" << endl;
		cout<<"skyline Size is : "<<Skyline.size();
		cout<<endl<<"=================================================================================="<<endl;
	}
	//	计算平均时间
	cout<<"The mean time is :"<<accumulate(runtimes.begin(),runtimes.end(),0.0)/runtimes.size()<<endl;
	*/
	
	/*******************测试部分***********************/
	
	

	Leveldb ldb;
	vector<KeyRow> queryRes= ldb.SLGet(query,SLFileName);	// 从SLdb中获取关键字对应的倒排索引组
	 cout<<5<<endl;
	SPS sps;
	// 将倒排序列读入数据结构中
	sps.init(queryRes,&graph);	// 初始化
	 cout<<6<<endl;
	clock_t startTime,endTime;	// 计时
	startTime = clock();//计时开始
	vector<int> Skyline=sps.SPS_calculate(query,SPFileName);	// 执行sps算法
	endTime = clock();//计时结束
	cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
  cout<<"skyline is : ";
	for_each(Skyline.begin(), Skyline.end(), show);	// 显示Skyline结果
   cout<<endl<<endl;


	return 0;
}
