//有向图支配树，Lengauer-Tarjan算法
//时间复杂度：O(nlogn)
vector<int> G[MAXN], RG[MAXN]; //G原图，RG反图
void init(int _n) {
    for (int i = 1; i <= _n; i++) {
        G[i].clear();
        RG[i].clear();
    }
}
namespace DominatorTree {
    struct edge {
        int u, v;
        int next;
    }e[MAXM * 2];
    int first[MAXN], idx, n;
    int tol, dfn[MAXN], id[MAXN], fa[MAXN], f[MAXN], mn[MAXN], sd[MAXN], idom[MAXN];
    //id[x]:dfs序为x的点的id；mn[x]:x除根以外的所有祖先中，半支配点dfs序最小的那个点；
    //sd[x]:x的半必经点；idom[x]:x的最近必经点，即支配树的父节点
    void add(int u, int v) {
        e[idx].u = u;
        e[idx].v = v;
        e[idx].next = first[u];
        first[u] = idx++;
    }
    void init(int _n) {
        n = _n;
        idx = 0;
        fill(first, first + n + 1, -1);
    }
    int find(int x) {
        if (f[x] == x) return x;
        int y = find(f[x]);
        if (dfn[sd[mn[x]]] > dfn[sd[mn[f[x]]]]) mn[x] = mn[f[x]];
        return f[x] = y;
    }
    void dfs(int u) {
        id[dfn[u] = ++tol] = u;
        for (auto v : G[u]) {
            if (!dfn[v]) {
                dfs(v);
                fa[v] = u;
            }
        }
    }
    void tarjan(int root) {
        tol = 0;
        for (int i = 1; i <= n; i++) {
            dfn[i] = id[i] = fa[i] = idom[i] = 0;
            f[i] = sd[i] = mn[i] = i;
        }
        dfs(root);
        for (int i = tol; i >= 2; i--) {
            //求解半支配点
            int x = id[i];
            for (auto v : RG[x]) {
                if (!dfn[v]) continue;
                find(v);
                if (dfn[sd[x]] > dfn[sd[mn[v]]]) sd[x] = sd[mn[v]];
            }
            //维护半支配树
            add(sd[x], x);
            //求解支配点
            x = f[x] = fa[x];
            for (int j = first[x]; j != -1; j = e[j].next) {
                int v = e[j].v;
                find(v);
                idom[v] = x == sd[mn[v]] ? x : mn[v];
            }
            //清空扫过的儿子
            first[x] = -1;
        }
        for (int i = 2; i <= tol; i++) {
            int x = id[i];
            if (idom[x] != sd[x]) idom[x] = idom[idom[x]];
            add(idom[x], x);
        }
    }
}

DominatorTree::init(n);
DominatorTree::tarjan(root);

/*
给定一张有向图，求从1号点出发，每个点能支配的点的个数（包括自己）
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 2e5 + 10;
const int MAXM = 3e5 + 10;
//有向图支配树，Lengauer-Tarjan算法
//时间复杂度：O(nlogn)
vector<int> G[MAXN], RG[MAXN]; //G原图，RG反图
void init(int _n) {
    for (int i = 1; i <= _n; i++) {
        G[i].clear();
        RG[i].clear();
    }
}
namespace DominatorTree {
    struct edge {
        int u, v;
        int next;
    }e[MAXM * 2];
    int first[MAXN], idx, n;
    int tol, dfn[MAXN], id[MAXN], fa[MAXN], f[MAXN], mn[MAXN], sd[MAXN], idom[MAXN];
    //id[x]:dfs序为x的点的id；mn[x]:x除根以外的所有祖先中，半支配点dfs序最小的那个点；
    //sd[x]:x的半必经点；idom[x]:x的最近必经点，即支配树的父节点
    void add(int u, int v) {
        e[idx].u = u;
        e[idx].v = v;
        e[idx].next = first[u];
        first[u] = idx++;
    }
    void init(int _n) {
        n = _n;
        idx = 0;
        fill(first, first + n + 1, -1);
    }
    int find(int x) {
        if (f[x] == x) return x;
        int y = find(f[x]);
        if (dfn[sd[mn[x]]] > dfn[sd[mn[f[x]]]]) mn[x] = mn[f[x]];
        return f[x] = y;
    }
    void dfs(int u) {
        id[dfn[u] = ++tol] = u;
        for (auto v : G[u]) {
            if (!dfn[v]) {
                dfs(v);
                fa[v] = u;
            }
        }
    }
    void tarjan(int root) {
        tol = 0;
        for (int i = 1; i <= n; i++) {
            dfn[i] = id[i] = fa[i] = idom[i] = 0;
            f[i] = sd[i] = mn[i] = i;
        }
        dfs(root);
        for (int i = tol; i >= 2; i--) {
            //求解半支配点
            int x = id[i];
            for (auto v : RG[x]) {
                if (!dfn[v]) continue;
                find(v);
                if (dfn[sd[x]] > dfn[sd[mn[v]]]) sd[x] = sd[mn[v]];
            }
            //维护半支配树
            add(sd[x], x);
            //求解支配点
            x = f[x] = fa[x];
            for (int j = first[x]; j != -1; j = e[j].next) {
                int v = e[j].v;
                find(v);
                idom[v] = x == sd[mn[v]] ? x : mn[v];
            }
            //清空扫过的儿子
            first[x] = -1;
        }
        for (int i = 2; i <= tol; i++) {
            int x = id[i];
            if (idom[x] != sd[x]) idom[x] = idom[idom[x]];
            add(idom[x], x);
        }
    }
}
int sz[MAXN];
void dfs(int u) {
    sz[u] = 1;
    for (int i = DominatorTree::first[u]; i != -1; i = DominatorTree::e[i].next) {
        int v = DominatorTree::e[i].v;
        dfs(v);
        sz[u] += sz[v];
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    init(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        RG[v].push_back(u);
    }
    DominatorTree::init(n);
    DominatorTree::tarjan(1);
    dfs(1);
    for (int i = 1; i <= n; i++) {
        if (i != 1) printf(" ");
        printf("%d", sz[i]);
    }
    return 0;
}
