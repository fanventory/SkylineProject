#include "ConnectTable.cpp"

//  g++ main.cpp -o kosa
int main() {

	string edgeFile = "/home/zhangzf/program/SPSLGraph/data/DBpediaVB/edgeDBpediaVB.txt";
	/*
	string edgeFile="/home/zhangzf/program/SPSLGraph/0809/data/edge.txt";
	*/
	Digraph G;
	G.readGraph(edgeFile);
	Kosaraju kosa(G);	//	计算强连通分量
	cout << "V:" << G.getV() << endl;
	cout << "connect:" << kosa.getCount() << endl;
	// kosa.write("./kosa.csv",G.getV());
	//	筛除掉连通分量为1的结点，并将剩余结点聚类，以索引形式存储
	ConnectTable conTable(kosa.getMap(), kosa.getCount());	
	conTable.write("../skylineRun/conTable.csv");
	return 0;
}