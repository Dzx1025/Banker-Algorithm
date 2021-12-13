#include <iostream>
#include <vector>
#include "algo.h"
#define DEBUG
using namespace std;
int n, m;
vector<int> avlb;
vector<vector<int>> maxx;
int main(int argc, char** argv)
{
	cout<<"Two integer following, the quantity of threads(n) and the variety of resource(m):"<<endl;
	cin>>n>>m;
	cout<<"Input the max-demand integral matrix("<<n<<"*"<<m<<"). Each line represents a thread:"<<endl;
	for (int i = 1; i <= n; i++)
	{
		vector<int> tmp;
		tmp.clear();
		for (int j = 1; j <= m; j++)
		{
			int x;
			cin>>x;
			tmp.push_back(x);
		}
		maxx.push_back(tmp);
	}
	cout<<"Input "<<m<<" integers in one line representing the available quantity of each resource:"<<endl;
	for (int i = 1; i <= m; i++)
	{
		int x;
		cin>>x;
		avlb.push_back(x);
	}
	bank* banker = new bank(n, m, move(avlb), move(maxx));
	banker->print();
	cout<<banker->safe();
	return 0;
}
