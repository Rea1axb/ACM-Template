/*
有向图有源点的最小生成树，朱刘算法，时间复杂度O(n*m)

不定根最小树形图：建立超级源点，向每个点连有向边，w为其余边的总和加1：sum+1
以超级源点利用朱刘算法计算答案，答案为ans-(sum+1）
ans == -1 || ans-(sum+1) >= sum+1 时无解
*/
namespace DMST {
    struct edge {
        int u, v;
        ll w;
        int id;
    }e[MAXM * 2];
    int cnt, fa[MAXN], id[MAXN], top[MAXN];
    int del_e[MAXM * 4], add_e[MAXM * 4], used[MAXM * 4];
    vector<int> res; //存可行方案
    int pre_e[MAXN];
    ll mn[MAXN];
    int rt, n, m, idx;
    int ROOT; //用于不定根最小树形图求实际源点，记录的是边的编号
    ll ans;
    void init(int _n, int _m, int _rt) {
        n = _n, m = _m, rt = _rt;
        ans = 0;
        idx = 0;
        ROOT = -1;
    }
    void add(int u, int v, ll w) {
        e[++idx] = {u, v, w, idx};
    }
    void solve() {
        while (1) {
            for (int i = 1; i <= n; i++) {
                id[i] = top[i] = -1;
                mn[i] = INF;
            }
            for (int i = 1; i <= m; i++) {
                if (e[i].u != e[i].v && e[i].w < mn[e[i].v]) {
                    fa[e[i].v] = e[i].u;
                    mn[e[i].v] = e[i].w;
                    pre_e[e[i].v] = e[i].id;
                    if (e[i].u == rt) {
                        ROOT = i;
                    }
                }
            }
            mn[rt] = 0;
            for (int i = 1; i <= n; i++) {
                if (mn[i] == INF) {
                    ans = -1;
                    return;
                }
                if (i != rt) used[pre_e[i]]++;
                ans += mn[i];
                int now;
                for (now = i; now != rt && top[now] != i && id[now] == -1; now = fa[now])
                    top[now] = i;
                if (now != rt && id[now] == -1) {
                    id[now] = ++cnt;
                    for (int v = fa[now]; v != now; v = fa[v])
                        id[v] = cnt;
                }
            }
            if (!cnt) break;
            for (int i = 1; i <= n; i++) {
                if (id[i] == -1)
                    id[i] = ++cnt;
            }
            for (int i = 1; i <= m; i++) {
                ll tmp = mn[e[i].v];
                int u = e[i].u;
                int v = e[i].v;
                e[i].u = id[u];
                e[i].v = id[v];
                if (e[i].u != e[i].v) {
                    e[i].w -= tmp;
                    del_e[++idx] = pre_e[v];
                    add_e[idx] = e[i].id;
                    e[i].id = idx;
                }
            }
            n = cnt;
            rt = id[rt];
            cnt = 0;
        }
        for (int i = idx; i > m; i--) {
            if (used[i]) {
                used[del_e[i]]--;
                used[add_e[i]]++;
                used[i] = 0;
            }
        }
        for (int i = 1; i <= m; i++) {
            if (used[i]) {
                res.push_back(i);
                used[i] = 0;
            }
        }
    }
}
DMST::init(n, m, root);
for (int i = 1; i <= m; i++) {
    cin >> u >> v >> w;
    DMST::add(u, v, w);
}
DMST::solve();
ans = DMST::ans;

/*
限制n号点父亲编号
给出一个有向图，求点1为根的最大树形图
使得第n个点的直接父亲编号最小

最大树形图只要边权取反
通过权值编码，对每条边的w乘一个系数，本题点编号是1~100，所以乘1000
对连向第n个点的所有边进行加权
最后答案是ans/1000和n+1-ans%1000
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e3 + 10;
const int MAXM = 1e4 + 10;
const ll INF = 1e18;
namespace DMST {
    struct edge {
        int u, v;
        ll w;
    }e[MAXM];
    int cnt, fa[MAXN], id[MAXN], top[MAXN];
    ll mn[MAXN];
    int rt, n, m, idx;
    ll ans;
    void init(int _n, int _m, int _rt) {
        n = _n, m = _m, rt = _rt;
        ans = 0;
        idx = 0;
    }
    void add(int u, int v, ll w) {
        e[++idx] = {u, v, w};
    }
    void solve() {
        while (1) {
            for (int i = 1; i <= n; i++) {
                id[i] = top[i] = -1;
                mn[i] = INF;
            }
            for (int i = 1; i <= m; i++) {
                if (e[i].u != e[i].v && e[i].w < mn[e[i].v]) {
                    fa[e[i].v] = e[i].u;
                    mn[e[i].v] = e[i].w;
                }
            }
            mn[rt] = 0;
            for (int i = 1; i <= n; i++) {
                if (mn[i] == INF) {
                    ans = -1;
                    return;
                }
                ans += mn[i];
                int now;
                for (now = i; now != rt && top[now] != i && id[now] == -1; now = fa[now])
                    top[now] = i;
                if (now != rt && id[now] == -1) {
                    id[now] = ++cnt;
                    for (int v = fa[now]; v != now; v = fa[v])
                        id[v] = cnt;
                }
            }
            if (!cnt) return;
            for (int i = 1; i <= n; i++) {
                if (id[i] == -1)
                    id[i] = ++cnt;
            }
            for (int i = 1; i <= m; i++) {
                ll tmp = mn[e[i].v];
                e[i].u = id[e[i].u];
                e[i].v = id[e[i].v];
                if (e[i].u != e[i].v)
                    e[i].w -= tmp;
            }
            n = cnt;
            rt = id[rt];
            cnt = 0;
        }
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        DMST::init(n, m, 1);
        for (int i = 1; i <= m; i++) {
            int u, v;
            ll w;
            scanf("%d%d%lld", &u, &v, &w);
            w *= 1000;
            if (v == n) {
                w += n + 1 - u;
            }
            DMST::add(u, v, -w);
        }
        DMST::solve();
        printf("%lld %d\n", -DMST::ans / 1000, n + 1 - (-DMST::ans % 1000));
    }
    return 0;
}
