#include <memory>
#include "algo.h"

int n, m;
vector<int> available;
vector<vector<int>> maxRequest;

int main() {
	cout << "请输入两个整数，分别为线程数(n)和资源种类数(m): ";
	cin >> n >> m;
	cout << "请输入一个整数矩阵（" << n << " * " << m << "）。每行代表一个线程对各资源的最大需求: " << endl;
	for (int i = 1; i <= n; i++) {
		vector<int> tmp;
		for (int j = 1; j <= m; j++) {
			int x;
			cin >> x;
			tmp.push_back(x);
		}
		maxRequest.push_back(tmp);
	}
	cout << "请输入" << m << "个整数代表各类资源的可用数量: ";
	for (int i = 1; i <= m; i++) {
		int x;
		cin >> x;
		available.push_back(x);
	}
	unique_ptr<Bank> banker(new Bank(n, m, move(available), move(maxRequest)));
	if (banker->is_safe())
		cout << "\t\t[系统目前安全]" << endl;
	else {
		cout << "\t\t[系统不安全!]";
		return 0;
	}
	while (!banker->finished()) {
		cout << "请输入发起此次需求的线程编号（编号始于0）: ";
		int x;
		cin >> x;
		cout << "请输入" << m << "个整数代表本次请求的各类资源数量: ";
		vector<int> req;
		for (int i = 1; i <= m; i++) {
			int tmp;
			cin >> tmp;
			req.push_back(tmp);
		}
		if (banker->make_request(x, req))
			cout << "\t\t[成功!]" << endl;
		else {
			cout << "\t\t[失败!]" << endl;
			return 0;
		}
		banker->print();
	}
	cout << "\t\t[所有线程均已完成，资源交还系统!]";
	return 0;
}

/*
4 3

3 2 2
6 1 3
3 1 4
4 2 2

9 3 6

0 1 0 0
1 5 1 1
2 2 1 1
3 0 0 2

0 2 2 2
1 1 0 2
2 1 0 3
3 4 2 0
*/