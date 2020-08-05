namespace MCMF {
    struct edge {
        int u, v;
        int next;
        ll f;
        ll cost;
    } e[MAXM * 2];
    struct node {
        int id;
        ll val;
        node(int a, ll b) : id(a), val(b) {}
        bool operator<(const node &t) const { return val > t.val; }
    };
    int first[MAXN];
    int idx;
    int n, s, t;
    ll flow, ans, sum;
    ll dist[MAXN];
    bool aug[MAXN];

    void add_edge(int u, int v, ll f, ll cost) {
        e[idx].u = u;
        e[idx].v = v;
        e[idx].f = f;
        e[idx].cost = cost;
        e[idx].next = first[u];
        first[u] = idx++;
    }

    void add(int u, int v, ll f, ll cost) {
        add_edge(u, v, f, cost);
        add_edge(v, u, 0, -cost);
    }

    void init(int _n) {
        n = _n;
        fill(first, first + n + 1, -1);
        idx = 0;
    }

    ll dfs(int u, ll lim) {
        if (!lim)
            return 0;
        if (u == t)
            return ans += lim * sum, lim;
        ll f = 0;
        aug[u] = 1;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!e[i].cost && e[i].f && !aug[v]) {
                ll t = dfs(v, min(lim - f, e[i].f));
                e[i].f -= t;
                e[i ^ 1].f += t;
                f += t;
                if (f == lim)
                    break;
            }
        }
        if (f == lim)
            aug[u] = 0;
        return f;
    }

    bool augment() {
        priority_queue<node> q;
        for (int i = 1; i <= n; i++) {
            dist[i] = INF;
        }
        dist[t] = 0;
        q.push(node(t, 0));
        while (!q.empty()) {
            node cur = q.top();
            q.pop();
            if (dist[cur.id] != cur.val)
                continue;
            for (int i = first[cur.id]; i != -1; i = e[i].next) {
                int v = e[i].v;
                ll dis = dist[cur.id] - e[i].cost;
                if (e[i ^ 1].f && dis < dist[v]) {
                    dist[v] = dis;
                    q.push(node(v, dis));
                }
            }
        }
        sum += dist[s];
        for (int i = 1; i <= n; i++) {
            for (int j = first[i]; j != -1; j = e[j].next) {
                int v = e[j].v;
                e[j].cost += dist[v] - dist[i];
            }
        }
        return dist[s] != INF;
    }

    void solve(int _s, int _t) {
        s = _s;
        t = _t;
        ll res;
        flow = ans = sum = 0;
        do
            do
                fill(aug, aug + n + 1, 0);
            while (flow += (res = dfs(s, INF)), res > 0);
        while (augment());
    }
}
