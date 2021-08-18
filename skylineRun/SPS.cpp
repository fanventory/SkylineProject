#include "Graph.cpp"
#include "TL_LABEL.cpp"
#pragma once
class SPS
{
private:
	vector<KeyRow> keyRows; // 三元组序列
	map<int, int> index;	// 三元组索引
	map<int, vector<keyDist>> distMap;	// 存储结点到关键词距离
	int queryNum;	// 查询关键词的数量
public:
	// 构造函数
	SPS(){}

	// 析构函数
	~SPS() {
		for (vector<KeyRow>::iterator it = this->keyRows.begin(); it < this->keyRows.end(); it++) {
			(*it).triples.~vector();
		}
		this->keyRows.~vector();
	}

	// 根据读取到的文本行，构造倒排索引数据结构
	void init(vector<KeyRow> row) {
		for (vector<KeyRow>::iterator it = row.begin(); it < row.end(); it++) {
			this->keyRows.push_back(*it);
			this->index[(*it).key] = this->keyRows.size() - 1;
		}
	}

	// 展示倒排索引数据
	void show() {
		for (vector<KeyRow>::iterator it = this->keyRows.begin(); it < this->keyRows.end(); it++) {
			cout << "keyword :" << (*it).key << endl;
			for (vector<Triple>::iterator it_inner = (*it).triples.begin(); it_inner < (*it).triples.end(); it_inner++) {
				cout << "(" << (*it_inner).node << "," << (*it_inner).distance << "," << boolalpha << (*it_inner).B << ")";
			}
			cout << endl << "---------------------------------" << endl;
		}
	}

	// 获取key对应的倒排索引行
	void getW(int key,vector<Triple> &list) {
		map<int, int>::iterator mapIter = this->index.find(key);
		if (mapIter != this->index.end()) {	// list不等于空
			int listIndex = (*mapIter).second;
			list = this->keyRows[listIndex].triples;
		}

	}

	// 将list中的结点加入字典distMap中
	void buildDistMap(vector<Triple> list) {
		for (vector<Triple>::iterator it = list.begin(); it < list.end(); it++) {
			map<int, vector<keyDist>>::iterator tempIter= this->distMap.find((*it).node);
			if (tempIter == this->distMap.end()) {
				vector<keyDist> temp;
				this->distMap[(*it).node] = temp;
			}
		}
	}

	// 获取倒排索引中点p到关键词key的距离，点p到关键词key的距离位置，返回-1
	int getDistByMap(int p,int key) {
		for (vector<keyDist>::iterator it = this->distMap[p].begin(); it < this->distMap[p].end(); it++) {
			if ((*it).key == key) {
				return (*it).dist;
			}
		}
		return -1;
	}

	// 计算点p到所有关键词是否可达
	bool materialized(int p,vector<int> query){
		if(this->distMap[p].size()!=query.size()){	// 3跳内不可达
			return false;
		}else{
			return true;
		}
	}

	// 获取点p到所有关键词的距离
	void ComputeDist(int p, vector<int> query) {
		Graph graph;
		int d;
		/*
			点p到关键词*it存在多个可达结点的情况：
			情况1：3跳内存在多个可达结点
				这种情况下前一步生成的倒排索引Table只会存储第一个最近的可达结点，此后取该关键词距离都是通过DistMap字典来操作，对于程序而言只关心距离而不关心路径信息
			情况2：3跳外存在多个可达结点
				这种情况下，调用bidirational Search算法算出的距离是最小距离，就算存在多个可达结点，取到的第一个一定是最短距离，其余较长的距离可直接排除
		*/
		for (vector<int>::iterator it = query.begin(); it < query.end(); it++) {
			// 查看字典distMap中是否存储了点p到关键词*it的距离
			d=this->getDistByMap(p,*it);
			if (d < 0) {	// 字典distMap没有点p到关键词*it的距离，调用graph.minDist计算距离
				d = graph.minDist(p, *it) - 1;	// graph中关键词被转化为结点，所以距离要减去1
				if (d < 0) {	// 点p到关键词*it不可达，返回一个空数组
					cout<<"error: "<<p<<" cannot reach find keyword "<< *it <<endl;
				}
				// 将计算好的值存入字典中
				this->distMap[p].push_back(keyDist(*it, d));
			} 
		}
	}

