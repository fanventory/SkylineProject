#include "leveldb.cpp"

/*
 *  该类用于生成运行TL_pre_processing程序所需的图结构文件
 */

class TL_pre_file
{
private:
    vector<set<int>> rNodes;	//	存储有向图
    map<int, int> rNodesMap;	//	行索引
    map<int,int> conTable;	//	存储结点的强连通关系
    int maxNode;	//	最大结点值
    int edgeNum;    //  边数
public:
    // 读取文件，构造图结构和强连通分量索引
	void readGraph(string edgeFileName, string keywordFileName,string conTableFileName) {
		// 打开文件
		vector<string> res;
		ifstream infile;
		string s;
		this->maxNode=-1;
        this->edgeNum=0;

        //	读取强连通分量关系
		infile.open(conTableFileName.data());   // 将文件流对象与文件连接起来 
		assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行
		while (getline(infile, s)) // 读取所有数据
		{
			vector<string> temp = Util::split(s, ",");
			this->conTable[stoi(temp.front())]=stoi(temp.back());
		}
		infile.close();

		// 读取edge文件
		infile.open(edgeFileName.data());   // 将文件流对象与文件连接起来 
		assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行
		getline(infile, s);	// 跳过第一行
		while (getline(infile, s)) // 读取所有数据
		{
			vector<string> temp = Util::split(s, ": ");
			int from = stoi(temp.front());	// 边的起始点
			if(from>this->maxNode){
				this->maxNode=from;
			}
			vector<string> tos = Util::split(temp.back(), ",");	// 边的终点集合
			this->insertEdge(from,tos,"node");
		}
		infile.close();

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
			this->insertEdge(from,tos,"keyword");
		}
		infile.close();
	}

    //  处理强连通分量，将这些强连通分量写入rNodes中，形成图结构
    /*
    void connectGraph(){
        int mapIndex;
        for(map<int,int>::iterator it=this->conTable.begin();it!=this->conTable.end();it++){
            if((*it).first!=(*it).second){
                //  插入索引
                if(this->rNodesMap.find((*it).second)==this->rNodesMap.end()){	//	结点(*it).second未在索引中
                    mapIndex=this->rNodes.size();
                    this->rNodesMap[(*it).second]=mapIndex;
                    this->rNodes.push_back(vector<int>());
                }else{	//	结点(*it).second已在索引中
                    mapIndex=this->rNodesMap[(*it).second];
                }

                //  插入边
                this->rNodes[mapIndex].insert((*it).first);
                this->edgeNum++;
            }
        }
    }
    */

    //	插入from结点对应的一组边,如果type值为keyword，则将tos数组存入this->keyList关键词序列中
	void insertEdge(int from,vector<string> tos,string type){
		int mapIndex;
		//	将tos的string类型转化为int
		vector<int> intTos;
        // transform (tos.begin(), tos.end(),intTos.begin(),[](string n){return stoi(n);});
		for(vector<string>::iterator it=tos.begin();it!=tos.end()-1;it++){
			intTos.push_back(stoi(*it));
		}
    
        //  比较大小
        int maxTo=*max_element(intTos.begin(),intTos.end());    //  获取IntTos中的最大值
        if(from > this->maxNode){
            this->maxNode=from;
        }
        if(maxTo>this->maxNode){
            this->maxNode=maxTo;
        }

        //  若起点from位于强连通分量中，则使用虚拟结点指向其他结点
        if(this->conTable.find(from)!=this->conTable.end()){
            from=this->conTable[from];
        }

		//	插入边索引
		if(this->rNodesMap.find(from)==this->rNodesMap.end()){	//	结点from未在索引中
			mapIndex=this->rNodes.size();
			this->rNodesMap[from]=mapIndex;
			this->rNodes.push_back(set<int>());
		}else{	//	结点from已在索引中
			mapIndex=this->rNodesMap[from];
		}
		
		//	插入边
        for(vector<int>::iterator it=intTos.begin();it!=intTos.end();it++){
            //  如果该边在强连通分量中，则另其指向虚拟节点
            int to=*it;
            if(this->conTable.find(to)!=this->conTable.end()){
                to=this->conTable[to];
            }
            //  插入边
            this->rNodes[mapIndex].insert(to);
            this->edgeNum++;
        }
		
	}

    void write(string outputFileName) {
		ofstream outfile;
		outfile.open(outputFileName.data());   // 将文件流对象与文件连接起来 
		assert(outfile.is_open());   // 若失败,则输出错误消息,并终止程序运行

        outfile<<this->maxNode+1<<" "<<this->edgeNum<<endl;
		for(map<int,int>::iterator it=this->rNodesMap.begin();it!=this->rNodesMap.end();it++){
			outfile<<(*it).first<<" "<<this->rNodes[(*it).second].size();
			for(set<int>::iterator it_inner=this->rNodes[(*it).second].begin();it_inner!=this->rNodes[(*it).second].end();it_inner++){
				outfile<<" "<<*it_inner;
			}
			if(it!=this->rNodesMap.end()){
				outfile<<endl;
			}
		}
		outfile.close();
	}
};

