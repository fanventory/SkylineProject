#include "SPSkyline.cpp"
class  Table
{
private:
	vector<tripleRow> row;	// 倒排索引组
	map<int, int> tableIndex;	// 倒排索引组索引
public:
	~Table()
	{
		for (vector<tripleRow>::iterator it = this->row.begin(); it < this->row.end(); it++) {
			(*it).triples.~vector();
		}
		this->row.~vector();
	}
	// 获取内部对象row
	vector<tripleRow> getRow() {
		return this->row;
	}
	// 通过二分查找，获取关键词在row组中的位置，若存在返回下标，否则返回应该插入的位置
	int findRow(int key)
	{
		int low = 0;
		int high = (int)this->row.size() - 1;
		int mid;
		while (high >= low)
		{
			mid = (low + high) / 2;
			if (this->row[mid].keyword == key)
			{
				return mid;
			}
			else if (this->row[mid].keyword > key)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}

		}
		return  low;
	}
	// 将tripleRow对象插入row中
	void insertSingleRow(int key) {
		tripleRow *tR = new tripleRow();
		tR->keyword = key;	// 设置关键词
		this->row.push_back(*tR);	// 添加到倒排索引组row中
		this->tableIndex[key] = (int)this->row.size() - 1;
	}
	// 通过二分查找法获取元组需要插入的位置
	int findTriple(tripleRow &tR, int d, int node) {
		int low = 0;
		int high = (int)tR.triples.size() - 1;
		int mid;
		while (high >= low)
		{
			mid = (low + high) / 2;
			if (tR.triples[mid].distance == d)
			{
				if (tR.triples[mid].index > node) {
					high = mid - 1;
				}
				else if (tR.triples[mid].index < node) {
					low = mid + 1;
				}
				else {
					return mid;
				}
			}
			else if (tR.triples[mid].distance > d)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}

		}
		return  low;
	}
	// 生成倒排索引
	void calculate(SPSkyline &spsl) {
		// 获取SPSkylineNode数据结构，包含语义地点信息
		vector<SPSkylineNode> nodes = spsl.getNodes();
		map<int,int> index = spsl.getIndex();
		// 关键词字典，判断关键词已写入数据结构中
		map<int, bool> keywordMap;
		map<int, bool>::iterator iter;
		for (vector< SPSkylineNode>::iterator it = nodes.begin(); it < nodes.end(); it++) {
			int p = (*it).sePlace;	// 获取根节点
			cout << "table calculate semantic place " << p << endl;
			// 处理第0、1、2、3层关键词信息
			for (int l = 0; l <= 3; l++) {
				// *it_inner为某一层的关键词序列
				try
				{
					for (map<int,int>::iterator it_inner = (*it).L[l].w.begin(); it_inner != (*it).L[l].w.end(); it_inner++) {
						tripleRow *tR = NULL;
						
						// 判断倒排索引组row中是否存在关键词
						iter = keywordMap.find((*it_inner).first);
						if (iter == keywordMap.end()) {	// 倒排索引组row中没有该关键词
							// 将关键词元组写入倒排索引组row中
							this->insertSingleRow((*it_inner).first);
							// 字典中存入该关键字
							keywordMap[(*it_inner).first] = true;
						}
						// 获取关键词的位置
						int i = this->tableIndex[(*it_inner).first];
						tR = &(this->row[i]);
						
						if (l == 0) {	// 处理第0层
							// 将元组插入row行中
							triple *t = new triple(p, 0, false);
							int i_inner = this->findTriple(*tR, 0, p);
							tR->triples.insert(tR->triples.begin() + i_inner, *t);
						}
						else {	// 处理第1、2、3层
							// 查找是否存在更短的语义地点到关键词的距离，即求B的值
							// 当前根节点到语义地点的距离为L，若第L层含有语义地点a[1,2,...,i]，查询语义地点a[i]中是否有达到该关键词更短的距离
							int minLen = l;
							for (vector<int>::iterator it_node = (*it).vertices.begin(); it_node < (*it).vertices.end(); it_node++) {
								// *it_node为根节点到关键词w路径上的语义地点v
								if (minLen != l) {	// 跳出循环
									break;
								}
								for (int j = 0; j < l; j++) {
									// 查询是否存在到关键词w[i]更近的语义地点
									int k = index[*it_node];
									map<int,int>::iterator resT=nodes[k].L[j].w.find((*it_inner).first);
									if (resT != nodes[k].L[j].w.end()) { // 存在更近的语义地点
										minLen = j;
										break;	// 跳出循环
									}
									
								}
							}
							bool B;
							if (minLen == l) {
								B = false;
							}
							else {
								B = true;
							}
							// 将元组插入row行中
							triple *t = new triple(p, l, B);
							int i_inner = this->findTriple(*tR, l, p);
							tR->triples.insert(tR->triples.begin() + i_inner, *t);
						}

					}
				}
				catch (const std::exception& e)
				{
					cout << e.what() << endl;
				}
			}
		}
	}
	// 显示数据结果
	void show() {
		for (map<int,int>::iterator it = this->tableIndex.begin(); it != this->tableIndex.end(); it++) {
			cout << "w:" << (*it).first << endl;
			vector<triple> tris= this->row[(*it).second].triples;
			for (vector<triple>::iterator it_inner = tris.begin(); it_inner < tris.end(); it_inner++) {
				cout << " (" << (*it_inner).index << "," << (*it_inner).distance << "," << boolalpha << (*it_inner).flag << "),";
			}
			cout << endl << "---------------------------------" << endl;
		}
	}
};

