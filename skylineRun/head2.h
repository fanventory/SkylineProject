#include<vector>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stack>
using namespace std;
#pragma once

// 存储倒排索引
struct Triple {
	int node;	// 节点
	int distance;	// 距离
	bool B;	// 是否为到关键词最近的节点
	Triple() {};
	Triple(int n,int d,bool b):node(n),distance(d),B(b){}
};

struct KeyRow{
	vector<Triple> triples;	// 三元组序列
	int key;	// 关键词
};

// 存储图结构
struct Node {
	int node;
	vector<int> edge;
};

// 存储TL_LABEL查询的节点数据结构
struct queryNode {
	int from;
	int to;
	queryNode() {}
	queryNode(int f,int t):from(f),to(t){}
};

// 存储结点到关键词的距离
struct keyDist {
	int key;	//	关键词
	int dist;	//	距离
	keyDist() {}
	keyDist(int k, int d) :key(k), dist(d) {}
};