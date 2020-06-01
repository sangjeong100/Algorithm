#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdlib.h>

using namespace std;

vector<vector<double>> A; //최소평균확률
vector<vector<int>>R;    //최소값만드는 k 저장 (root)
vector<int> Key;

typedef struct node
{
	int key;
	struct node * left;
	struct node * right;
}node;

node* tree(int i,int j)
{
	int k = R[i][j];
	
	if (k == 0)
		return NULL;
	
	node* p = (node*)malloc(sizeof(node));

	p->key = Key[k];
	p->left = tree(i, k - 1);
	p->right = tree(k + 1, j);
	return p;


}

float optsearchtree(int n, vector<double> p)
{

	int j;
	int diagonal;

	for (int i = 0; i < n + 2; i++)
	{
		vector<double> element(n + 1);
		vector<int> element2(n + 1);
		
		A.push_back(element);
		R.push_back(element2);
	}

	for (int i = 1; i <= n; i++) //초기화 routine
	{
		A[i][i - 1] = 0;
		A[i][i] = p[i];
		R[i][i] = i;
		R[i][i - 1] = 0;
	}
	A[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (int i = 1; i <= n - diagonal; i++) {

			j = i + diagonal;

			double min_ = 100000;	//최소값의 초기값을 100000로 놓는다.
			double psum = 0;
			int min_k = 1000; //minimum이 되는 k의 최솟값 1000으로 초기화

			for (int k = i; k <= j; k++)
			{
				if (min_ > A[i][k - 1] + A[k + 1][j])
				{
					min_ = A[i][k - 1] + A[k + 1][j];
	
						min_k = k;
				}
				psum += p[k];
			}
			R[i][j] = min_k;
			A[i][j] = min_ + psum;
		}

	}
	return A[1][n]; //average number of key comparisons
}

void preorder(node* p)
{
	if (p == NULL)
		return;
	
	cout << p->key << ' ';
	preorder(p->left);
	preorder(p->right);
	return;
}

int main()
{
	int n; //key개수

	cin >> n;

	vector <double> p(n + 1);

	Key.push_back(0);

	for (int i = 1; i < n + 1; i++)
	{
		cin >> p[i];				//각 key의 확률
		Key.push_back(i);			//key 초기화
	}
	cout << fixed;
	cout.precision(3);
	cout << optsearchtree(n, p) << " ";
	node * Opt_Tree = tree(1, n);		//최적 tree 생성

	preorder(Opt_Tree);					//tree 전위순회

	free(Opt_Tree);
	
	return 0;
}