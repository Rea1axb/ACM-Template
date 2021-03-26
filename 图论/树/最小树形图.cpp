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

/*
Tarjan O(m+nlogn)
*/
#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100
#define MMAX 10000

typedef long long i64;

struct UnionFind {
    UnionFind() {
        memset(fa, 0, sizeof(fa));
    }
    int fa[2 * NMAX + 10];
    void clear(int n) {
        memset(fa + 1, 0, sizeof(int) * n);
    }
    int find(int x) {
        return fa[x] ? fa[x] = find(fa[x]) : x;
    }
    int operator[](int x) {
        return find(x);
    }
};

#define INF 0x3f3f3f3f
struct Edge {
    int u, v, w, w0;
};
struct Heap {
    Heap(Edge *_e) : e(_e), rk(1), sum(0), lch(NULL), rch(NULL) {}
    Edge *e;
    int rk, sum;
    Heap *lch, *rch;
    void push() {
        if (lch)
            lch->sum += sum;

        if (rch)
            rch->sum += sum;

        e->w += sum;
        sum = 0;
    }
};
inline Heap *meld(Heap *x, Heap *y) {
    if (!x)
        return y;

    if (!y)
        return x;

    if (x->e->w + x->sum > y->e->w + y->sum)
        swap(x, y);

    x->push();
    x->rch = meld(x->rch, y);

    if (!x->lch || x->lch->rk < x->rch->rk)
        swap(x->lch, x->rch);

    x->rk = x->rch ? x->rch->rk + 1 : 1;
    return x;
}
inline Edge *extract(Heap *&x) {
    Edge *r = x->e;
    x->push();
    x = meld(x->lch, x->rch);
    return r;
}
static vector<Edge> in[NMAX + 10];
static int n, m, fa[2 * NMAX + 10], nxt[2 * NMAX + 10];
static Edge *ed[2 * NMAX + 10];
static Heap *Q[2 * NMAX + 10];
static UnionFind id; // id[] & id.fa
void contract() {
    static bool mark[2 * NMAX + 10];

    //memset(mark + 1, 0, 2 * n);
    //id.clear(2 * n);
    for (int i = 1; i <= n; i++) {
        queue<Heap *> q;

        for (int j = 0; j < in[i].size(); j++)
            q.push(new Heap(&in[i][j]));

        while (q.size() > 1) {
            Heap *u = q.front();
            q.pop();
            Heap *v = q.front();
            q.pop();
            q.push(meld(u, v));
        }

        Q[i] = q.front();
    }

    mark[1] = true;

    for (int u = 1, u0 = 1, p; Q[u]; mark[u0 = u] = true) {
        do
            u = id[(ed[u] = extract(Q[u]))->u];

        while (u == u0 && Q[u]);

        if (u == u0)
            break;

        if (!mark[u])
            continue;

        for (u0 = u, n++; u != n; u = p) {
            id.fa[u] = fa[u] = n;

            if (Q[u])
                Q[u]->sum -= ed[u]->w;

            Q[n] = meld(Q[n], Q[u]);
            p = id[ed[u]->u];
            nxt[p == n ? u0 : p] = u;
        }
    }
}
i64 expand(int, int);
i64 expand(int x) {
    i64 r = 0;

    for (int u = nxt[x]; u != x; u = nxt[u])
        if (ed[u]->w0 >= INF)
            return INF;
        else
            r += expand(ed[u]->v, u) + ed[u]->w0;

    return r;
}
i64 expand(int x, int t) {
    i64 r = 0;

    for (; x != t; x = fa[x])
        if ((r += expand(x)) >= INF)
            return INF;

    return r;
}

inline void link(int u, int v, int w) {
    in[v].push_back({u, v, w, w});
}

int main() {
    int rt;
    scanf("%d%d%d", &n, &m, &rt);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        link(u, v, w);
    }

    for (int i = 1; i <= n; i++)  // ensure strong connectivity
        link(i > 1 ? i - 1 : n, i, INF);

    contract();
    i64 ans = expand(rt, n);

    if (ans >= INF)
        puts("-1");
    else
        printf("%lld\n", ans);

    return 0;
}
