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
    if (x.deadline == y.deadline)       //deadline�� ������ job�������� ��
        return x.job < y.job;
    else
        return x.deadline < y.deadline; //deadline �ٸ��� deadline �������� ��
}

void OptDeadline(vector<dataset> feasible_seq)
{
    for (int i = 0; i < n; i++)
    {
        fposition = Data[i].deadline - 1;    //feasible�� data���� üũ�ϱ� ���ؼ� deadline - 1���� ��ġ�� ������� üũ
        while (1)
        {

            if (check[fposition] == 0) //feasible��ġ�� ������� Ȯ��
            {
                check[fposition] = 1;               //feasible ä��ɷ� �����
                feasible_seq.push_back(Data[i]);    //feasible sequence�� data�� �߰�
                opt_profit += Data[i].profit;        //optimal profit�� data profit ���ϱ�
                break;
            }
            else  //feasible��ġ�� ������� ������, �Ʒ� fposition --;
            {
                fposition--;
                if (fposition < 0) break; //���� fposition�� 0���� ��������, �� data�� feasible�� data�� �ƴ�
            }

        }
    }

    sort(feasible_seq.begin(), feasible_seq.end(), SortRule); //SortRule�� ���� feasible_sequence�� sorting�Ѵ�.
    

    cout << opt_profit << " ";                      //���
    for (int i = 0; i < feasible_seq.size(); i++)
    {
        cout << feasible_seq[i].job << " ";
    }
}


int main()
{
    cin >> n;

    for (int i = 0; i < n; i++) // profit���� ������������ �Է¹���
    {
        cin >> Data[i].job >> Data[i].deadline >> Data[i].profit;
        maxdeadline = max(maxdeadline, Data[i].deadline);
    }
    vector<dataset>feasible_seq;
    check.assign(maxdeadline, 0);   //�ڸ� �������� üũ�ϱ� ���� check vector

    OptDeadline(feasible_seq);

   
    return 0;
}