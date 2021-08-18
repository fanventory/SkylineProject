#include "Graph.cpp"
#include "leveldb/db.h"
#pragma once
class SPSkyline
{
private:
private:
	vector<SPSkylineNode> nodes; // 存放语义地点数组
	map<int, int> index;		 // 语义地点字典，用于快速定位值为k的结点在数组中的未知
public:
	// 构造函数
	SPSkyline(){}
	// 析构函数
	~SPSkyline()
	{
		for (vector<SPSkylineNode>::iterator it = this->nodes.begin(); it < this->nodes.end(); it++)
		{
			(*it).L.~vector();
			(*it).vertices.~vector();
		}
		this->nodes.~vector();
	}
	// 获取语义地点数组
	vector<SPSkylineNode> getNodes()
	{
		return this->nodes;
	}
	// 获取语义地点字典
	map<int, int> getIndex()
	{
		return this->index;
	}
	// 查找语义地点需要插入数组中的位置
	int findNode(int node)
	{
		int low = 0;
		int high = (int)this->nodes.size() - 1;
		int mid;
		while (high >= low)
		{
			mid = (low + high) / 2;
			if (this->nodes[mid].sePlace == node)
			{
				return mid;
			}
			else if (this->nodes[mid].sePlace > node)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		return low;
	}
	// 通过坐标信息初始化语义结点数组
	void init(vector<string> fileRows)
	{
		for (vector<string>::iterator it = fileRows.begin(); it < fileRows.end(); it++)
		{
			// 字符串切割，前半段为语义地点p，后半段为坐标信息（不需要，抛弃）
			vector<string> t = Util::split(*it, ": ");
			// first为语义地点p
			int p = stoi(t.front());
			// 将语义地点p插入语义地点数组this->nodes中
			SPSkylineNode *temp = new SPSkylineNode(p);
			this->nodes.push_back(*temp);
			// 在语义地点字典中记录
			this->index[p] = (int)this->nodes.size() - 1;
		}
	}
	// 显示数据
	void show()
	{
		for (vector<SPSkylineNode>::iterator it = this->nodes.begin(); it < this->nodes.end(); it++)
		{
			cout << "index:" << (*it).sePlace << endl;
			int l = 0;
			for (vector<KSDL>::iterator it_inner = (*it).L.begin(); it_inner < (*it).L.end(); it_inner++)
			{
				cout << "L" << l++ << ":" << endl;
				for (map<int, int>::iterator it_w = (*it_inner).w.begin(); it_w != (*it_inner).w.end(); it_w++)
				{
					cout << (*it_w).first << ",";
				}
				cout << endl
					 << "-------------------------" << endl;
			}
		}
	}
	// 清空队列
	void clearQueue(queue<int> &q)
	{
		queue<int> empty;
		swap(empty, q);
	}
	// 计算语义地点，最大跳数为3
	void calculate(Graph &graph)
	{
		queue<int> qu; // 队列，用于实现BFS算法
		vector<Node> nodes = graph.getNodes();
		for (vector<SPSkylineNode>::iterator it = this->nodes.begin(); it < this->nodes.end(); it++)
		{
			int p = (*it).sePlace; // p为语义位置的根节点
			cout << "spskyline make semantic place " << p << endl;
			map<int, bool> keywordMap;		   // 判断该关键字是否已遍历
			map<int, bool> nodeMap;			   // 判断该结点是否已遍历
			map<int, bool>::iterator nodeIter; // 指向nodeMap的find函数返回值，判断指定的node是否已遍历
			int lastNode = p;
			int floor = 0; // 设置层数为0

			// 每次循环之前清空队列
			this->clearQueue(qu);
			qu.push(p);
			while (!qu.empty() && floor <= 3)
			{
				int curr = qu.front(); // 取队列第一个元素
				qu.pop();			   // 删除队列第一个元素
				// 记录已遍历过该元素
				nodeMap[curr] = true;
				// 将点curr上的关键词记录到每一层的字典中
				for (vector<int>::iterator it_inner = nodes[curr].keyword.begin(); it_inner < nodes[curr].keyword.end(); it_inner++)
				{
					map<int, bool>::iterator mapIter = keywordMap.find(*it_inner);
					if (mapIter == keywordMap.end())
					{
						// 在floor层中记录该关键词，这里采用字典存储关键词信息，用于接下来查找时减少时间复杂度
						(*it).L[floor].w[*it_inner] = 1;
						keywordMap[*it_inner] = true; // 在关键词字典中记录该关键词已遍历
					}
					//	keywordMap.insert(map<int, bool>::value_type(*it_inner, true));
				}

				// 查找点curr的邻接结点
				for (vector<int>::iterator it_inner = nodes[curr].edge.begin(); it_inner < nodes[curr].edge.end(); it_inner++)
				{
					nodeIter = nodeMap.find((*it_inner));
					if (nodeIter == nodeMap.end())
					{
						qu.push(*it_inner);
					}
				}
				// 当curr等于该层的最后一个结点时，层数加一，且lastNode指向下一层的最后一个结点
				if (curr == lastNode && !qu.empty())
				{
					lastNode = qu.back();
					floor++;
				}
			}
			// 记录该语义结点子树的所有语义位置
			for (map<int, bool>::iterator it_inner = nodeMap.begin(); it_inner != nodeMap.end(); it_inner++)
			{
				// 当该结点为语义位置且不为点p本身时，存储该结点信息到SP中
				if (nodes[(*it_inner).first].flag && (*it_inner).first != p)
				{
					(*it).vertices.push_back((*it_inner).first);
				}
			}
			sort((*it).vertices.begin(), (*it).vertices.end());
		}
	}
	// 将中间结果写入文件（用于调试程序）
	void write(string fileName)
	{
		ofstream outfile;
		outfile.open(fileName.data()); // 打开文件
		assert(outfile.is_open());	   // 判断文件是否打开成功

		for (vector<SPSkylineNode>::iterator it = this->nodes.begin(); it < this->nodes.end(); it++)
		{
			string k = to_string((*it).sePlace); // k为语义地点
			string v;							 // v为各层的关键字序列
			int floor = 0;
			for (vector<KSDL>::iterator it_inner = (*it).L.begin(); it_inner < (*it).L.end(); it_inner++)
			{
				v = v + to_string(floor++);
				for (map<int, int>::iterator it_w = (*it_inner).w.begin(); it_w != (*it_inner).w.end(); it_w++)
				{
					v = v + "," + to_string((*it_w).first);
				}
				v = v + "|";
			}
			// 写入文件
			outfile << k << ":" << v << endl;
		}
		outfile.close();
	}
	// 将中间结果从文件中读入内存（用于调试程序）
	void read(string fileName,string tmpDBName)
	{
		// 定义leveldb
		leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options,tmpDBName, &db);
        assert(status.ok());
		// 打开文件
		ifstream infile;
		infile.open(fileName.data()); // 打开文件
		assert(infile.is_open());	  // 判断文件是否打开成功
		string s;

		while (getline(infile, s)) // 按行读取文件
		{
			SPSkylineNode *SPSN = new SPSkylineNode();
			vector<string> t1 = Util::split(s, ":");				 // 切割字符串，t1为语义地点的根节点p
			SPSN->sePlace = stoi(t1.front());						 // 设置语义地点的根节点p
			// cout<<"read index "<<t1.front()<<endl;
			this->index[stoi(t1.front())] = (int)this->nodes.size(); // 存入语义地点字典中
			vector<string> t2 = Util::split(t1.back(), "|");		 // 切割字符串，t2为各层信息
			for (vector<string>::iterator it = t2.begin(); it < t2.end() - 1; it++)
			{
				vector<string> t4 = Util::split(*it, ","); //切割字符串，t4为层数和各层的关键词信息
				int L = stoi(t4.front());	// 第一个元素记录层数
				for (vector<string>::iterator it_inner = t4.begin() + 1; it_inner < t4.end(); it_inner++)
				{
					SPSN->L[L].w[stoi(*it_inner)] = 1;
				}
			}
			// 获取SP信息，即语义地点子树的各语义位置信息
			string v;
			status = db->Get(leveldb::ReadOptions(), t1.front(), &v);
			if (status.ok())
			{
				vector<string> t5 = Util::split(v, ",");
				for (vector<string>::iterator it = t5.begin(); it < t5.end() - 1; it++)
				{
					SPSN->vertices.push_back(stoi(*it));
				}
			}
			this->nodes.push_back(*SPSN);
		}
		delete db;
		infile.close();
	}
};