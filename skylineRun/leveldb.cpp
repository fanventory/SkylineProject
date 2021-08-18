#include "Util.cpp"
#include "leveldb/db.h"
class Leveldb {
private:
	leveldb::DB* db;
	leveldb::Options options;
	leveldb::Status status;
public:
	Leveldb() {
		options.create_if_missing = true;
	}
	~Leveldb()
	{
		delete db;
	}

	KeyRow SLGetOne(int w) {
		string v;
		KeyRow res;
		res.key = w;
		status = db->Get(leveldb::ReadOptions(), to_string(w), &v);	// get
		vector<string> triTmp = Util::split(v, "),");
		// 获取三元组
		for (vector<string>::iterator it_inner = triTmp.begin(); it_inner < triTmp.end() - 1; it_inner++) {
			Triple tt;
			char tB;
			// 从分割串中获取三元组数据
			sscanf((*it_inner).c_str(), "(%d,%d,%c", &(tt.node), &(tt.distance), &tB);
			tt.B = tB == 't' ? true : false;
			// 将三元组加入队列中
			res.triples.push_back(tt);
		}
		return res;
	}

	vector<KeyRow> SLGet(vector<int> query,string fileName) {
		this->status = leveldb::DB::Open(options, fileName, &db);
		assert(status.ok());
		vector<KeyRow> res;
		for (vector<int>::iterator it = query.begin(); it < query.end(); it++) {
			KeyRow t = this->SLGetOne(*it);
			res.push_back(t);
		}
		return res;
	}

	vector<int> SPGet(int p,string fileName) {
		string v;
		vector<int> res;
		this->status = leveldb::DB::Open(options, fileName, &db);
		assert(status.ok());
		status = db->Get(leveldb::ReadOptions(), to_string(p), &v);	// get
		vector<string> tmp=Util::split(v, ",");	// 处理获取到的字符串
		for (vector<string>::iterator it = tmp.begin(); it < tmp.end() - 1; it++) {
			res.push_back(stoi(*it));
		}
		return res;
	}



	//// 读取
	//status = db->Get(leveldb::ReadOptions(), k1, &v1);
	//assert(status.ok());
	//std::cout << "k1:" << k1 << "; v1:" << v1 << std::endl;

	// 删除
	/*status = db->Delete(leveldb::WriteOptions(), k2);
	assert(status.ok());
	std::cout << "Delete k2.." << std::endl;
	status = db->Get(leveldb::ReadOptions(), k2, &v2);
	if (!status.ok())
		std::cerr << "k2:" << k2 << "; " << status.ToString() << std::endl;
	else
		std::cout << "k2:" << k2 << "; v2:" << v2 << std::endl;*/


};