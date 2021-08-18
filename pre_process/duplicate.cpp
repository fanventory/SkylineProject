#include <cassert>
#include <string>
#include <iostream>
#include "leveldb/db.h"


// 输出所有的倒排索引组
// 命令：g++ duplicate.cpp libleveldb.a -lpthread -I ../../leveldb/include  -o outputIndex
// 命令：./outputIndex

int main(){
        leveldb::DB* db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options,"/home/zhangzf/program/SPSLGraph/db/SLdb", &db);
        assert(status.ok());
         
         
         leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
         for (it->SeekToFirst(); it->Valid(); it->Next()) {
             std::cout << it->key().ToString() << ": " << it->value().ToString() << std::endl;
            //  std::string k = it->key().ToString()+":";
            //  std::string v = it->value().ToString();
		      	//  std::cout<<k<<v<<std::endl;
         }
        assert(it->status().ok());
        
        delete it;
        delete db;
        return 0;
}