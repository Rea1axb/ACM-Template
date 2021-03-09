/*
LOJ-2874：区间内某种颜色的重要度为颜色号与出现次数的乘积：color[i]*cnt[color[i]]
求区间内最大的重要度

普通莫队很难解决最大值问题，因为无法维护删除一个数后的最大值，
但是能维护增加一个数后的最大值。所以用回滚莫队使得只维护增加一个数后的最大值
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
const int MAXQ = 1e5 + 10;
vector<ll> lisan;
int getid(ll x) {
    return lower_bound(lisan.begin(), lisan.end(), x) - lisan.begin() + 1;
}
int block;
int blocknum[MAXN]; //记录某个位置属于哪个块
struct query {
    int l, r;
    int id;
    ll ans;
}q[MAXQ];
bool cmp_block(query a, query b) {
    if (blocknum[a.l] != blocknum[b.l]) return a.l < b.l;
    return a.r < b.r;
}
bool cmp_id(query a, query b) {
    return a.id < b.id;
}
ll color[MAXN];
int cnt[MAXN], _cnt[MAXN]; //_cnt用于左右端点属于同一个块的数量记录
ll sum;
int L[MAXN], R[MAXN]; //每个块的左右端点
void build(int n) { //得到每个块的左右端点和blocknum
    int tot = n / block;
    for (int i = 1; i <= tot; i++) {
        L[i] = (i - 1) * block + 1;
        R[i] = i * block;
    }
    if (R[tot] < n) {
        ++tot;
        L[tot] = R[tot - 1] + 1;
        R[tot] = n;
    }
    for (int i = 1; i <= tot; i++) {
        for (int j = L[i]; j <= R[i]; j++)
            blocknum[j] = i;
    }
}
void add(int val) {
    cnt[val]++;
    sum = max(sum, lisan[val - 1] * cnt[val]);
}
void del(int val) { //删除操作只需记录数量，不用维护答案
    cnt[val]--;
}
int main() {
    int n, Q;
    scanf("%d%d", &n, &Q);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &color[i]);
        lisan.push_back(color[i]);
    }
    sort(lisan.begin(), lisan.end());
    lisan.erase(unique(lisan.begin(), lisan.end()), lisan.end());
    for (int i = 1; i <= n; i++) {
        color[i] = getid(color[i]);
    }
    for (int i = 1; i <= Q; i++) {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    block = sqrt(n);
    build(n);
    sort(q + 1, q + Q + 1, cmp_block);
    for (int i = 1, l = 1, r = 0, last_block = 0; i <= Q; i++) {
        if (blocknum[q[i].l] == blocknum[q[i].r]) {
            // 询问的左右端点同属于一个块则暴力扫描回答
            for (int j = q[i].l; j <= q[i].r; j++)
                ++_cnt[color[j]];
            for (int j = q[i].l; j <= q[i].r; j++)
                q[i].ans = max(q[i].ans, _cnt[color[j]] * lisan[color[j] - 1]);
            for (int j = q[i].l; j <= q[i].r; j++)
                --_cnt[color[j]];
            continue;
        }
        if (blocknum[q[i].l] != last_block) {
            // 访问到了新的块则重新初始化莫队区间，使得之后只需维护增加一个数的操作
            while (r > R[blocknum[q[i].l]]) del(color[r--]);
            while (l < R[blocknum[q[i].l]] + 1) del(color[l++]);
            sum = 0;
            last_block = blocknum[q[i].l];
        }
        //扩展右端点
        while (r < q[i].r) add(color[++r]);

        //记录回滚点
        int tmpl = l;
        ll tmpsum = sum;

        //扩展左端点
        while (l > q[i].l) add(color[--l]);

        //答案
        q[i].ans = sum;

        //回滚
        while (l < tmpl) del(color[l++]);
        sum = tmpsum;
    }
    sort(q + 1, q + Q + 1, cmp_id);
    for (int i = 1; i <= Q; i++) {
        printf("%lld\n", q[i].ans);
    }
    return 0;
}
