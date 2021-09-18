#include "leveldb.cpp"

class Graph
{
private:
	vector<Node *> rNodes;
	vector<Node *> cNodes;
	// 修改图的数据结构
	map<int, int> rNodesMap;	//	行索引
	map<int, int> cNodesMap;	//	列索引
	int edgeNum;	// 边数量
	int maxNode;
	Graph(){}
public:
	static Graph& getInstance(){
        static Graph instance;
        return instance;
    }

	//	获取链表数量
	int getNodeListSize(Node *no,char type){
		Node *p=no;
		int n=0;
		if(type=='r'){
			while(p!=NULL){
				p=p->right;
				n++;
			} 
		}else if(type=='c'){
			while(p!=NULL){
				p=p->down;
				n++;
			}
		}
		return n;
	}

	//	获取十字链表中指定行或列的最后一个链表结点,type取值r或c指示遍历方向
	Node *getLastNode(Node *no,char type){
		Node *p=no;
		if(type=='r'){	//	向右遍历最后一个结点
			if(p==NULL){	//	空链表
				return NULL;
			}
			while(p->right!=NULL){
				p=p->right;
			}
			return p;	//	返回最后一个结点
		}else if(type=='c'){
			if(p==NULL){	//	空链表
				return NULL;
			}
			while(p->down!=NULL){
				p=p->down;
			}
			return p;	//	返回最后一个结点
		}
		cout<<"type值传入出错！"<<endl;
		return NULL;	//	type传入出错
	}

	//	将边信息插入十字链表中
	void insertEdge(int from,int to){
		this->edgeNum++;	//	边数自增
		if(to>this->maxNode){
			this->maxNode=to;
		}
		//	将边插入十字链表中
		//	初始化结点
		Node *head=(Node *)malloc(sizeof(Node));
		head->from=from;
		head->to=to;
		head->right=NULL;
		head->down=NULL;
		//	初始化链表索引
		map<int, int>::iterator index;
		Node *row=NULL,*column=NULL;

		//	判断行索引是否存在
		index=this->rNodesMap.find(from);
		if(index==this->rNodesMap.end()){	//	from结点的索引不存在
			this->rNodesMap[from]=this->rNodes.size();	//	建立行索引
			this->rNodes.push_back(head);	//	插入链表中
		}else{//	from结点的索引存在
			head->right=this->rNodes[this->rNodesMap[from]];
			this->rNodes[this->rNodesMap[from]]=head;
			// row=this->getLastNode(this->rNodes[this->rNodesMap[from]],'r');	//	获取该行位置，并得到该行链表的最后一个结点
		}

		//	判断列索引是否存在
		index=this->cNodesMap.find(to);
		if(index==this->cNodesMap.end()){	//	to结点的索引不存在
			this->cNodesMap[to]=this->cNodes.size();	//	建立列索引
			this->cNodes.push_back(head);
		}else{	//	from结点的索引存在
			head->down=this->cNodes[this->cNodesMap[to]];
			this->cNodes[this->cNodesMap[to]]=head;
			// column=this->getLastNode(this->cNodes[this->cNodesMap[to]],'c');	//	获取该行位置，并得到该行链表的最后一个结点
		}
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
		this->maxNode=-1;

		// 读取edge文件
		getline(infile, s);	// 跳过第一行
		while (getline(infile, s)) // 读取所有数据
		{
			vector<string> temp = Util::split(s, ": ");
			int from = stoi(temp.front());	// 边的起始点
			if(from>this->maxNode){
				this->maxNode=from;
			}
			vector<string> tos = Util::split(temp.back(), ",");	// 边的终点集合
			for (vector<string>::iterator it = tos.begin(); it != tos.end() - 1; it++) {	
				//	end()-1是因为文件每一行结尾是空格，split按空格分割后，空格后面会分割出一个空的字符串
				int to=stoi(*it);	//	边的终点
				this->insertEdge(from,to);
			}
		}
		infile.close();
		cout<<1<<endl;
		// 读取keyword文件
		infile.open(keywordFileName.data());   // 将文件流对象与文件连接起来 
		assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行

		getline(infile, s);
		while (getline(infile, s)) // 读取所有数据
		{
			vector<string> temp = Util::split(s, ": ");
			int from=stoi(temp.front());
			if(from>this->maxNode){
				this->maxNode=from;
			}
			vector<string> tos = Util::split(temp.back(), ",");	// 获取关键词
			for (vector<string>::iterator it = tos.begin(); it != tos.end() - 1; it++) {
				//	end()-1是因为文件每一行结尾是空格，split按空格分割后，空格后面会分割出一个空的字符串
				int to=stoi(*it);	//	边的终点
				this->insertEdge(from,to);
			}
		}
		infile.close();
	}

