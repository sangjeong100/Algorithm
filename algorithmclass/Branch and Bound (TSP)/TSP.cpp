#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

//출력은 첫 번째 줄에 optimal tour의 weight를 출력
//다음 줄에는 optimal tour를 이루는 정점들의 번호를 방문하는 순서대로 출력

typedef struct node
{
    int level;
    vector<int> path;
    int bound;
}node;

int n; //정점의 개수
int adj[16][16]; //인접행렬
int minlength;   //최소 bound;
vector <int> opt_path; //opt_path


int bound(node v)
{
    int bound = 0;
    int path_check = 0;

    if (v.path.size() == 1)         //root인경우
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

    while (path_check < v.path.size() - 1) //경로 정해진 bound 더하기
    {
        bound += adj[v.path[path_check]][v.path[path_check + 1]];   //인접행렬에서 가져옴
        path_check++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (find(v.path.begin(), v.path.end(), i) != v.path.end()) //path에 존재하면서
            if (i != v.path[v.path.size() - 1])                  //path의 끝 값이 아니라면
                continue;

        int min_ = 10000;
        for (int k = 1; k <= n; k++)
        {
            if (i == k) continue;

            if (i == v.path[v.path.size() - 1])                  //path의 끝 값이면
            {
                if ( find(v.path.begin(), v.path.end(), k) != v.path.end())   //자기 자신이거나, path의 안의 값이면 
                    continue;
            }

            else
                if ( find(v.path.begin(), v.path.end(), k) != v.path.end())      //자기 자신이거나, path의 안의 값 중 1이 아니라면
                    if (k != 1)
                        continue;

            min_ = min(min_, adj[i][k]);                  //각 행별 최소값 구하기
        }
        bound += min_;
    }

    return bound;                                 //bound 출력
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
    bool operator() (node a, node b) {      //bound 비교 연산자 구현
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
    v.bound = bound(v);         //bound 구하기
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
                if (find(v.path.begin(), v.path.end(), i) != v.path.end()) //i가 path안에 있으면
                    continue;

                u.path = v.path;
                u.path.push_back(i);

                if (u.level == n - 2)                                 //끝에서 2번째에 도달
                {
                    for (int k = 2; k <= n; k++)
                    {
                        if (find(u.path.begin(), u.path.end(), k) == u.path.end()) //k가 path안에 없으면
                        {
                            u.path.push_back(k);               //마지막 남은 path 추가하고
                            break;                           //break;
                        }
                    }
                    u.path.push_back(1);                  //1추가

                    int length_;
                    if ((length_ =length(u)) < minlength)         //u가 최소값이면 
                    {                                    //length 대입
                        minlength = length_;
                        opt_path = u.path;                     //opt_path 저장
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
            cin >> adj[i][k];      //인접행렬 구성

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