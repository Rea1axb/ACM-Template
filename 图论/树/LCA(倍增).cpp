/*
预处理时间 O(nlogn)
单次查询时间 O(logn)
*/
namespace LCA {
    int fa[MAXN][DEG];
    int dep[MAXN];

    void bfs(int root) {
        queue<int> q;
        dep[root] = 0;
        fa[root][0] = root;
        q.push(root);
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            for (int i = 1; i < DEG; i++) {
                fa[tmp][i] = fa[fa[tmp][i - 1]][i - 1];
            }
            for (int i = first[tmp]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (v == fa[tmp][0]) continue;
                dep[v] = dep[tmp] + 1;
                fa[v][0] = tmp;
                q.push(v);
            }
        }
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
};
LCA::bfs(root);
LCA::query(u, v);