	// 将图结构写入文件中，格式为：节点 出度数 连接的顶点1,连接的顶点2,.....
	void write(string outputFileName) {
		ofstream outfile;
		outfile.open(outputFileName.data());   // 将文件流对象与文件连接起来 
		assert(outfile.is_open());   // 若失败,则输出错误消息,并终止程序运行

		outfile<<this->maxNode+1<<" "<<this->edgeNum<<" "<<endl;
		for(map<int,int>::iterator it=this->rNodesMap.begin();it!=rNodesMap.end();it++){
			outfile<<(*it).first<<" "<<getNodeListSize(this->rNodes[(*it).second],'r');
			Node *p=this->rNodes[(*it).second];
			while(p!=NULL){
				outfile<<" "<<p->to;
				p=p->right;
			}
			if(it!=this->rNodesMap.end()){
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
		map<int,bool> visitf;	//	判断结点是否已经遍历过
		map<int,bool> visitb;
		queue<int> quf,qub;
		int distf = 0 ,distb = 0 , index = 0, p = 0, nextFf = from, nextFb=to;
		quf.push(from);
		qub.push(to);
		visitf[from]=true;
		visitb[to]=true;

		while (!quf.empty() && !qub.empty()) {
			if(!quf.empty()){
				p = quf.front();
				quf.pop();
				if(p == to || contains(qub,p)){
					return distf+distb;
				}
				// 获取点p的邻接结点
				if(this->rNodesMap.find(p)!=this->rNodesMap.end()){	//	该结点有邻接节点
					Node *no=this->rNodes[this->rNodesMap[p]];
					while(no!=NULL){
						if(visitf.find(no->to)==visitf.end()){	//	结点p未访问
							visitf[no->to]=true;
							quf.push(no->to);
						}
						no=no->right;
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
				if(p == from || contains(quf,p)){
					return distf+distb;
				}
				// 获取点p的邻接结点
				if(this->cNodesMap.find(p)!=this->cNodesMap.end()){	//	该结点有邻接节点
					Node *no=this->cNodes[this->cNodesMap[p]];
					while(no!=NULL){
						if(visitb.find(no->from)==visitb.end()){	//	结点p未访问
							visitb[no->from]=true;
							qub.push(no->from);
						}
						no=no->down;
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

	//	输出十字链表的列
	void showColumns() {
		for(map<int,int>::iterator it=this->cNodesMap.begin();it!=cNodesMap.end();it++){
			cout<<(*it).first<<" "<<getNodeListSize(this->cNodes[(*it).second],'c');
			Node *p=this->cNodes[(*it).second];
			while(p!=NULL){
				cout<<" "<<p->from;
				p=p->down;
			}
			if(it!=this->cNodesMap.end()){
				cout<<endl;
			}
		}
	}
	
	//	输出十字链表的行
	void showRows() {
		for(map<int,int>::iterator it=this->rNodesMap.begin();it!=rNodesMap.end();it++){
			cout<<(*it).first<<" "<<getNodeListSize(this->rNodes[(*it).second],'r');
			Node *p=this->rNodes[(*it).second];
			while(p!=NULL){
				cout<<" "<<p->to;
				p=p->right;
			}
			if(it!=this->rNodesMap.end()){
				cout<<endl;
			}
		}
	}

};