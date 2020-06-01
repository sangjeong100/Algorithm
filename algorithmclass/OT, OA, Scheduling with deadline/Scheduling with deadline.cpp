//Scheduling with deadline

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct dataset
{
    int job;
    int deadline;
    int profit;
}dataset; 

dataset Data[101];
vector<int> check;

int opt_profit = 0;
int n;
int fposition = 0;
int maxdeadline = 0;

bool SortRule(dataset x, dataset y)     //feasible_sequence Sorting Rule
{
    if (x.deadline == y.deadline)       //deadline이 같으면 job기준으로 비교
        return x.job < y.job;
    else
        return x.deadline < y.deadline; //deadline 다르면 deadline 기준으로 비교
}

void OptDeadline(vector<dataset> feasible_seq)
{
    for (int i = 0; i < n; i++)
    {
        fposition = Data[i].deadline - 1;    //feasible한 data인지 체크하기 위해서 deadline - 1부터 위치가 비었는지 체크
        while (1)
        {

            if (check[fposition] == 0) //feasible위치가 비었는지 확인
            {
                check[fposition] = 1;               //feasible 채운걸로 만들고
                feasible_seq.push_back(Data[i]);    //feasible sequence에 data를 추가
                opt_profit += Data[i].profit;        //optimal profit에 data profit 더하기
                break;
            }
            else  //feasible위치가 비어있지 않으면, 아래 fposition --;
            {
                fposition--;
                if (fposition < 0) break; //만약 fposition이 0보다 적어지면, 이 data는 feasible한 data가 아님
            }

        }
    }

    sort(feasible_seq.begin(), feasible_seq.end(), SortRule); //SortRule에 따라서 feasible_sequence를 sorting한다.
    

    cout << opt_profit << " ";                      //출력
    for (int i = 0; i < feasible_seq.size(); i++)
    {
        cout << feasible_seq[i].job << " ";
    }
}


int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) // profit기준 내림차순으로 입력받음
    {
        cin >> Data[i].job >> Data[i].deadline >> Data[i].profit;
        maxdeadline = max(maxdeadline, Data[i].deadline);
    }
    vector<dataset>feasible_seq;
    check.assign(maxdeadline, 0);   //자리 차지한지 체크하기 위한 check vector

    OptDeadline(feasible_seq);

   
    return 0;
}