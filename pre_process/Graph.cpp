#include "Util.cpp"

class Graph {
private:
	vector<Node> nodes;	// 节点列表
	int nodeNum;	// 节点数量
	int edgeNum;	// 边数量
public:
	// 无参构造函数,rowNum为默认值
	Graph() {
		this->edgeNum = 0;
		this->nodeNum = 0;
		this->nodes.resize(rowNum);
	}
	// 有参构造函数，n为节点数
	Graph(int n) {
		this->edgeNum = 0;
		this->nodeNum = 0;
		this->nodes.resize(n);
	}
	~Graph() {
		for (vector<Node>::iterator it = this->nodes.begin(); it < this->nodes.end(); it++)
		{
			(*it).edge.~vector();
			(*it).keyword.~vector();
		}
		this->nodes.~vector();
	}
	// 返回节点列表
	vector<Node> getNodes() {
		return this->nodes;
	}
	// 插入单个图的点
	void insertSingleNode(int node) {
		this->nodes[node].isExist = true;
	}
	// 插入单个图的边
	void insertSingleEdge(int begin, int end) {
		// 实现按顺序插入，由二分查找找出插入位置
		int i = Util::binaryFind(this->nodes[begin].edge, end);
		// 插入边信息
		this->nodes[begin].edge.insert(this->nodes[begin].edge.begin() + i, end);
	}
	// 赋值单个点的关键词
	void insertSingleKeyword(int node, int key) {
		// 实现按顺序插入，由二分查找找出插入位置
		int i = Util::binaryFind(this->nodes[node].keyword, key);
		// 插入关键词信息
		this->nodes[node].keyword.insert(this->nodes[node].keyword.begin() + i, key);
	}
	// 插入单个图的x、y坐标
	void insertSingleCoordinate(int node, double x, double y) {
		// 插入边信息
		this->nodes[node].flag = true;
		this->nodes[node].coordinate.x = x;
		this->nodes[node].coordinate.y = y;
	}
	// 插入图的点和边
	void createGraph(vector<string> fileRow) {
		for (vector<string>::iterator it = fileRow.begin(); it < fileRow.end(); it++) {
			// 按:分隔字符串
			vector<string> t = Util::split(*it, ": ");
			// first为初始点
			string first = t.front();
			// second为终点序列
			string second = t.back();
			// 将点设为存在
			this->insertSingleNode(stoi(first));
			this->nodeNum++;
			// 按,分隔字符串
			vector<string> keys = Util::split(second, ",");
			for (vector<string>::iterator it_inner = keys.begin(); it_inner < keys.end() - 1; it_inner++) {
				this->insertSingleEdge(stoi(first), stoi(*it_inner));
				this->edgeNum++;

			}
		}
	}
	// 插入节点的关键词信息
	void createKeys(vector<string> fileRow) {
		for (vector<string>::iterator it = fileRow.begin(); it < fileRow.end(); it++) {
			// 按:分隔字符串
			vector<string> t = Util::split(*it, ": ");
			// first为初始点
			string first = t.front();
			// second为关键词序列
			string second = t.back();
			// 按,分隔字符串
			vector<string> keys = Util::split(second, ",");
			for (vector<string>::iterator it_inner = keys.begin(); it_inner < keys.end() - 1; it_inner++) {
				this->insertSingleKeyword(stoi(first), stoi(*it_inner));
			}

		}
	}
	// 插入节点的坐标信息
	void createCoordinate(vector<string> fileRow) {
		for (vector<string>::iterator it = fileRow.begin(); it < fileRow.end(); it++) {
			// 按:分隔字符串
			vector<string> t = Util::split(*it, ": ");
			// first为初始点
			string first = t.front();
			// second为关键词序列
			string second = t.back();
			// 按,分隔字符串
			vector<string> Coord = Util::split(second, " ");
			string x = Coord.front();
			string y = Coord.back();
			try
			{
				this->insertSingleCoordinate(stoi(first), stod(x), stod(y));
			}
			catch (const std::exception& e)
			{
				cout << x << "," << y << endl;
			}

		}
	}
	// 显示图的邻接矩阵
	void showGraph() {
		int len = this->nodes.size();
		for (int i = 0; i < len; i++) {
			if (this->nodes[i].flag) {
				cout << "index:" << i << endl << "=====>";
				cout << "(" << this->nodes[i].coordinate.x << "," << this->nodes[i].coordinate.y << ")" << endl << "=====>";
			}
			else {
				cout << i << endl << "=====>";
			}
			vector<int> e = this->nodes[i].edge;
			for (vector<int>::iterator it = e.begin(); it < e.end(); it++) {
				cout << *it << ",";
			}
			cout << endl << "=====>";
			e = this->nodes[i].keyword;
			for (vector<int>::iterator it = e.begin(); it < e.end(); it++) {
				cout << *it << ",";
			}
			cout << endl << "----------------------------------------------------------" << endl;
		}
	}
	// 查询某关键字是否在图中
	bool iskeyExist(int node,int key) {
		for (vector<int>::iterator it = this->nodes[node].keyword.begin(); it < this->nodes[node].keyword.end(); it++) {
			if (*it == key) {
				return true;
			}
		}
		return false;
	}
};