#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

float optsearchtree(int n, vector<float> p)
{
	vector<vector<float>> A; //최소평균확률

	int j;
	int diagonal;

	for (int i = 0; i < n+2; i++)
	{
		vector<float> element(n+1);
		A.push_back(element);
	}

	for (int i = 1; i <= n; i++)
	{
		A[i][i - 1] = 0;
		A[i][i] = p[i];
	}
	A[n + 1][n] = 0;

	for (diagonal = 1; diagonal <= n - 1; diagonal++)
	{
		for (int i = 1; i <= n - diagonal; i++) {
			
			j = i + diagonal;
			
			float min_ = 100000;	//최소값의 초기값을 100000로 놓는다.
			float psum = 0;
			for (int k = i; k <= j; k++)
			{
				if (min_ > A[i][k - 1] + A[k + 1][j])
				{
					min_ = A[i][k - 1] + A[k + 1][j];
				}
				psum += p[k];
			}
			A[i][j] = min_ + psum;
		}
		
	}
	return A[1][n]; //average number of key comparisons
}


int main()
{
	int n; //key개수

	cin >> n;

	vector <float> p(n+1);
	p[0] = 0;

	for (int i = 1; i < n+1; i++)
		cin >> p[i];

	cout << fixed;
	cout.precision(3);
	cout << optsearchtree(n, p) <<endl;

	return 0;
}