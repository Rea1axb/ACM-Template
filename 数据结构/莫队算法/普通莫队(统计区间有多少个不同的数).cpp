/*
    BZOJ - 1878 统计[L,R]区间内有多少个不同的数
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 5e4 + 10;
const int MAXNUM = 1e6 + 10;
const int MAXQ = 2e5 + 10;
int block;
struct query {
    int l, r;
    int id;
    int ans;
}q[MAXQ];
bool cmp_block(query a, query b) { //分块排序
    if (a.l / block != b.l / block) return a.l < b.l;
    return (a.l / block) & 1 ? a.r < b.r : a.r > b.r;
}
bool cmp_id(query a, query b) {
    return a.id < b.id;
}
int color[MAXN], cnt[MAXNUM];
int sum;
void add(int val) {
    cnt[val]++;
    if (cnt[val] == 1) sum++;
}
void del(int val) {
    cnt[val]--;
    if (cnt[val] == 0) sum--;
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    block = sqrt(n);
    sort(q + 1, q + m + 1, cmp_block);
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        while (l > q[i].l) add(color[--l]);
        while (r < q[i].r) add(color[++r]);
        while (l < q[i].l) del(color[l++]);
        while (r > q[i].r) del(color[r--]);
        q[i].ans = sum;
    }
    sort(q + 1, q + m + 1, cmp_id);
    for (int i = 1; i <= m; i++) {
        printf("%d\n", q[i].ans);
    }
    return 0;
}
