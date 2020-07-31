namespace MaxFlow {
    struct Edge {
        int v, rev;
        ll f;
    };

    int n, s, t;
    int cur[MAXMN], dep[MAXN], gap[MAXN];
    ll flow;
    vector<Edge> G[MAXN];

    void add_edge(int u, int v, ll f) {
        G[u].push_back({v, (int) G[v].size(), f});
        G[v].push_back({u, (int) G[u].size() - 1, 0});
    }

    ll dfs(int u, ll lim) {
        if (u == t)
            return lim;
        ll num = 0;
        for (int &i = cur[u], v; i < G[u].size(); ++i) {
            ll f = G[u][i].f;
            if (dep[v = G[u][i].v] == dep[u] - 1 && f) {
                f = dfs(v, min(lim - num, f));
                G[v][G[u][i].rev].f += f;
                G[u][i].f -= f;
                num += f;
                if (num == lim) return num;
            }
        }
        if (!--gap[dep[u]++])
            dep[s] = n + 1;
        ++gap[dep[u]];
        cur[u] = 0;
        return num;
    }

    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; ++i) G[i].clear();
    }

    void solve(int _s, int _t) {
        s = _s, t = _t, flow = 0;
        for (int i = 0; i <= n; ++i) cur[i] = dep[i] = gap[i] = 0;
        for (gap[0] = n; dep[s] <= n; flow += dfs(s, INF));
    }
}
