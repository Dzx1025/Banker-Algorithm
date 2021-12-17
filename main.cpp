#include <iostream>
#include <vector>
#include "algo.h"
#define DEBUG
using namespace std;
int n, m;
vector<int> avlb;
vector<vector<int>> maxx;
int main()
{
    cout<<"�����������������ֱ�Ϊ�߳��� n ����Դ������ m :"<<endl;
    cin>>n>>m;
    cout<<"������һ����������( "<<n<<" * "<<m<<" ). ÿ�д���һ���̶߳Ը���Դ���������:"<<endl;
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
    cout<<"������ "<<m<<" ���������������Դ�Ŀ�������:"<<endl;
    for (int i = 1; i <= m; i++)
    {
        int x;
        cin>>x;
        avlb.push_back(x);
    }
    bank* banker = new bank(n, m, move(avlb), move(maxx));
    if (banker->safe())
        cout<<"ϵͳ��ȫ!"<<endl;
    else
    {
        cout<<"ϵͳ����ȫ!";
        return 0;
    }
    while (!banker->finished())
    {
        cout<<"�����뷢��˴�������̱߳��(���ʼ��0) :";
        int x;
        cin>>x;
        cout<<"������ "<<m<<" ����������������ĸ�����Դ����:"<<endl;
        vector<int> req;
        req.clear();
        for (int i = 1; i <= m; i++)
        {
            int tmp;
            cin>>tmp;
            req.push_back(tmp);
        }
        if (banker->make_request(x, req))
            cout<<"\t\t�ɹ�!"<<endl;
        else
            cout<<"\t\tʧ��!"<<endl;
        banker->print();
    }
    cout<<"�����߳̾�����ɣ���Դ����ϵͳ��";
    return 0;
}