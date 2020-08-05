/*
����״����ά���������D[i] = A[i] - A[i-1]
A[i] = D[1] + D[2] + D[3] + ... + D[i]

*/
namespace BIT {
ll c[MAXN];
int n;
int lowbit(int x) {
    return x & (-x);
}

void updata(int i, int k) {
    while (i <= n) {
        c[i] += k;
        i += lowbit(i);
    }
}

ll getsum(int i) {//��D[1] + D[2] + ... + D[i], ��A[i]
    ll res = 0;
    while (i > 0) {
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}

void change(int l, int r, int k) {
    BIT::updata(l, k);
    BIT::updata(r + 1, -k);
}

ll query(int x) {
    return getsum(x);
}

void init(int _n) {
    n = _n;
    fill(sum1, sum1 + n + 1, 0);
    fill(sum2, sum2 + n + 1, 0);
}
};
BIT::init(n);
BIT::change(i, i, a[i]);

//[l, r]�������k
BIT::change(l, r, k);
ans = BIT::query(i);
