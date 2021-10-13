#include "Digraph.cpp"
#include <stack>

//  计算拓扑序列
class DepthFirstOrder
{
private:
    map<int,bool> marked;
    stack<int> reversePost;
public:
   DepthFirstOrder(Digraph G){
       map<int,int> GMap=G.getMap();
       for(map<int,int>::iterator it=GMap.begin();it!=GMap.end();it++){
           int v=(*it).first;
           if(this->marked.find(v)==this->marked.end()){
               this->dfs(G,v);
           }
       }
   }
   void dfs(Digraph &G,int v){
       this->marked[v]=true;
       vector<int> w=G.getAdj(v);
       if (!w.empty()) {
           for (vector<int>::iterator it = w.begin(); it != w.end(); it++) {
               if (this->marked.find(*it) == this->marked.end()) {
                   this->dfs(G, *it);
               }
           }
           
       }
       this->reversePost.push(v);
   }
   stack<int> getPost(){
        return this->reversePost;
    }
};
