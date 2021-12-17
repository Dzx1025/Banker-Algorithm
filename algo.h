#include <vector>
#include <iostream>
#include <queue>
using namespace std;
namespace vectorcmp
{
    template<typename T>
    bool operator>(const vector<T>& lhs, const vector<T>& rhs)
    {
        for (int i = 0; i < lhs.size(); i++)
            if (lhs[i] > rhs[i])
                return true;
        return false;
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
    bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
    {
        for (int i = 0; i < lhs.size(); i++)
            if (lhs[i] > rhs[i])
                return false;
        return true;
    }
    template<typename T>
    bool iszero(const vector<T>& arg)
    {
        for (auto v : arg)
            if (v)
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
    bank(int ths, int res, vector<int>&& avlb, vector<vector<int>>&& max) : n(ths), m(res)
    {
        this->available = move(avlb);
        this->max = move(max);
        for (int i = 0; i < ths; i++)
        {
            vector<int> tmp;
            tmp.resize(res);
            allocation.push_back(tmp);
        }
        n_finished = 0;
        finish.resize(ths);
    }
    bool make_request(int x, const vector<int>& request)//x - ����������̣߳�request - ���ζԸ���Դ������
    {
        if (request + allocation[x] > max[x] || request > available || finish[x])//���������
            return false;
        available -= request;//���Է���
        allocation[x] += request;
        if (safe())//��ȫ�Լ��
        {
            if (iszero(need(x)))//�߳��˳�
                mark(x);
            return true;
        }
        else
        {
            available += request;
            allocation[x] -= request;
        }
        return false;
    }
    void print()const;
    bool safe()const;
    void mark(const int &arg)//�����̱��Ϊ�����
    {
        if (!finish[arg])
        {
            finish[arg] = true;
            available += allocation[arg];
            allocation[arg] = vector<int>(m, 0);
            n_finished++;
        }
    }
    bool finished()const{
        return n_finished == n;
    }
private:
    int n;//������
    int m;//��Դ������
    int n_finished;//���������
    vector<bool> finish;//����������
    vector<int> available;//��ǰM����Դ�Ŀ�����
    vector<vector<int>> max;//N�����̶�M����Դ���������
    vector<vector<int>> allocation;//��ǰ�Ѿ���N�����̷����M����Դ����
    vector<int> need(const int &x)const
    {
        return max[x] - allocation[x];
    }
};
void bank::print()const
{
    cout<<"------------------��ǰ���----------------"<<endl;
    cout<<"��ǰ������Դ :\t";
    for (auto v : available)
        cout<<v<<ends;
    cout<<endl;
    cout<<"���߳��ѷ�����Դ:"<<endl;
    cout<<"�̱߳��:";
    for (int i = 0; i < m; i++)
        printf("[%d]\t", i);
    cout<<endl;
    for (int i = 0; i < allocation.size(); i++)
    {
        if (finish[i])
            cout<<"\tFINISHED!";
        else
            for (int j = 0; j < allocation[i].size(); j++)
                printf("\t%d", allocation[i][j]);
        cout<<endl;
    }
    cout<<string(40, '-')<<endl;
}
bool bank::safe()const
{
    vector<int> keep = available;
    int now_fin = n_finished;
    vector<bool> finish = this->finish;
    queue<int> cpl_list;
    while (now_fin != n)//���в���ȫ����
    {
        bool change = false;
        for (int i = 0; i < n; i++)
            if (!finish[i] && need(i) <= keep)
            {
                keep += allocation[i];
                finish[i] = true;
                cpl_list.push(i);
                change = true;
                now_fin++;
            }
        if (!change)//û�н����ܹ���Ϊ��ȫ
            return false;
    }
    //�����ȫ����
    cout<<"��ȫ����Ϊ: ";
    while (!cpl_list.empty())
    {
        cout<<cpl_list.front()<<'\t';
        cpl_list.pop();
    }
    cout<<endl;
    return true;//���н��̾���Ϊ��ȫ
}