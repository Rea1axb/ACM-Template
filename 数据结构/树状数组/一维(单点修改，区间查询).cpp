namespace BIT {
    ll c[MAXN];
    int n;
    int lowbit(int x) {
        return x & (-x);
    }

    void updata(int i, int k) {//在i位置加上k
        while (i <= n) {
            c[i] += k;
            i += lowbit(i);
        }
    }

    ll getsum(int i) {//求A[1] + A[2] + ... + A[i]
        ll res = 0;
        while (i > 0) {
            res += c[i];
            i -= lowbit(i);
        }
        return res;
    }

    void change(int x, int k) {
        updata(x, k);
    }

    ll query(int l, int r) {
        return getsum(r) - getsum(l - 1);
    }

    void init(int _n) {
        n = _n;
        fill(c, c + n + 1, 0);
    }
};
BIT::init(n);
BIT::change(i, a[i]);
//i位置加上k
BIT::change(i, k);
ans = query(l, r);//多组数据时要考虑其他组测试数据的影响

//求后缀和只需把updata和getsum取反，二维同理

//求后缀最大值

void updata(int i, ll k) {
    while (i > 0) {
        c[i] = max(c[i], k);
        i -= lowbit(i);
    }
}
ll getsum(int i) {
    ll res = -INF;
    while (i <= n) {
        res = max(res, c[i]);
        i += lowbit(i);
    }
    return res;
}
void init(int _n) {
    n = _n;
    for (int i = 1; i <= n; i++) {
        c[i] = -INF;
    }
}
