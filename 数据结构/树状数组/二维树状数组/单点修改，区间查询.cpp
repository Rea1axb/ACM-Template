/*
在一维树状数组中，
c[x]记录的是右端点为x，长度为lowbit(x)的区间和

在二维树状数组中，
可以用c[x][y]记录右下角为(x, y)，高为lowbit(x)，宽为lowbit(y)的矩阵和
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

void change(int x, int y, int k) {
    updata(x, y, k);
}

ll query(int x1, int y1, int x2, int y2) {
    return getsum(x2, y2) - getsum(x2, y1 - 1) - getsum(x1 - 1, y2) + getsum(x1 - 1, y1 - 1);
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
BIT::change(i, j, a[i][j]);

//(x, y)位置加上k
BIT::change(x, y, k);

//求左上角为(x1, y1), 右下角为(x2, y2)的矩阵和
ans = BIT::query(x1, y1, x2, y2);
