//	����kosaraju�㷨�ļ�������ɸ��������ͨ�����ĵ�
#include "Kosaraju.cpp"

class ConnectTable
{
private:
	map<int, int> table;
public:
	ConnectTable(map<int, int> origin,int n) {
		int *groups = (int*)malloc(sizeof(int) * (n + 1));
		memset(groups, 0, sizeof(int) * (n + 1));	//	��ʼ��Ϊ0
		for (map<int, int>::iterator it = origin.begin(); it != origin.end(); it++) {
			groups[(*it).second]++;	//	��ÿ����ͨ�����Ľڵ�����һ������
		}
		map<int, vector<int>> conList;
		for (map<int, int>::iterator it = origin.begin(); it != origin.end(); it++) {
			if (groups[(*it).second] > 1) {
				if (conList.find((*it).second) == conList.end()) {	//	�����ֵ���Ŀ
					conList[(*it).second] = vector<int>();
				}
				conList[(*it).second].push_back((*it).first);
			}
		}
		for (map<int, vector<int>>::iterator it = conList.begin(); it != conList.end(); it++) {
			int virtualNode=(*it).second.front();	//	����һ�������Ϊ����������ڵ㣬ָ������ǿ��ͨ�Ľ��
			for (vector<int>::iterator it_inner = (*it).second.begin(); it_inner != (*it).second.end(); it_inner++) {
				this->table[(*it_inner)] = virtualNode;
			}
		}
	}
	map<int, int> getTable() {
		return this->table;
	}
	void write(string fileName) {
		ofstream outfile;
		outfile.open(fileName.data());   // ���ļ����������ļ��������� 
		assert(outfile.is_open());   // ��ʧ��,�����������Ϣ,����ֹ��������

		for (map<int, int>::iterator it = this->table.begin(); it != this->table.end(); it++) {
			outfile << (*it).first << "," << (*it).second << endl;
		}
		outfile.close();
	}
};