	// Partition根据距离划分Cand
	vector<vector<int>> Partition(set<int> Cand, vector<int> query) {
		vector<vector<int>> dists;	// 记录Cand中所有点到查询关键词q.Ψ的距离
		vector<int> CandT(Cand.begin(),Cand.end());	// 将set集合转化为vector数组
		for (vector<int>::iterator it = CandT.begin(); it < CandT.end(); it++) {
			vector<int> distRow;	// 记录Cand中单个点p[i]到各个关键词q.Ψ的距离
			for (vector<int>::iterator it_inner = query.begin(); it_inner < query.end(); it_inner++) {
				// 计算距离
				distRow.push_back(this->getDistByMap(*it,*it_inner));
			}
			dists.push_back(distRow);
		}

		// 根据距离分组,到各个关键词的距离都相同的结点视为同一组，这里引进分组分数，同一组的分数相同
		vector<vector<int>> p;	// 分组后的结点（同组只取第一个结点的值）
		map<string, int> indexT;	// 索引，记录分组分数和组下标的关系

		// =================================================================================================== //
		// 做法1：将所有不可达的结点成为独立组
		for (int i = 0; i < CandT.size(); i++) {
			vector<int> tmpRow = dists[i];
			string score;
			for (vector<int>::iterator it = tmpRow.begin(); it < tmpRow.end(); it++) {
				if (*it == -1) {	// 3跳内对该关键词不可达
					// 将该语义地点独立分为一组
					vector<int> tmp;
					tmp.push_back(CandT[i]);
					p.push_back(tmp);
					score="";
					break;
				}
				score += to_string(*it)+",";	
			}
			if(score.compare("")==0){	// 3跳内不可达的情况已记录，不参与下列分组环节
				continue;
			}
			map<string, int>::iterator tempIter = indexT.find(score);
			if (tempIter == indexT.end()) {
				vector<int> tmp;
				tmp.push_back(CandT[i]);
				p.push_back(tmp);
				indexT[score] = p.size() - 1;	// 记录此分组score在输出队列p中的位置
			}
			else 
			{
				p[(*tempIter).second].push_back(CandT[i]);
			}
		}
		// =================================================================================================== //
		// 做法2：将不可达的结点的距离视为4，这样可将不可达的结点进行分组
		/*
		for (int i = 0; i < CandT.size(); i++) {
			vector<int> tmpRow = dists[i];
			string score;
			for (vector<int>::iterator it = tmpRow.begin(); it < tmpRow.end(); it++) {
				if (*it == -1) {	// 3跳内对该关键词不可达
					score += "4,";	
				}else{
					score += to_string(*it)+",";	
				}
			}
			// 根据距离分组
			map<string, int>::iterator tempIter = indexT.find(score);
			if (tempIter == indexT.end()) {
				vector<int> tmp;
				tmp.push_back(CandT[i]);
				p.push_back(tmp);
				indexT[score] = p.size() - 1;	// 记录此分组score在输出队列p中的位置
			}
			else 
			{
				p[(*tempIter).second].push_back(CandT[i]);
			}
		}
		*/
		// =================================================================================================== //
		return p;
	}

	// 判断两语义地点之间的支配算法
	bool control(int pi,int pj) {
		// 执行此算法时，一定不存在不可达或可达性未知的结点
		vector<keyDist> rowi=this->distMap[pi];
		vector<keyDist> rowj=this->distMap[pj];
		// 如果语义地点的可达性未知，则返回true，不执行裁剪
		if(rowi.size()!=this->queryNum || rowj.size()!=this->queryNum){
			return true;
		}
		bool flag=false;	// 用于判断rowi和rowj中所有距离都相等的情况
		// 如果不可支配，返回false
		for(int i=0;i<rowi.size();i++){
			if(rowi[i].dist>rowj[i].dist){
				return false;	//不可支配
			}else if(rowi[i].dist<rowj[i].dist){
				flag=true;
			}
		}
		if(flag){	//	可支配
			return true;
		}else{	// 两结点到所有关键词的距离都相等，不可支配
			return false;
		}
	}

