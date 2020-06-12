#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

//����� ù ��° �ٿ� optimal tour�� weight�� ���
//���� �ٿ��� optimal tour�� �̷�� �������� ��ȣ�� �湮�ϴ� ������� ���

typedef struct node
{
    int level;
    vector<int> path;
    int bound;
}node;

int n; //������ ����
int adj[16][16]; //�������
int minlength;   //�ּ� bound;
vector <int> opt_path; //opt_path


int bound(node v)
{
    int bound = 0;
    int path_check = 0;

    if (v.path.size() == 1)         //root�ΰ��
    {
        for (int i = 1; i <= n; i++)
        {
            int min_ = 10000;
            for (int k = 1; k <= n; k++)
            {
                if (i != k)
                    min_ = min(min_, adj[i][k]);
            }
            bound += min_;
        }
        return bound;
    }

    while (path_check < v.path.size() - 1) //��� ������ bound ���ϱ�
    {
        bound += adj[v.path[path_check]][v.path[path_check + 1]];   //������Ŀ��� ������
        path_check++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (find(v.path.begin(), v.path.end(), i) != v.path.end()) //path�� �����ϸ鼭
            if (i != v.path[v.path.size() - 1])                  //path�� �� ���� �ƴ϶��
                continue;

        int min_ = 10000;
        for (int k = 1; k <= n; k++)
        {
            if (i == k) continue;

            if (i == v.path[v.path.size() - 1])                  //path�� �� ���̸�
            {
                if ( find(v.path.begin(), v.path.end(), k) != v.path.end())   //�ڱ� �ڽ��̰ų�, path�� ���� ���̸� 
                    continue;
            }

            else
                if ( find(v.path.begin(), v.path.end(), k) != v.path.end())      //�ڱ� �ڽ��̰ų�, path�� ���� �� �� 1�� �ƴ϶��
                    if (k != 1)
                        continue;

            min_ = min(min_, adj[i][k]);                  //�� �ະ �ּҰ� ���ϱ�
        }
        bound += min_;
    }

    return bound;                                 //bound ���
}

int length(node u)
{
    int length = 0;
    int pathcheck = 0;

    while (pathcheck < u.path.size() - 1) {
        length += adj[u.path[pathcheck]][u.path[pathcheck + 1]];
        pathcheck++;
    }
    return length;

}

struct cmp {
    bool operator() (node a, node b) {      //bound �� ������ ����
        //if (a.bound == b.bound)return a.level > b.level;
        return a.bound > b.bound;
    }
};

void travel2()
{
    priority_queue <node, vector<node>, cmp>PQ;
    node v;

    v.level = 0;
    v.path.push_back(1);
    v.bound = bound(v);         //bound ���ϱ�
    minlength = 10000;
    PQ.push(v);

    while (!PQ.empty())
    {
        node u;
        v = PQ.top();      //Remove node with best bound
        PQ.pop();
        if (v.bound < minlength)
        {
            u.level = v.level + 1;
            for (int i = 2; i <= n; i++)
            {
                if (find(v.path.begin(), v.path.end(), i) != v.path.end()) //i�� path�ȿ� ������
                    continue;

                u.path = v.path;
                u.path.push_back(i);

                if (u.level == n - 2)                                 //������ 2��°�� ����
                {
                    for (int k = 2; k <= n; k++)
                    {
                        if (find(u.path.begin(), u.path.end(), k) == u.path.end()) //k�� path�ȿ� ������
                        {
                            u.path.push_back(k);               //������ ���� path �߰��ϰ�
                            break;                           //break;
                        }
                    }
                    u.path.push_back(1);                  //1�߰�

                    int length_;
                    if ((length_ =length(u)) < minlength)         //u�� �ּҰ��̸� 
                    {                                    //length ����
                        minlength = length_;
                        opt_path = u.path;                     //opt_path ����
                    }
                }
                else {
                    u.bound = bound(u);
                    if (u.bound < minlength) PQ.push(u);
                }
            }
        }
    }

}


int main()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
        for (int k = 1; k <= n; k++)
            cin >> adj[i][k];      //������� ����

    if (n == 1)
    {
        cout << 0 << "\n" << n;
        return 0;
    }

    else if (n == 2)
    {
        node u;
        u.path.push_back(1);
        u.path.push_back(2);
        u.path.push_back(1);
        minlength = length(u);

        cout << minlength << endl;
        for (int i = 0; i < u.path.size(); i++)
            cout << u.path[i] << " ";
        
        return 0;
    }

    travel2();
    cout << minlength << "\n";
    
    for (int k = 0; k < opt_path.size(); k++)
        cout << opt_path[k] << " ";

    return 0;
}