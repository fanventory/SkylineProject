#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <queue>
#include <map>
#pragma once
#ifndef EDGE
#define EDGE
using namespace std;

// 坐标
struct Coordinate
{
	double x;
	double y;
};

// 图节点信息
struct Node {
	vector<int> keyword;
	vector<int> edge;
	bool isExist;	// 存在性标识
	bool flag;		// 节点类型，true为带坐标节点，false为不带坐标节点
	Coordinate coordinate;	// 若为带坐标节点，该结构体储存坐标的x、y坐标
};

struct KSDL {
	map<int, int> w;
};

struct SPSkylineNode {
	vector<KSDL> L;
	int sePlace;	// 语义地点
	vector<int> vertices;	// 记录子图中所以的位置节点
	SPSkylineNode() {
		L.resize(4);
	}
	SPSkylineNode(int p):sePlace(p) {
		L.resize(4);
	}
};

// 输出三元组
struct triple
{
	int index;	// 根节点
	int distance;	//	根节点到关键词距离
	bool flag;	// 当存在比根节点更近的语义地点到达该关键词时，该值为true
	triple(int i,int d,int f):index(i),distance(d),flag(f){}
};

struct tripleRow {
	vector<triple> triples;
	int keyword;
};
#define rowNum 20
#endif