	// P中两两之间进行支配比较，并执行裁剪操作
	void DominanceCheck(vector<vector<int>> &P,int &t3){
		bool bflag=false;
		for (vector<vector<int>>::iterator it = P.begin(); it < P.end(); ) {	// for each partition Pi∈ P do
			for (vector<vector<int>>::iterator it_inner = it+1; it_inner < P.end(); it_inner++) {
				if(control((*it_inner).front(),(*it).front())){
					it = P.erase(it);	// Pi is pruned and removed;
					t3++;	// 记录裁剪次数
					bflag=true;	// 执行 P.erase(it);后，it指向下一个结点，此时不需要执行it++语句
					break;
				}
			}
			if(!bflag){
				it++;
			}
		}
	}

	// 对distMap进行排序
	void sortDistMap(){
		for(map<int, vector<keyDist>>::iterator it=this->distMap.begin();it!=this->distMap.end();it++){
			sort((*it).second.begin(),(*it).second.end(),Util::comp);
		}
	}

	// SPS算法
	vector<int> SPS_calculate(vector<int> query,string SPFileName) {
		set<int> SkylineSet,Cand;
		vector<Triple> list;
		int t1=0,t2=0,t3=0;	// 记录三次裁剪的计数器
		this->queryNum=query.size();

		for (vector<int>::iterator it = query.begin(); it < query.end(); it++) {	// for each w[i] in q.Ψ
			list.clear();		// 清空list
			this->getW(*it, list);	// list[i]=SL.get(w[i])
			if (list.size() != 0) {	// list!=0
				// 将list中的结点加入字典distMap中，便于后续计算结点到关键字的距离
				this->buildDistMap(list);
				Triple entryTmp=list.back();	// Entry(p,d,B)<-list[i].RemoveEntry()
				list.pop_back();
				int min = entryTmp.distance;	// min<-d
				this->distMap[entryTmp.node].push_back(keyDist(*it,min));	// 记录结点到关键词的距离
				for (vector<Triple>::iterator it_inner = list.begin(); it_inner < list.end(); it_inner++) {	// repeat
					this->distMap[(*it_inner).node].push_back(keyDist(*it, (*it_inner).distance));	// 记录结点到关键词的距离
					if ((*it_inner).distance == min) {	// min==d
						SkylineSet.insert((*it_inner).node);	// ADD/Update p to/in Skyline
					}
					else { // min!=d
						Cand.insert((*it_inner).node);	// ADD p to/in Cand
					}
				}
			}
		}
		cout<<11<<endl;
		// this->sortDistMap();

		// Update p to / in Cand
		set<int> C;
		// 求Skyline和Cand的差集
		set_difference(Cand.begin(), Cand.end(), SkylineSet.begin(), SkylineSet.end(), insert_iterator<set<int>>(C, C.begin()));
		Cand.swap(C);		// 此时Cand为去除Skyline的部分

		// judge p in Skyline if can reach all keyword limit 3 skip, if can, we define that p is materialized
		vector<queryNode> query_list;
		vector<int> SkylineUnMaterialized;
		for (set<int>::iterator sIter = SkylineSet.begin(); sIter != SkylineSet.end(); sIter++) {
			// if p is not materialized, push in query_list, which use to test if p is reachable later
			if(!this->materialized(*sIter,query)){	// if p is not materialized
				for (vector<int>::iterator wIter = query.begin(); wIter < query.end(); wIter++) {
					queryNode temp(*sIter,*wIter);
					query_list.push_back(temp);	// query_list用于调用TL_LABEL算法判断可达性
				}
				SkylineUnMaterialized.push_back(*sIter);
			}
		}
		
		// query if two node reach each other by TL_Label
		char indexFile[64];
		strcpy(indexFile, "../index/p2p_scc");
		vector<int> res = judgeReachable(Util::countFileRows("./data.txt"), indexFile, query_list);	// if p is reachable, return 1; else return 0
		cout<<12<<endl;	

		// judge p in Skyline can reach all query keyword in q.Ψ
		vector<int> SkylineUnReachable;
		int reachTemp=0;
		for (int i = 0,k = 0; i < res.size(); i++ ) { 
			reachTemp += res[i];
			if (i == (k + 1)*query.size() - 1) {
				if (reachTemp != query.size()) {	// unreachable
					SkylineUnReachable.push_back(SkylineUnMaterialized[k]);
				}
				k++;
				reachTemp = 0;
			}
		}

		// delete the node p which cannot reach q.ψ
		vector<int> Skyline;	// Skyline的结果到所有关键词都可达
		set_difference(SkylineSet.begin(), SkylineSet.end(), SkylineUnReachable.begin(), SkylineUnReachable.end(), insert_iterator<vector<int>>(Skyline, Skyline.begin()));

		// Compute distance that node in Skyline
		for (vector<int>::iterator sIter = Skyline.begin(); sIter != Skyline.end(); sIter++) {	// for each p ∈ Skyline do
			ComputeDist(*sIter,query);	// ComputeDist(p, q.ψ);
		}
		this->sortDistMap();
		cout<<13<<endl;	

		// P ← Partition(Cand);
		vector<vector<int>> P = Partition(Cand, query);	
		cout<<14<<endl;	

		for (vector<vector<int>>::iterator it = P.begin(); it < P.end(); ) {	// for each partition Pi∈ P do
			bool bflag = false;
			vector<int> pi = (*it);
			for (vector<int>::iterator it_s = Skyline.begin(); it_s < Skyline.end(); it_s++) {
				if (control(*it_s,pi[0])) {	// if ∃pj∈ Skyline(Tpj≺ Tp∗i) then
					it = P.erase(it);	// Pi is pruned and removed;
					bflag = true;
					t1++;
					break;
				}
			}
			if (bflag) {	// if Pi is pruned and removed ,skip this cycle
				continue;
			}
			for (vector<int>::iterator it_i = pi.begin(); it_i < pi.end(); it_i++) {	// for each p ∈ Pido
				Leveldb ldb;
				vector<int> vp=ldb.SPGet(*it_i,SPFileName);	// Vp← Sp.Get(p);
				for (vector<int>::iterator it_v = vp.begin(); it_v < vp.end(); it_v++) {
					ComputeDist(*it_v,query);
					if (materialized(*it_v,query)){
						if(control(*it_v, *it_i)) {	// if ∃pj∈ Vp(Tpj≺ Tp) then
							it = P.erase(it);	// Pi is pruned and removed;
							bflag = true;
							t2++;
							break;
						}
					}
				}
				if (bflag) {	// if Pi is pruned and removed ,skip this cycle
					break;
				}
			}
			if (!bflag) {	// if Pi is not pruned and removed ,it point Pi+1
				it++;	// 避免最后一个结点执行P.erase()后，执行it++操作导致报错，所以it++在此处执行
			}
		}

		cout<<15<<endl;	
		// ========================================================================================================== //
		// 方法1：对P中的点先求可达性和距离，再进行两两支配关系比较
		vector<int> PUnMaterialized;
		query_list.clear();
		for (vector<vector<int>>::iterator it = P.begin(); it < P.end(); it++) {	// for each partition Pi∈ P do
			if (!materialized((*it).front(),query)){	// 可达性未知
				for (vector<int>::iterator wIter = query.begin(); wIter < query.end(); wIter++) {
					queryNode temp((*it).front(),*wIter);
					query_list.push_back(temp);
				}
				PUnMaterialized.push_back((*it).front());
			}
		}
		res = judgeReachable(Util::countFileRows("./data.txt"), indexFile, query_list);
		cout<<16<<endl;	
		vector<int> PUnReachable;
		reachTemp=0;
		for (int i = 0,k = 0; i < res.size(); i++ ) { 
			reachTemp += res[i];
			if (i == (k + 1)*query.size() - 1) {
				if (reachTemp != query.size()) {	// unreachable
					PUnReachable.push_back(PUnMaterialized[k]);
				}
				k++;
				reachTemp = 0;
			}
		}
		// delete the node p which cannot reach q.ψ
		for (vector<vector<int>>::iterator it = P.begin(); it < P.end(); ) {
			vector<int>::iterator itFind = find(PUnReachable.begin(), PUnReachable.end(), (*it).front());
			if(itFind!=PUnReachable.end()){	// P UnReachable
				it = P.erase(it);	// Pi is pruned and removed;
			}else{
				it++;
			}
		}
		// Compute distance that node in Skyline
		for (vector<vector<int>>::iterator it = P.begin(); it < P.end(); ) {
			ComputeDist((*it).front(),query);	// ComputeDist(p, q.ψ);
		}	// 距离计算完成，结果都存放在变量distMap中
		cout<<17<<endl;	
		this->sortDistMap();
		cout<<18<<endl;	
		// ========================================================================================================== //
		// 方法2：按照论文上的方法，求可达性和距离 与 支配关系比较同时进行
		/*
		for (vector<vector<int>>::iterator it = P.begin(); it < P.end(); ) {	// for each partition Pi∈ P do
			if(materialized((*it).front(),query){	// if p∗i is materialized then
				bool bflag=false;
				for (vector<vector<int>>::iterator it_inner = it+1; it_inner < P.end(); it_inner++) {
					// if ∃Pj∈ P (p∗j is materialized ∧ Tp∗j≺ Tp∗i) then
					if (materialized((*it_inner).front(),query)){
						if(control((*it_inner).front(),(*it).front())){
							it = P.erase(it);	// Pi is pruned and removed;
							t3++;
							bflag=true;
							break;
						}
					}
				}
				if(!bflag){
					it++;
				}
			}else{	// if p∗i is not materialized then
				vector<queryNode> query_list;
				for (vector<int>::iterator it_inner = (*it).begin(); it_inner < (*it).end(); it_inner++) {	// for each p ∈ Pido
					for (vector<int>::iterator wIter = query.begin(); wIter < query.end(); wIter++) {
						queryNode temp(*it_inner,*wIter);
						query_list.push_back(temp);	// query_list用于调用TL_LABEL算法判断可达性
					}
				}
				// query if two node reach each other by TL_Label
				char indexFile[64];
				strcpy(indexFile, "../index/p2p_scc");
				res = judgeReachable(Util::countFileRows("./data.txt"), indexFile, query_list);	// if p is reachable, return 1; else return 0

				// judge p in Skyline can reach all query keyword in q.Ψ
				vector<int> PUnReachable;
				int reachTemp=0;
				for (int i = 0,k = 0; i < res.size(); i++ ) { 
					reachTemp += res[i];
					if (i == (k + 1)*query.size() - 1) {
						if (reachTemp != query.size()) {	// unreachable
							PUnReachable.push_back((*it)[k]);
						}
						k++;
						reachTemp = 0;
					}
				}
				// delete the node p which cannot reach q.ψ
				for (vector<int>::iterator it_inner = (*it).begin(); it_inner < (*it).end(); it_inner++) {	// for each p ∈ Pido
					vector<int>::iterator itFind = find(PUnReachable.begin(), PUnReachable.end(), *it_inner);
					if(itFind!=PUnReachable.end()){	// P UnReachable
						it_inner = P.erase(it_inner);	// Pi is pruned and removed;
					}else{	// if ReachabilityTest(p, q.ψ) then
						ComputeDist(*it_inner,query);	// ComputeDist(p, q.ψ);
						it_inner++;
					}
				}	
			}	
		}
		*/
		// ========================================================================================================== //
		DominanceCheck(P,t3);	// DominanceCheck(P);
		cout<<19<<endl;	
		for (vector<vector<int>>::iterator it = P.begin(); it < P.end(); ) {	// Add each Pi∈ P to Skyline;
			vector<int> pi = (*it);
			for (vector<int>::iterator it_p = pi.begin(); it_p < pi.end(); it_p++) {
				Skyline.push_back(*it_p);
			}
		}

		cout<<"t1:"<<t1<<endl<<"t2:"<<t2<<endl<<"t3:"<<t3<<endl;
		return Skyline;
	}
};
