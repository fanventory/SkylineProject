#include "head.h"


class Util {
public:
	/*
		功  能：按行读取文件
		参  数：文件名
		返回值：存储文件行的列表
	*/
	static const vector<string> readFile(string fileName) {
		// 打开文件
		vector<string> res;
		ifstream infile;
		infile.open(fileName.data());   // 将文件流对象与文件连接起来 
		assert(infile.is_open());   // 若失败,则输出错误消息,并终止程序运行
		string s;

		// 跳过第一行
		getline(infile, s);
		while (getline(infile, s)) // 读取所有数据
		{
			res.push_back(s);
		}

		//for (int i = 0; i < rowNum; i++)	// 读取前rowNum行数据
		//{
		//	getline(infile, s);
		//	res.push_back(s);
		//}
		infile.close();
		return res;
	}

	/*
		功  能：获取文件行数
		参  数：文件名
		返回值：文件行数
	*/
	static const int countFileRows(string fileName) {
		FILE *pFile;
		int c;
		int n = 0;
		pFile=fopen64(fileName.data(), "r");
		if (pFile == NULL)
		{
			return -1;
		}
		else
		{
			do {
				c = fgetc(pFile);
				if (c == '\n')
					n++;
			} while (c != EOF);
		}
		return n;
	}

	/*
		功  能：读取文件最后一行
		参  数：文件名
		返回值：文件最后一行字符串
	*/
	static const string endFileRow(string fileName) {
		// 打开文件
		ifstream ifs(fileName.c_str(), fstream::in);
		if (!ifs) {
			cout << "Read file failed!" << std::endl;
			return "";
		}
		// 定位到结尾最后一个字符
		ifs.seekg(0, ifs.end);
		// 计算当前位置，获取文件长度
		long long length = ifs.tellg();
		
		string line;
		int index = -2;
		int linenum = 0;
		while (length)
		{
			char c;
			// 定位到倒数第index个字符的位置
			ifs.seekg(index, ifs.end);
			// 获取该字符
			ifs.get(c);
			// 如果字符为换行符，则倒数第index个位置到末尾即为最后一行
			if (c == '\n')
			{
				// 获取最后一行字符串
				getline(ifs, line);
				// 转化为字符串流，并读取字符串
				istringstream iss(line);
				iss >> linenum;
				break;
			}
			length--;
			index--;
		}

		return line;
	}

	/*
		功  能：由文件最后一行获取最大节点数
		参  数：文件名列表
		返回值：最大节点数
	*/
	static const int getMaxNodeNum(vector<string> fileNames) {
		vector<int> res;
		// 获取每个文件最后一行的节点值
		for (vector<string>::iterator it = fileNames.begin(); it < fileNames.end(); it++) {
			string line = endFileRow(*it);
			vector<string> t = Util::split(line, ":");
			res.push_back(stoi(t.front()));
		}

		vector<int>::iterator maxPosition = max_element(res.begin(), res.end());
		return *maxPosition;
	}

	/*
		功  能：字符串切割函数
		参  数：待切割字符串，分隔符字符串
		返回值：被切割字符串列表
	*/
	static const vector<string> split(string str, string pattern)
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

	/*
		功  能：vector二分查找
		参  数：vector列表，目标节点
		返回值：返回目标节点位置的迭代器
	*/
	static const int binaryFind(vector<int> &list, int node)
	{
		int low = 0;
		int high = list.size() - 1;
		int mid;
		while (high>=low)
		{
			mid = (low + high) / 2;
			if (list[mid]==node)
			{
				cout << ">>>>>>>>>>>>>>>>>>存在重边>>>>>>>>>>>>>>>>"<<endl;
				return mid;
			}
			else if (list[mid] > node)
			{
				high = mid-1;
			}
			else
			{
				low = mid + 1;
			}
			
		}
		return  low;
	}
};
