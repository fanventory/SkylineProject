//	根据kosaraju算法的计算结果，筛除不是连通分量的点
#include "Kosaraju.cpp"

class ConnectTable
{
private:
	map<int, int> table;
public:
	ConnectTable(map<int, int> origin,int n) {
		int *groups = (int*)malloc(sizeof(int) * (n + 1));
		memset(groups, 0, sizeof(int) * (n + 1));	//	初始化为0
		for (map<int, int>::iterator it = origin.begin(); it != origin.end(); it++) {
			groups[(*it).second]++;	//	对每个连通分量的节点数做一个计数
		}
		map<int, vector<int>> conList;
		for (map<int, int>::iterator it = origin.begin(); it != origin.end(); it++) {
			if (groups[(*it).second] > 1) {
				if (conList.find((*it).second) == conList.end()) {	//	创建字典条目
					conList[(*it).second] = vector<int>();
				}
				conList[(*it).second].push_back((*it).first);
			}
		}
		for (map<int, vector<int>>::iterator it = conList.begin(); it != conList.end(); it++) {
			int virtualNode=(*it).second.front();	//	将第一个结点作为聚类后的虚拟节点，指向其他强连通的结点
			for (vector<int>::iterator it_inner = (*it).second.begin(); it_inner != (*it).second.end(); it_inner++) {
				this->table[(*it_inner)] = virtualNode;
			}
		}
	}
	map<int, int> getTable() {
		return this->table;
	}
	void write(string fileName) {
		ofstream outfile;
		outfile.open(fileName.data());   // 将文件流对象与文件连接起来 
		assert(outfile.is_open());   // 若失败,则输出错误消息,并终止程序运行

		for (map<int, int>::iterator it = this->table.begin(); it != this->table.end(); it++) {
			outfile << (*it).first << "," << (*it).second << endl;
		}
		outfile.close();
	}
};
