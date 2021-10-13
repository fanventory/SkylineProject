#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <cstring>
#include <assert.h>
using namespace std;

class Digraph
{
private:
    int V;  //  记录点数
    int E;  //  记录边数
    vector<vector<int>> adj;
    map<int,int> adjMap;
public:
    //  构造函数
    Digraph()
    {
        this->V=0;
        this->E=0;
    }
    ~Digraph(){}
    int getV(){
        return this->V;
    }
    int getE(){
        return this->E;
    }
    //  添加边
    void addEdge(int v,int w){
        int index;
        if(this->adjMap.find(v) ==this->adjMap.end()){    //  存储起点
            index=this->V;
            this->adjMap[v]=index;
            this->V++;
            this->adj.push_back(vector<int>());
        }else{  //  点已存储
            index=this->adjMap[v];
        }
        if (this->adjMap.find(w) == this->adjMap.end()) {  //  存储终点
            this->adjMap[w] = this->V;
            this->V++;
            this->adj.push_back(vector<int>());
        }
        //  插入边
        this->adj[index].push_back(w);
        this->E++;
    }
    //  返回顶点v指向的所有顶点w
    vector<int> getAdj(int v){
        int index;;
        if(this->adjMap.find(v)==this->adjMap.end()){    //  存储点
            return vector<int>();
        }else{  //  点已存储
            index=this->adjMap[v];
        }
        return this->adj[index];
    }
    //  得到反转的边
    Digraph reverse(){
        Digraph R;
        for(map<int,int>::iterator it=this->adjMap.begin();it!=this->adjMap.end();it++){
            int v=(*it).first;
            vector<int> w=this->getAdj(v);
            for(vector<int>::iterator it_inner=w.begin();it_inner!=w.end();it_inner++){
                R.addEdge(*it_inner,v);
            }
        }
        return R;
    }
    //  获取字典
    map<int,int> getMap(){
        return this->adjMap;
    }
    //  读取图
    void readGraph(string edgeFileName){
        vector<string> res;
		ifstream infile;
		infile.open(edgeFileName.data());   // 将文件流对象与文件连接起来 
		assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行
		string s;

		// 读取edge文件
		getline(infile, s);	// 跳过第一行
		while (getline(infile, s)) // 读取所有数据
		{
			vector<string> temp = this->split(s, ": ");
			int from = stoi(temp.front());	// 边的起始点
			vector<string> tos = this->split(temp.back(), ",");	// 边的终点集合
            for(vector<string>::iterator it=tos.begin();it!=tos.end()-1;it++){
				this->addEdge(from,stoi(*it));
			}
		}
		infile.close();
    }
    //  工具函数：切割字符串
    vector<string> split(string str, string pattern)
	{
		string::size_type pos;
		vector<string> result;
		str += pattern;//扩展字符串，处理分隔符不存在的情况
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

};