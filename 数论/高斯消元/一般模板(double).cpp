#include <bits/stdc++.h>
using namespace std;
#define N 105
double a[N][N];
int n;
void gauss()
{
    for (int i = 1; i <= n; i++) //枚举列（项）
    {
        int maxn = i;
        for (int j = i + 1; j <= n; j++) //选出该列最大系数
        {
            if (fabs(a[j][i]) > fabs(a[max][i]))
            {
                maxn = j;
            }
        }
        for (int j = 1; j <= n + 1; j++) //交换
        {
            swap(a[i][j], a[maxn][j]);
        }
        if (!a[i][i]) //最大值等于0则说明该列都为0，肯定无解
        {
            printf("No Solution\n");
            return;
        }
        for (int j = 1; j <= n; j++) //每一项都减去一个数（就是小学加减消元）
        {
            if (j != i)
            {
                double temp = a[j][i] / a[i][i];
                for (int k = i + 1; k <= n + 1; k++)
                {
                    a[j][k] -= a[i][k] * temp;
                    //a[j][k]-=a[j][i]*a[i][k]/a[i][i];
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            printf("%.2lf\n", a[i][n + 1] / a[i][i]);
        }
    }
    //上述操作结束后，矩阵会变成这样
    /*
    k1*a=e1
    k2*b=e2
    k3*c=e3
    k4*d=e4
    */
    //所以输出的结果要记得除以该项系数，消去常数
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n + 1; j++)
        {
            scanf("%lf", &a[i][j]);//tmd卡精度直接java,
        }
    }
    gauss();
    return 0;
}
