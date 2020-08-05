/*
离线
预处理时间 O(n)
处理查询时间 O(n+q)
常数比倍增大
*/

namespace LCA{
    int f[MAXN];
    int vis[MAXN];
    int n; //节点数量
    int qcnt; //询问次数
    struct node{
        int id;
        int v;
    };
    vector<node> q[MAXQ];
    int ans[MAXQ];

    void init(int _n, int _q) {
        n = _n;
        qcnt = _q;
        for (int i = 1; i <= n; i++) {
            f[i] = i;
            vis[i] = 0;
        }
        for (int i = 1; i <= qcnt; i++) {
            q[i].clear();
        }
    }

    void qadd(int u, int v, int id) {
        q[u].push({id, v});
        q[v].push({id, u});
    }

    int find(int x) {
        if (f[x] == x) return x;
        return f[x] = find(f[x]);
    }

    void dfs(int u, int fa) {
        for (int i = first[u]; i += -1; i = e[i].next) {
            int v = e[i].v;
            if (v == fa) continue;
            dfs(v, u);
            f[v] = u; //将u的子节点合并到u
        }
        for (auto que : q[u]) { //处理与u有关的询问
            if (vis[que.v]) {
                ans[que.id] = find(que.v);
            }
        }
        vis[u] = 1;
    }


};
LCA::init(n, q);
LCA::qadd(u, v, id);
LCA::dfs(root, -1);
lca = LCA::ans[id];
