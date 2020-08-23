/*
A[i][j] = A[i-1][j] + A[i][j-1] - A[i-1][j-1] + D[i][j]
用树状数组维护差分数组D[i][j]
*/
namespace BIT {
ll c[MAXN][MAXM];
int n, m;
int lowbit(int x) {
    return x & (-x);
}

void updata(int x, int y, int k) {//在(x, y)加上k
    int tmp = y;
    while (x <= n) {
        y = tmp;
        while (y <= m) {
            c[x][y] += k;
            y += lowbit(y);
        }
        x += lowbit(x);
    }
}

ll getsum(int x, int y) {//求左上角为(1, 1)，右下角为(x, y)的矩阵和
    ll res = 0;
    int tmp = y;
    while (x > 0) {
        y = tmp;
        while (y > 0) {
            res += c[x][y];
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

ll query(int x, int y) {
    return getsum(x, y);
}

void init(int _n, int _m) {
    n = _n;
    m = _m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[i][j] = 0;
        }
    }
}
};
BIT::init(n, m);
BIT::change(i, j, i, j, a[i][j]);

//左上角为(x1, y1),右下角为(x2, y2)的矩阵加上k
BIT::change(x1, y1, x2, y2, k);

//(x, y)位置的值
ans = BIT::query(x, y);
