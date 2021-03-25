//一个点x的支配点是所有能够直接到达x的点在支配树上的LCA。

//拓扑序依次建立支配树，通过反图找到所有能够直接到达当前点的点，倍增求解 LCA，支配树上该点
//的父亲就是所求的LCA


/*
无向图中，求解除原点外删掉一个点后有多少个点的最短路会改变，输出最大值。

求解原点到其他点的最短路后删去无用的边，只保留最短路的路径，
那么图就变成了DAG，建立支配树求解答案
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 2e5 + 10;
const int MAXM = 3e5 + 10;
const int DEG = 20;
const ll INF = 1e18;
struct edge {
    int u,v;
    int next;
    ll w;
}e[MAXM * 2];
int first[MAXN];
int idx;
void add(int a, int b, ll c) {
    e[idx].u = a;
    e[idx].v = b;
    e[idx].w = c;
    e[idx].next = first[a];
    first[a] = idx++;
}
void init(int _n) {
    fill(first, first + _n + 1, -1);
    idx = 0;
}
ll dist[MAXN];
int vis[MAXN];
struct node {
    int id;
    ll val;
    bool operator < (const node &t) const {
        return val > t.val;
    }
};
void dijkstra(int s, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        vis[i] = 0;
    }
    priority_queue<node> q;
    q.push({s, 0});
    dist[s] = 0;
    while (!q.empty()) {
        node cur = q.top();
        q.pop();
        if (vis[cur.id]) continue;
        vis[cur.id] = 1;
        for (int i = first[cur.id]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (dist[v] > dist[cur.id] + e[i].w) {
                dist[v] = dist[cur.id] + e[i].w;
                q.push({v, dist[v]});
            }
        }
    }
}
vector<int> G[MAXN], RG[MAXN];
namespace LCA {
    int fa[MAXN][DEG];
    int dep[MAXN];
    vector<int> G[MAXN];
    int sz[MAXN];
    void init(int root, int _n) {
        dep[root] = 0;
        fa[root][0] = root;
        for (int i = 1; i < DEG; i++) {
            fa[root][i] = fa[fa[root][i - 1]][i - 1];
        }
        for (int i = 1; i <= _n; i++)
            G[i].clear();
    }
    void add(int u, int v) { //边加点边更新倍增信息
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        for (int i = 1; i < DEG; i++) {
            fa[v][i] = fa[fa[v][i - 1]][i - 1];
        }
        G[u].push_back(v);
    }

    int query(int u, int v) {
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        int hu = dep[u], hv = dep[v];
        int tu = u, tv = v;
        for (int k = hv - hu, i = 0; k; k >>= 1, i++) {
            if (k & 1) {
                tv = fa[tv][i];
            }
        }
        if (tu == tv) {
            return tu;
        }
        for (int i = DEG - 1; i >= 0; i--) {
            if (fa[tu][i] == fa[tv][i]) {
                continue;
            }
            tu = fa[tu][i];
            tv = fa[tv][i];
        }
        return fa[tu][0];
    }
    void dfs(int u) {
        sz[u] = 1;
        for (auto v : G[u]) {
            dfs(v);
            sz[u] += sz[v];
        }
    }
}
int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    init(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    //求最短路
    dijkstra(s, n);
    vector<int> indeg(n + 1);
    //建立DAG原图和反图
    for (int i = 1; i <= n; i++) {
        for (int j = first[i]; j != -1; j = e[j].next) {
            int v = e[j].v;
            if (dist[v] == dist[i] + e[j].w) {
                G[i].push_back(v);
                indeg[v]++;
                RG[v].push_back(i);
            }
        }
    }
    //DAG建立支配树
    queue<int> q;
    q.push(s);
    LCA::init(s, n);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (!RG[cur].empty()) {
            int lca = RG[cur][0];
            for (auto v : RG[cur]) {
                lca = LCA::query(lca, v);
            }
            LCA::add(lca, cur);
        }
        for (auto v : G[cur]) {
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }
    //求解答案
    LCA::dfs(s);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i == s) continue;
        ans = max(ans, LCA::sz[i]);
    }
    printf("%d\n", ans);
    return 0;
}
