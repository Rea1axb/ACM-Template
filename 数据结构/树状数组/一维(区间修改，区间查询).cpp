/*
A[i] = D[1] + D[2] + D[3] + ... + D[i]
A[1] + A[2] + ... + A[n]
= n * (D[1] + D[2] + ... + D[n]) - (0 * D[1] + 1 * D[2] + ... + D[n])
因此维护两个数状数组
sum1[i] = D[i]
sum2[i] = D[i] * (i - 1)

*/
namespace BIT {
ll sum1[MAXN];
ll sum2[MAXN];
int n;
int lowbit(int x) {
    return x & (-x);
}

void updata(int i, int k) {
    ll x = i;//先保存i的值
    while (i <= n) {
        sum1[i] += k;
        sum2[i] += k * (x - 1);
        i += lowbit(i);
    }
}

ll getsum(int i) {
    ll res = 0;
    ll x = i;
    while (i > 0) {
        res += x * sum1[i] - sum2[i];
        i -= lowbit(i);
    }
    return res;
}

void change(int l, int r, int k) {
    updata(l, k);
    updata(r + 1, -k);
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
BIT::change(i, i, a[i]);

//[l, r]区间加上k
BIT::change(l, r, k);

//[l, r]区间和
ans = BIT::query(l, r);
