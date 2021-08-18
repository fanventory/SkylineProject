#include "Table.cpp"
#include "leveldb/db.h"
class Leveldb{
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
 
	// 写入文件SL
	void writeSL(Table &table,string fileName) {
 		this->status = leveldb::DB::Open(options, fileName, &db);
		assert(status.ok());
		vector<tripleRow> rows = table.getRow();
		for (vector<tripleRow>::iterator it = rows.begin(); it < rows.end(); it++) {
			string k = to_string((*it).keyword);	// 关键词作为键
			string v;	// 三元组作为值
			for (vector<triple>::iterator it_inner = (*it).triples.begin(); it_inner < (*it).triples.end(); it_inner++) {
				v.append("(" + to_string((*it_inner).index) + "," + to_string((*it_inner).distance) + "," + ((*it_inner).flag == true ? "t":"f") + "),");
			}
			// 写入
			status = db->Put(leveldb::WriteOptions(), k, v);
			assert(status.ok());
		}
	}
   
 
 	// 写入文件SP
	void writeSP(SPSkyline &spsl,string fileName) {
  		this->status = leveldb::DB::Open(options, fileName, &db);
		assert(status.ok());
		vector<SPSkylineNode> nodes = spsl.getNodes();
		for (vector<SPSkylineNode>::iterator it = nodes.begin(); it < nodes.end(); it++) {
			string k = to_string((*it).sePlace);	// 关键词作为键
			string v;	// 三元组作为值
			for (vector<int>::iterator it_inner = (*it).vertices.begin(); it_inner < (*it).vertices.end(); it_inner++) {
        if((*it).sePlace==*it_inner){
          // 过滤掉根节点
          continue;
        }
				v.append(to_string(*it_inner) + "," );
			}
			// 写入
			status = db->Put(leveldb::WriteOptions(), k, v);
			assert(status.ok());
		}
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