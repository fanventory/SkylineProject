#include "leveldb.cpp"

class Graph
{
private:
	vector<Node> nodes;
	map<int, int> nodesMap;
	int edgeNum;	// 边数量
	Graph(){}
public:
	static Graph& getInstance(){
        static Graph instance;
        return instance;
    }
	~Graph() {
		for (vector<Node>::iterator it = this->nodes.begin(); it < this->nodes.end(); it++) {
			(*it).edge.~vector();
		}
		this->nodes.~vector();
	}
	// 将关键字整合到图中，成为图中节点，便于计算可达性和距离
	void transformGraph(string edgeFileName, string keywordFileName) {
		// 打开文件
		vector<string> res;
		ifstream infile;
		infile.open(edgeFileName.data());   // 将文件流对象与文件连接起来 
		assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行
		string s;
		this->edgeNum=0;

		// 读取edge文件
		getline(infile, s);	// 跳过第一行
		while (getline(infile, s)) // 读取所有数据
		{
			vector<string> temp = Util::split(s, ": ");
			Node nodeT;
			nodeT.node = stoi(temp.front());	// 存储结点
			vector<string> edgeT = Util::split(temp.back(), ",");	// 存储边
			for (vector<string>::iterator it = edgeT.begin(); it != edgeT.end() - 1; it++) {
				nodeT.edge.push_back(stoi(*it));
				this->edgeNum++;
			}
			this->nodes.push_back(nodeT);
			nodesMap[nodeT.node] = this->nodes.size() - 1;
		}
		infile.close();

		// 读取keyword文件
		infile.open(keywordFileName.data());   // 将文件流对象与文件连接起来 
		assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行

		// 读取edge文件
		getline(infile, s);
		while (getline(infile, s)) // 读取所有数据
		{
			int index;
			vector<string> temp = Util::split(s, ": ");
			map<int,int>::iterator mapIter=this->nodesMap.find(stoi(temp.front()));
			if (mapIter == this->nodesMap.end()) {	// 图中没有该节点
				Node nodeT;
				nodeT.node = stoi(temp.front());	// 存储结点
				this->nodes.push_back(nodeT);
				nodesMap[nodeT.node] = this->nodes.size() - 1;
				index= this->nodes.size() - 1;
			}
			else {
				index = (*mapIter).second;
			}
			
			vector<string> edgeT = Util::split(temp.back(), ",");	// 存储边
			for (vector<string>::iterator it = edgeT.begin(); it != edgeT.end() - 1; it++) {
				this->nodes[index].edge.push_back(stoi(*it));
				this->edgeNum++;
			}
		}
		infile.close();
	}

	// 将图结构写入文件中，格式为：节点 出度数 连接的顶点1,连接的顶点2,.....
	void write(string outputFileName) {
		ofstream outfile;
		outfile.open(outputFileName.data());   // 将文件流对象与文件连接起来 
		assert(outfile.is_open());   // 若失败,则输出错误消息,并终止程序运行

		outfile<<this->nodes.size()<<" "<<this->edgeNum<<endl;
		for(vector<Node>::iterator it=this->nodes.begin();it!=this->nodes.end();it++){
			outfile<<(*it).node<<" "<<(*it).edge.size();
			for(vector<int>::iterator it_inner=(*it).edge.begin();it_inner!=(*it).edge.end();it_inner++){
				outfile<<" "<<(*it_inner);
			}
			if(it!=this->nodes.end()-1){
				outfile<<endl;
			}
		}
		outfile.close();
	}

	// 判断点p是否在队列中
	bool contains(queue<int> qu,int p){
		queue<int> tmp(qu);
		while(!tmp.empty()){
			if(p == tmp.front()){
				return true;
			}
			tmp.pop();
		}
		return false;
	}

	// 计算图中两结点的最短路径,采用bidirational Search算法
	int minDist(int from,int to) {
		bool *visit=new bool[this->nodes.size()];
		memset(visit,0,sizeof(bool)*this->nodes.size());
		queue<int> quf,qub;
		int distf = 0 ,distb = 0 , index = 0, p = 0, nextFf = from, nextFb=to;
		quf.push(from);
		qub.push(to);
		visit[this->nodesMap[from]]=true;
		visit[this->nodesMap[to]]=true;

		while (!quf.empty() && !qub.empty()) {
			if(!quf.empty()){
				p = quf.front();
				quf.pop();
				if(p == to || contains(qub,p)){
					return distf+distb-1;
				}
				// 获取点p的邻接结点
				for(vector<int>::iterator it=this->nodes[this->nodesMap[p]].edge.begin();it<this->nodes[this->nodesMap[p]].edge.end();it++){
					if(!visit[this->nodesMap[*it]]){
						visit[this->nodesMap[*it]]=true;
						quf.push(*it);
					}
				}
				// 若点p是当层最后一个结点，路径距离+1
				if(nextFf==p){
					distf++;
					nextFf=quf.back();
				}
			}

			if(!qub.empty()){
				p = qub.front();
				qub.pop();
				if(p == to || contains(quf,p)){
					return distf+distb-1;
				}
				// 获取点p的邻接结点
				for(vector<int>::iterator it=this->nodes[this->nodesMap[p]].edge.begin();it<this->nodes[this->nodesMap[p]].edge.end();it++){
					if(!visit[this->nodesMap[*it]]){
						visit[this->nodesMap[*it]]=true;
						qub.push(*it);
					}
				}
				// 若点p是当层最后一个结点，路径距离+1
				if(nextFb==p){
					distb++;
					nextFb=qub.back();
				}
			}
		}
		return -1;	// 不可达
	}
};