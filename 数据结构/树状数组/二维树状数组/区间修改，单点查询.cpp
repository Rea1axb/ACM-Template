/*
A[i][j] = A[i-1][j] + A[i][j-1] - A[i-1][j-1] + D[i][j]
����״����ά���������D[i][j]
*/
namespace BIT {
ll c[MAXN][MAXM];
int n, m;
int lowbit(int x) {
    return x & (-x);
}

void updata(int x, int y, int k) {//��(x, y)����k
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

ll getsum(int x, int y) {//�����Ͻ�Ϊ(1, 1)�����½�Ϊ(x, y)�ľ����
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

//���Ͻ�Ϊ(x1, y1),���½�Ϊ(x2, y2)�ľ������k
BIT::change(x1, y1, x2, y2, k);

//(x, y)λ�õ�ֵ
ans = BIT::query(x, y);
