#include "DepthFirstOrder.cpp"

class Kosaraju
{
private:
    map<int, bool> marked;
    map<int, int> id;
    int count;
public:
    Kosaraju(Digraph& G) {
        DepthFirstOrder order(G.reverse());
        stack<int> reversePost = order.getPost();
        this->count = 0;
        while (!reversePost.empty()) {
            int s = reversePost.top();
            reversePost.pop();
            if (this->marked.find(s) == this->marked.end()) {
                dfs(G, s);
                this->count++;
            }
        }
    }
    void dfs(Digraph& G, int v) {
        this->marked[v] = true;
        this->id[v] = count;
        vector<int> w = G.getAdj(v);
        for (vector<int>::iterator it = w.begin(); it != w.end(); it++) {
            if (this->marked.find(*it) == this->marked.end()) {
                this->dfs(G, *it);
            }
        }
    }
    bool stronglyConnected(int v, int w) {
        return this->id[v] == this->id[w];
    }
    int getId(int v) {
        return this->id[v];
    }
    int getCount() {
        return this->count;
    }
    map<int, int> getMap() {
        return this->id;
    }
    //	写入文件
    void write(string fileName, int total) {
        ofstream outfile;
        outfile.open(fileName.data());   // 将文件流对象与文件连接起来 
        assert(outfile.is_open());   // 若失败,则输出错误消息,并终止程序运行

        outfile << total << "," << this->count << endl;
        for (map<int, int>::iterator it = this->id.begin(); it != this->id.end(); it++) {
            outfile << (*it).first << "," << (*it).second << endl;
        }
        outfile.close();
    }
};

