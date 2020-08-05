#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int inf=0x3f3f3f3f;
const double pi= acos(-1.0);
const double esp=1e-6;
const int MAXN=310;
int aug[MAXN][MAXN];<span style="background-color: rgb(255, 255, 255);">
//增广矩阵行数为m,分别为0到m-1,列数为n+1,分别为0到n.</span>
int x[MAXN];//解集
int free_num;
int m,n;//m个方程，n个变元
int gcd(int a,int b) {
    int r;
    while(b!=0) {
        r=b;
        b=a%b;
        a=r;
    }
    return a;
}
int lcm(int a,int b) {
    return a/gcd(a,b)*b;
}
/*void Debug(void)
{
    puts("");
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n+1;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}*/
int trans(char *str) {
    if(strcmp(str,"MON")==0) return 1;
    else if(strcmp(str,"TUE")==0) return 2;
    else if(strcmp(str,"WED")==0) return 3;
    else if(strcmp(str,"THU")==0) return 4;
    else if(strcmp(str,"FRI")==0) return 5;
    else if(strcmp(str,"SAT")==0) return 6;
    else if(strcmp(str,"SUN")==0) return 7;
}
// 高斯消元法解方程组(Gauss-Jordan elimination).(-1表示无解，
//0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
int Gauss() {
    int i,j;
    int row,col,max_r;// 当前这列绝对值最大的行;
    int LCM;
    int ta,tb;
    int tmp;
    for(row=0,col=0; row<m&&col<n; row++,col++) {
        // 枚举当前处理的行.
        // 找到该col列元素绝对值最大的那行与第row行交换.(为了在除法时减小误差)
        max_r=row;
        for(i=row+1; i<m; i++) {
            if(abs(aug[i][col])>abs(aug[max_r][col]))
                max_r=i;
        }
        if(max_r!=row) {
            // 与第row行交换
            for(j=row; j<n+1; j++)
                swap(aug[row][j],aug[max_r][j]);
        }
        if(aug[row][col]==0) {
            // 说明该col列第row行以下全是0了，则处理当前行的下一列.
            row--;
            continue;
        }
        for(i=row+1; i<m; i++) {
            // 枚举要删去的行.
            if(aug[i][col]!=0) {
                LCM=lcm(abs(aug[i][col]),abs(aug[row][col]));
                ta=LCM/abs(aug[i][col]);
                tb=LCM/abs(aug[row][col]);
                if(aug[i][col]*aug[row][col]<0) tb=-tb;//异号的情况是相加
                for(j=col; j<n+1; j++) {
                    aug[i][j]=(((aug[i][j]*ta-aug[row][j]*tb)%7+7)%7);
                }
            }
        }
    }
    //Debug();
    // 1. 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
    for(i=row; i<m; i++) {
        if(aug[i][col]!=0)  return -1;
    }
    // 2. 无穷解的情况: 在n * (n + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
    // 且出现的行数即为自由变元的个数.
    if(row<n){
        return n-row;
    }
     // 3. 唯一解的情况: 在n * (n + 1)的增广阵中形成严格的上三角阵.
    // 计算出Xn-1, Xn-2 ... X0.
    for(i=n-1; i>=0; i--) {
        tmp=aug[i][n];//等式右边的数
        for(j=i+1; j<n; j++) {
            if(aug[i][j]!=0) tmp-=aug[i][j]*x[j];//把已知的解带入，减去，只剩下，一个未知的解
            tmp=(tmp%7+7)%7;
        }
        while(tmp%aug[i][i]!=0)//外层每次循环都是为了求 a[i][i],因为它是每个方程中唯一一个未知的变量（求该方程时）
            tmp+=7;//因为天数不确定，而aug[i][i]必须得为整数才可以，周期为7
        x[i]=(tmp/aug[i][i])%7;
    }
    return 0;
}
int main(void) {
    int nn,mm,i,j,k;
    int num;
    char Start[5],End[5];
    while(~scanf("%d %d",&nn,&mm)) {
        if(nn==0&&mm==0) break;
        n=m=0;
        memset(aug,0,sizeof(aug));
        for(i=0; i<mm; i++) {
            scanf("%d",&k);
            scanf("%s %s",Start,End);
            aug[i][nn]=((trans(End)-trans(Start)+1)%7+7)%7;
            for(j=1; j<=k; j++) {
                scanf("%d",&num);
                num--;
                aug[i][num]++;
                aug[i][num]%=7;//有重复的
            }
        }
        m=mm;
        n=nn;
        free_num = Gauss();
        if(free_num==0) {
            for(i=0; i<n; i++)
                if(x[i]<3)//根据题意，每个零件的加工时间在3-9天.
                    x[i]+=7;
            for(i=0; i<n-1; i++)
                printf("%d ",x[i]);
            printf("%d\n",x[i]);
        } else if(free_num==-1)
            puts("Inconsistent data.");
        else
            puts("Multiple solutions.");
    }
    return 0;
}
