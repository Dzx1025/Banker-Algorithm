#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

namespace vectorCmp {
	template<typename T>
	bool operator>(const vector<T> &lhs, const vector<T> &rhs) {
		for (int i = 0; i < lhs.size(); i++)
			if (lhs[i] > rhs[i])
				return true;
		return false;
	}

	template<typename T>
	bool operator<(const vector<T> &lhs, const vector<T> &rhs) {
		for (int i = 0; i < lhs.size(); i++)
			if (lhs[i] >= rhs[i])
				return false;
		return true;
	}

	template<typename T>
	bool operator<=(const vector<T> &lhs, const vector<T> &rhs) {
		for (int i = 0; i < lhs.size(); i++)
			if (lhs[i] > rhs[i])
				return false;
		return true;
	}

	template<typename T>
	bool is_zero(const vector<T> &arg) {
		return std::all_of(arg.begin(), arg.end(), [&](const auto &t) { return !t; });
	}

	template<typename T>
	vector<T> operator+(const vector<T> &arg0, const vector<T> &arg1) {
		vector<T> tmp(arg0.size());
		for (int i = 0; i < arg0.size(); i++)
			tmp[i] = arg0[i] + arg1[i];
		return tmp;
	}

	template<typename T>
	vector<T> operator-(const vector<T> &arg0, const vector<T> &arg1) {
		vector<T> tmp(arg0.size());
		for (int i = 0; i < arg0.size(); i++)
			tmp[i] = arg0[i] - arg1[i];
		return tmp;
	}

	template<typename T>
	vector<T> &operator+=(vector<T> &src, const vector<T> &arg) {
		for (int i = 0; i < src.size(); i++)
			src[i] += arg[i];
		return src;
	}

	template<typename T>
	vector<T> &operator-=(vector<T> &src, const vector<T> &arg) {
		for (int i = 0; i < src.size(); i++)
			src[i] -= arg[i];
		return src;
	}
}
using namespace vectorCmp;

class Bank {
public:
	Bank() = delete;

	Bank(int ths, int res, vector<int> &&available, vector<vector<int>> &&max)
			: n(ths), m(res), available(available), max(max), allocation(ths, vector<int>(res)), n_finished(0),
			  finish(ths) {}

	bool make_request(int x, const vector<int> &request)    //x - 提起需求的线程，request - 本次对各资源的需求
	{
		if (request + allocation[x] > max[x] || request > available || finish[x])   //需求合理性
			return false;
		available -= request;   //尝试分配
		allocation[x] += request;
		if (is_safe())  //安全性检查
		{
			if (is_zero(need(x)))   //线程退出
				mark(x);
			return true;
		} else {
			available += request;
			allocation[x] -= request;
		}
		return false;
	}

	void print() const;

	[[nodiscard]] bool is_safe() const;

	void mark(const int arg)   //将进程标记为已完成
	{
		if (!finish[arg]) {
			finish[arg] = true;
			available += allocation[arg];
			allocation[arg] = vector<int>(m, 0);
			n_finished++;
		}
	}

	[[nodiscard]] bool finished() const {
		return n_finished == n;
	}

private:
	int n;                          //进程数
	int m;                          //资源类型数
	int n_finished;                 //已完成数量
	vector<bool> finish;            //进程完成情况
	vector<int> available;          //当前M个资源的可用性
	vector<vector<int>> max;        //N个进程对M个资源的最大需求
	vector<vector<int>> allocation; //当前已经给N个进程分配的M个资源数量

	[[nodiscard]] vector<int> need(const int &x) const {
		return max[x] - allocation[x];
	}
};

void Bank::print() const {
	cout << "------------------当前情况----------------" << endl;
	cout << "当前可用资源 :\t";
	for (auto v: available)
		cout << v << ' ';
	cout << endl;
	cout << "各线程已分配资源:" << endl;
	cout << "线程编号:";
	for (int i = 0; i < m; i++)
		printf("[%d]\t", i);
	cout << endl;
	for (int i = 0; i < allocation.size(); i++) {
		if (finish[i])
			cout << "\tFINISHED!";
		else
			for (int j: allocation[i])
				printf("\t%d", j);
		cout << endl;
	}
	cout << string(40, '-') << endl;
}

bool Bank::is_safe() const {
	vector<int> keep(available);
	int now_fin = n_finished;
	vector<bool> is_finish(finish);
	queue<int> cpl_list;
	while (now_fin != n)    //尚有不安全进程
	{
		bool change = false;
		for (int i = 0; i < n; i++)
			if (!is_finish[i] && need(i) <= keep) {
				keep += allocation[i];
				is_finish[i] = true;
				cpl_list.push(i);
				change = true;
				now_fin++;
			}
		if (!change)    //没有进程能够变为安全
			return false;
	}
	//输出安全序列
	cout << "安全序列为: ";
	while (!cpl_list.empty()) {
		cout << cpl_list.front() << ' ';
		cpl_list.pop();
	}
	cout << endl;
	return true;    //所有进程均变为安全
}
