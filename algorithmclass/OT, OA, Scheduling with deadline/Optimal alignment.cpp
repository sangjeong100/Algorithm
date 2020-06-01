#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <cfloat>

using namespace std;

double opt_align[102][102];
int check[102][102];
double gap_penalty;
double mismatch_penalty;
string x;
string y;
int m, n;
vector<char> xResult;
vector<char> yResult;


int prioritySelection(int i,int j, double penalty)
{
    //������ ��
    //gap���� mismatch ������ ��
    //gap�߿��� y�������� gap�� �ִ� ���� ����

    double min_ = 0;
    if (opt_align[i + 1][j] < opt_align[i][j + 1])
        min_ = opt_align[i + 1][j] + gap_penalty;
    else if (fabsf(opt_align[i + 1][j] - opt_align[i][j + 1]) <= FLT_EPSILON)
        min_ = opt_align[i + 1][j] + gap_penalty;
    else
        min_ = opt_align[i][j + 1] + gap_penalty;
    

    if (opt_align[i + 1][j + 1] + penalty < min_ || fabsf((opt_align[i + 1][j + 1] + penalty) - min_) <= FLT_EPSILON)
        min_ = opt_align[i+1][j+1] + penalty;
    
    if (fabsf(min_ - (opt_align[i + 1][j + 1] + penalty)) <= FLT_EPSILON)
        return 0; //�밢��
    else if (fabsf(min_ - (opt_align[i + 1][j] + gap_penalty)) <= FLT_EPSILON)
        return 1; //�Ʒ���
    else
        return 2; //������
}
void opt()
{
    double penalty; //mismatch

    int i, j; //x,y���� ��ġ
    for (i = m - 1; i >= 0; i--)
        for (j = n - 1; j >= 0; j--)
        {
            if (x[i] == y[j]) penalty = 0;
            else penalty = mismatch_penalty;

            opt_align[i][j] = min(min(opt_align[i + 1][j + 1] + penalty, opt_align[i + 1][j] + gap_penalty) ,opt_align[i][j + 1] + gap_penalty);
            check[i][j] = prioritySelection(i,j, penalty); //�켱������ ���� ���õǴ� ���� �����س���
        }
    return;
}




int MakeSeqeuce()
{
    int i = 0;
    int j = 0;
    int maxlen = m + n;

    int xpos = 0;
    int ypos = 0;
    double penalty = 0;

    int ch = 0;

    xResult.assign(maxlen, 0);
    yResult.assign(maxlen, 0);


    while (1)
    {
        if (i >= m || j >= n) break;
        
        if (check[i][j] == 0)  //mismatch or match
        {
            xResult[xpos] = x[i];
            yResult[ypos] = y[j];
            xpos++; ypos++;
            i++; j++;
        }
        else if(check[i][j] == 1) //y sequence�� gap �߰�
        {
            xResult[xpos] = x[i];
            yResult[ypos] = '-';
            xpos++; ypos++;
            i++;
        }
        else                        //x sequence�� gap�߰�
        {
            xResult[xpos] = '-';
            yResult[ypos] = y[j];
            xpos++; ypos++;
            j++;
        }

    }

    //�ڿ� ������ �κ� gap���� ä��� �κ�
    if (xpos < maxlen)
    {
        for (i; i < m; i++)
            xResult[xpos++] = x[i];

        while (xpos < maxlen)
            xResult[xpos++] = '-';
    }
    if (ypos < maxlen)
    {
        for (j; j < n; j++)
            yResult[ypos++] = y[j];
        while (ypos < maxlen)
            yResult[ypos++] = '-';
    }

    //x,y�Ѵ� gap�� ���� ���̹Ƿ�, ���κ� ����
    for (i = 0; i < maxlen; i++)
        if (xResult[i] == '-' && yResult[i] == '-')
        {
            return i;
        }
}

int main()
{

    cin >> m >> n; //���� �Է�
    cin >> x >> y; //x,y string �Է�
    cin >> gap_penalty >> mismatch_penalty; //penalty �� �Է�


    for (int i = 0; i < m; i++)
        opt_align[i][n] = gap_penalty * (m - i);
    for (int j = 0; j < n; j++)
        opt_align[m][j] = gap_penalty * (n - j);

    opt_align[m][n] = 0;

    opt();
    int last = MakeSeqeuce();
    
    cout << fixed;
    cout.precision(1);

    cout << opt_align[0][0] << " ";
    for (int i = 0; i < last; i++)
        cout << xResult[i];
    cout << " ";
    for (int i = 0; i < last; i++)
        cout << yResult[i];

    return 0;

}