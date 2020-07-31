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
ans = query(l, r);
