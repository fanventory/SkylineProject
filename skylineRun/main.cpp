#include "SPS.cpp"
#include "TL_pre_processing.cpp"
#pragma once

void show(int &v) { cout << v << ","; }

int main(int argc, char **argv) {
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
	Graph graph=Graph::getInstance();
	// 将关键字转化为图中的节点
	graph.transformGraph(edgeFile, keywordFile);
	cout<<2<<endl;
	// *****第一次运行需要执行写入，将index写入硬盘中***** //
	if(build){
		graph.write("./data.txt");	// 输出转化后的图（用于TL_LABEL预处理）
		cout<<3<<endl;
		// TL_LABEL预处理
		char filename[64], resfilename[64];
		strcpy(filename, "./data.txt");
		strcpy(resfilename, "../index/p2p_scc");
		pre_processing(filename,resfilename);
		cout<<4<<endl;
	}
	// 准备工作结束
	
	Leveldb ldb;
	vector<KeyRow> queryRes= ldb.SLGet(query,SLFileName);	// 从SLdb中获取关键字对应的倒排索引组
	cout<<5<<endl;
	SPS sps;
	// 将倒排序列读入数据结构中
	sps.init(queryRes);	// 初始化
	cout<<6<<endl;
	clock_t startTime,endTime;	// 计时
	startTime = clock();//计时开始
	vector<int> Skyline=sps.SPS_calculate(query,SPFileName);	// 执行sps算法
	endTime = clock();//计时结束
	cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	for_each(Skyline.begin(), Skyline.end(), show);	// 显示Skyline结果
	cout<<endl<<7<<endl;
	return 0;
}
