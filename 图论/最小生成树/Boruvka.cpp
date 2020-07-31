/*
1.统计每个连通块和非块内点的最小边长以及所连的点
2.将每个连通块和连边边长最短的连通块相连
3.重复步骤1-2知道连通块数量变为1
并查集维护，最多进行logn轮，复杂度O((n+m)logn)
*/
namespace MST{
    int idx;
    int n, m;
    ll ans;
    int f[MAXN];
    int best[MAXN];
    int vis[MAXM];
    struct edge {
        int u,v;
        ll w;
    }e[MAXM];
    void add(int a, int b, ll w) {
        ++idx;
        e[idx].u = a;
        e[idx].v = b;
        e[idx].w = w;
    }
    int find(int x) {
        if (f[x] == x) return x;
        return f[x] = find(f[x]);
    }
    bool better(int x, int y) {
        if (y == 0) return 1;
        if (e[x].w != e[y].w) return e[x].w < e[y].w;
        return x < y;
    }
    void init(int _n, int _m) {
        n = _n;
        m = _m;
        idx = 0;
        ans = 0;
        for (int i = 1; i <= n; i++) {
            f[i] = i;
            vis[i] = 0;
        }
    }
    void Boruvka() {
        bool upd = 1;
        int cnt = 0;
        while (upd) {
            upd = 0;
            fill(best, best + n + 1, 0);
            for (int i = 1; i <= m; i++) {
                if (vis[i]) continue;
                int fu = find(e[i].u);
                int fv = find(e[i].v);
                if (fu == fv) continue;
                if (better(i, best[fu])) best[fu] = i;
                if (better(i, best[fv])) best[fv] = i;
            }
            for (int i = 1; i <= n; i++) {
                if (best[i] && !vis[best[i]]) {
                    upd = 1;
                    cnt++;
                    ans += e[best[i]].w;
                    vis[best[i]] = 1;
                    int fu = find(e[best[i]].u);
                    int fv = find(e[best[i]].v);
                    f[fu] = fv;
                }
            }
        }
        if (cnt != n - 1) ans = -1;//无法构成生成树
    }
};
