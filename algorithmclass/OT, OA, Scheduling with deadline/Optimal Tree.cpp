#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <stdlib.h>

using namespace std;

vector<vector<double>> A; //�ּ����Ȯ��
vector<vector<int>>R;    //�ּҰ������ k ���� (root)
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

	for (int i = 1; i <= n; i++) //�ʱ�ȭ routine
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

			double min_ = 100000;	//�ּҰ��� �ʱⰪ�� 100000�� ���´�.
			double psum = 0;
			int min_k = 1000; //minimum�� �Ǵ� k�� �ּڰ� 1000���� �ʱ�ȭ

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
	int n; //key����

	cin >> n;

	vector <double> p(n + 1);

	Key.push_back(0);

	for (int i = 1; i < n + 1; i++)
	{
		cin >> p[i];				//�� key�� Ȯ��
		Key.push_back(i);			//key �ʱ�ȭ
	}
	cout << fixed;
	cout.precision(3);
	cout << optsearchtree(n, p) << " ";
	node * Opt_Tree = tree(1, n);		//���� tree ����

	preorder(Opt_Tree);					//tree ������ȸ

	free(Opt_Tree);
	
	return 0;
}