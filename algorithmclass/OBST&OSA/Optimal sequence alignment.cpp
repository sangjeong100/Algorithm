#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

float opt_align[102][102];
float gap_penalty;
float mismatch_penalty;
string x;
string y;
int m, n;


void opt() 
{
	float penalty;
	int i, j; //x,y참조 위치
	for (i = m - 1; i >= 0; i--)
		for (j = n - 1; j >= 0; j--)
		{
			if (x[i] == y[j]) penalty = 0;
			else penalty = mismatch_penalty;

			opt_align[i][j] = min(opt_align[i + 1][j + 1] + penalty, min(opt_align[i + 1][j] + gap_penalty, opt_align[i][j + 1] + gap_penalty));
		}
}	

int main()
{

	cin >> m >> n; //길이 입력
	cin >> x >> y; //x,y string 입력
	cin >> gap_penalty >> mismatch_penalty; //penalty 값 입력

	for (int i = 0; i < m; i++)
		opt_align[i][n] = gap_penalty * (m - i);
	for (int j = 0; j < n; j++)
		opt_align[m][j] = gap_penalty * (n - j);
	
	opt();
	cout << fixed;
	cout.precision(1);
	cout << opt_align[0][0];

	return 0;

}