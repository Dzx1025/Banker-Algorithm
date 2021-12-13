#include<vector>
#include<deque>
#include<iostream>
#define DEBUG
using namespace std;
namespace vectorcmp
{
	template<typename T>
	bool operator>(const vector<T>& lhs, const vector<T>& rhs)
	{
		for (int i = 0; i < lhs.size(); i++)
			if (lhs[i] <= rhs[i])
				return false;
		return true;
	}
	template<typename T>
	bool operator<(const vector<T>& lhs, const vector<T>& rhs)
	{
		for (int i = 0; i < lhs.size(); i++)
			if (lhs[i] >= rhs[i])
				return false;
		return true;
	}
	template<typename T>
	vector<T> operator+(const vector<T> &arg0, const vector<T> &arg1)
	{
		vector<T> tmp;
		tmp.resize(arg0.size());
		for (int i = 0; i < arg0.size(); i++)
			tmp[i] = arg0[i] + arg1[i];
		return tmp;
	}
	template<typename T>
	vector<T> operator-(const vector<T> &arg0, const vector<T> &arg1)
	{
		vector<T> tmp;
		tmp.resize(arg0.size());
		for (int i = 0; i < arg0.size(); i++)
			tmp[i] = arg0[i] - arg1[i];
		return tmp;
	}
	template<typename T>
	vector<T>& operator+=(vector<T> &src, const vector<T> &arg)
	{
		for (int i = 0; i < src.size(); i++)
			src[i] += arg[i];
		return src;
	}
	template<typename T>
	vector<T>& operator-=(vector<T> &src, const vector<T> &arg)
	{
		for (int i = 0; i < src.size(); i++)
			src[i] -= arg[i];
		return src;
	}
}
using namespace vectorcmp;
class bank
{
	public:
		bank() = delete;
		bank(int n, int m, vector<int>&& avlb, vector<vector<int>>&& max)
		{
			this->n= n;
			this->m= m;
			this->available = move(avlb);
			this->max = move(max);
		}
		bool make_request(int x, vector<int> request)
		{
			//���������
			if (request + allocation[x] > max[x] || request > available)
				return false;
			//���Է���
			available -= request;
			allocation[x] += request;
			//��ȫ�Լ��
			if (safe())
				return true;
			else
			{
				available += request;
				allocation[x] -= request;
			}
			return false;
		}
		bool safe()const;
#ifdef DEBUG
		void print()const
		{
			cout<<"available = []\n";
			for (auto v : available)
				cout<<v<<ends;
			cout<<endl<<"max = [][]"<<endl;
			for (auto u : max)
			{
				for (auto v : u)
					cout<<v<<ends;
				cout<<endl;
			}
		}
#endif
	private:
		int n;//������
		int m;//��Դ������
		vector<int> available;//��ǰM����Դ�Ŀ�����
		vector<vector<int>> max;//N�����̶�M����Դ���������
		vector<vector<int>> allocation;//��ǰ�Ѿ���N�����̷����M����Դ����
		int need(const int& x, const int& y)const
		{
			return max[x][y] - allocation[x][y];
		}
		const vector<int> need(const int &x)const
		{
			auto tmp = max[x] - allocation[x];
			return tmp;
		}
};
bool bank::safe()const
{
	vector<int> keep = available;
	int cnt_fin = 0;
	vector<bool> finish(n, false);
	while (cnt_fin != n)//���в���ȫ����
	{
		bool change = false;
		for (int i = 0; i < n; i++)
			if (!finish[i] && need(i) <= keep)
			{
				keep += allocation[i];
				finish[i] = true;
				change = true;
				cnt_fin++;
			}
		if (!change)//û�н����ܹ���Ϊ��ȫ
			return false;
	}
	return true;//���н��̾���Ϊ��ȫ
}
