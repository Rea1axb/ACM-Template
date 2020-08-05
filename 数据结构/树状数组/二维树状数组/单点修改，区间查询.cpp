/*
��һά��״�����У�
c[x]��¼�����Ҷ˵�Ϊx������Ϊlowbit(x)�������

�ڶ�ά��״�����У�
������c[x][y]��¼���½�Ϊ(x, y)����Ϊlowbit(x)����Ϊlowbit(y)�ľ����
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

//(x, y)λ�ü���k
BIT::change(x, y, k);

//�����Ͻ�Ϊ(x1, y1), ���½�Ϊ(x2, y2)�ľ����
ans = BIT::query(x1, y1, x2, y2);
