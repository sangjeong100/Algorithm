#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


//출력
//n-Queens problem의 첫 번째 solution이 담겨있는 배열 col
//backtracking으로 탐색한 state space tree의 노드 개수 
//promising nodes 개수 (선택된)
//모든 solution의 개수

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
		
		//새로운 퀸과 기존 퀸 같은 행 or 대각선에 있을 경우
		if (col[i] == col[k] || abs(col[i] - col[k]) == i - k)
		{
			switch_ = false; //실패
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
	cin >> n; //n값 입력

	queens(0);
	
	if (solution_count == 0)
		cout << "No solution";
	else
		cout <<state_space_tree_nodes <<" "<<promising_nodes << " "<<solution_count;

	return 0;

}