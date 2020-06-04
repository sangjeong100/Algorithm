#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


//���
//n-Queens problem�� ù ��° solution�� ����ִ� �迭 col
//backtracking���� Ž���� state space tree�� ��� ���� 
//promising nodes ���� (���õ�)
//��� solution�� ����

int col[13] = { 0 ,};
int n;
int solution_count = 0;
int state_space_tree_nodes = 0;
int promising_nodes = 0;


bool promising(int i)
{
	state_space_tree_nodes++;

	int k;
	bool switch_;
	int temp_promising = 0;	
	
	k = 1;
	switch_ = true;
	
	while (k < i && switch_)
	{
		
		//���ο� ���� ���� �� ���� �� or �밢���� ���� ���
		if (col[i] == col[k] || abs(col[i] - col[k]) == i - k)
		{
			switch_ = false; //����
		}
		k++;
	}

	return switch_;
}


void queens(int i)
{
	int j;

	if (promising(i))
	{
		promising_nodes++;

		if (i == n)
		{
			if(solution_count == 0)
			{
				for (int a = 1; a <= n; a++)
					cout << col[a] << " ";
			}
			solution_count++;
		}
		else
		{
			for (j = 1; j <= n; j++)
			{
				col[i + 1] = j;
				queens(i + 1);
			}
		}

	}

}


int main()
{
	cin >> n; //n�� �Է�

	queens(0);
	
	if (solution_count == 0)
		cout << "No solution";
	else
		cout <<state_space_tree_nodes <<" "<<promising_nodes << " "<<solution_count;

	return 0;

}