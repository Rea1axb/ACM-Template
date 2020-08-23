/*
SUMD[x][y]:以(x,y)为右下角，(1,1)为左上角的差分矩阵之和
A[1][1] + ... + A[1][y] + A[2][1] + ... + A[x][y]
=(x + 1)*(y + 1)*SUMD[x][y] - (y + 1) * SUMD[x][y] * i - (x + 1) * SUMD[x][y] * j
+ SUMD[x][y] * i * j

因此用4个树状数组分别维护：
sum1[i][j]:D[i][j]
sum2[i][j]:D[i][j]*i
sum3[i][j]:D[i][j]*j
sum4[i][j]:D[i][j]*i*j
*/
namespace BIT {
ll sum1[MAXN][MAXM];
ll sum2[MAXN][MAXM];
ll sum3[MAXN][MAXM];
ll sum4[MAXN][MAXM];
int n, m;
int lowbit(int x) {
    return x & (-x);
}

void updata(int x, int y, int k) {//在(x, y)加上k
    ll tmpx = x;
    ll tmpy = y;
    while (x <= n) {
        y = tmpy;
        while (y <= m) {
            sum1[x][y] += k;
            sum2[x][y] += k * tmpx;
            sum3[x][y] += k * tmpy;
            sum4[x][y] += k * tmpx * tmpy;
            y += lowbit(y);
        }
        x += lowbit(x);
    }
}

ll getsum(int x, int y) {//求左上角为(1, 1)，右下角为(x, y)的矩阵和
    ll res = 0;
    ll tmpx = x;
    ll tmpy = y;
    while (x > 0) {
        y = tmpy;
        while (y > 0) {
            res += (tmpx + 1) * (tmpy + 1) * sum1[x][y]
                    - (tmpy + 1) * sum2[x][y]
                    - (tmpx + 1) * sum3[x][y]
                    + sum4[x][y];
            y -= lowbit(y);
        }
        x -= lowbit(x);
    }
    return res;
}

void change(int x1, int y1, int x2, int y2, int k) {
    updata(x1, y1, k);
    updata(x1, y2 + 1, -k);
    updata(x2 + 1, y1, -k);
    updata(x2 + 1, y2 + 1, k);
}

ll query(int x1, int y1, int x2, int y2) {
    return getsum(x2, y2) - getsum(x2, y1 - 1) - getsum(x1 - 1, y2) + getsum(x1 - 1, y1 - 1);
}

void init(int _n, int _m) {
    n = _n;
    m = _m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            sum1[i][j] = 0;
            sum2[i][j] = 0;
            sum3[i][j] = 0;
            sum4[i][j] = 0;
        }
    }
}
};
BIT::init(n, m);
BIT::change(i, j, i, j, k);

//左上角为(x1, y1),右下角为(x2, y2)的矩阵加上k
BIT::change(x1, y1, x2, y2, k);

//左上角为(x1, y1)，右下角为(x2, y2)的矩阵和
ans = BIT::query(x1, y1, x2, y2);

