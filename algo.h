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
			//需求合理性
			if (request + allocation[x] > max[x] || request > available)
				return false;
			//尝试分配
			available -= request;
			allocation[x] += request;
			//安全性检查
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
		int n;//进程数
		int m;//资源类型数
		vector<int> available;//当前M个资源的可用性
		vector<vector<int>> max;//N个进程对M个资源的最大需求
		vector<vector<int>> allocation;//当前已经给N个进程分配的M个资源数量
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
	while (cnt_fin != n)//尚有不安全进程
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
		if (!change)//没有进程能够变为安全
			return false;
	}
	return true;//所有进程均变为安全
}
