/*
    小Z的袜子
    统计[L,R]区间内选两只袜子，颜色相同的概率。区间查询，统计两个相同概率。
    N,M ≤ 50000，1 ≤ L < R ≤ N，Ci ≤ N。
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 5e4 + 10;
const int MAXQ = 5e4 + 10;
int block;
struct query {
    int l, r;
    int id;
    ll ans1, ans2; //分子分母
}q[MAXQ];
bool cmp_block(query a, query b) { //分块排序
    if (a.l / block != b.l / block) return a.l < b.l;
    return (a.l / block) & 1 ? a.r < b.r : a.r > b.r;
}
bool cmp_id(query a, query b) {
    return a.id < b.id;
}
ll sum;
int color[MAXN];
int cnt[MAXN];
void add(int val) {
    sum += cnt[val];
    cnt[val]++;
}
void del(int val) {
    cnt[val]--;
    sum -= cnt[val];
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    block = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + m + 1, cmp_block);
    sum = 0;
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        if (q[i].l == q[i].r) {
            q[i].ans1 = 0, q[i].ans2 = 1;
            continue;
        }
        while (l > q[i].l) add(color[--l]);
        while (r < q[i].r) add(color[++r]);
        while (l < q[i].l) del(color[l++]);
        while (r > q[i].r) del(color[r--]);
        q[i].ans1 = sum;
        q[i].ans2 = 1ll * (r - l + 1) * (r - l) / 2;
    }
    sort(q + 1, q + m + 1, cmp_id);
    for (int i = 1; i <= m; i++) {
        ll g = __gcd(q[i].ans1, q[i].ans2);
        q[i].ans1 /= g, q[i].ans2 /= g;
        printf("%lld/%lld\n", q[i].ans1, q[i].ans2);
    }
    return 0;
}
