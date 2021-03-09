/*
    HDU - 6534
    区间内满足i<j，|val[i]−val[j]| ≤ k的数量
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 3e4 + 10;
const int MAXQ = 3e4 + 10;
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

    ll getsum(int i) {
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
}
vector<ll> lisan;
int getid(ll x) {
    return lower_bound(lisan.begin(), lisan.end(), x) - lisan.begin() + 1;
}
struct query {
    int l, r;
    int id;
    int ans;
}q[MAXQ];
int block;
bool cmp_block(query a, query b) { //分块排序
    if (a.l / block != b.l / block) return a.l < b.l;
    return (a.l / block) & 1 ? a.r < b.r : a.r > b.r;
}
bool cmp_id(query a, query b) {
    return a.id < b.id;
}
ll val[MAXN];
int le[MAXN], ri[MAXN];
ll sum;
int k;
int n, m;
void add(int pos) {
    sum += BIT::query(le[pos], ri[pos]);
    BIT::change(val[pos], 1);
}
void del(int pos) {
    BIT::change(val[pos], -1);
    sum -= BIT::query(le[pos], ri[pos]);
}
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &val[i]);
        lisan.push_back(val[i]);
    }
    sort(lisan.begin(), lisan.end());
    lisan.erase(unique(lisan.begin(), lisan.end()), lisan.end());
    for (int i = 1; i <= n; i++) { //预处理每个数离散化后的数和左右计算区间
        le[i] = getid(val[i] - k);
        ri[i] = getid(val[i] + k);
        if (lisan[ri[i] - 1] > val[i] + k) ri[i]--;
        val[i] = getid(val[i]);
    }
    block = sqrt(n);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    BIT::init(n);
    sort(q + 1, q + m + 1, cmp_block);
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        if (q[i].l == q[i].r) {
            q[i].ans = 0;
            continue;
        }
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        q[i].ans = sum;
    }
    sort(q + 1, q + m + 1, cmp_id);
    for (int i = 1; i <= m; i++) {
        printf("%d\n", q[i].ans);
    }
    return 0;
}
