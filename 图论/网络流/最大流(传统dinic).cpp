namespace MaxFlow {
    struct edge {
        int u, v;
        int next;
        ll f;
    }e[MAXM * 2];
    int first[MAXN], idx;
    int hcur[MAXN];

    int n, s, t;
    int dep[MAXN];
    ll flow;

    void add_edge(int u, int v, ll f) {
        e[idx].u = u;
        e[idx].v = v;
        e[idx].f = f;
        e[idx].next = first[u];
        first[u] = idx++;
    }

    void add(int u, int v, ll f) {
        add_edge(u, v, f);
        add_edge(v, u, 0);
    }

    int bfs() {
        for (int i = 1; i <= n; i++) {
            dep[i] = -1;
            hcur[i] = first[i];
        }

        dep[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = first[cur]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (dep[v] != -1 || e[i].f == 0)
                    continue;
                dep[v] = dep[cur] + 1;
                q.push(v);
            }
        }
        return dep[t] != -1;
    }

    ll dfs(int u, ll lim) {
        if (u == t || !lim)
            return lim;
        ll num = 0;
        for (int i = hcur[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            hcur[u] = i;
            ll f = e[i].f;
            if (dep[v] != dep[u] + 1 || f == 0)
                continue;
            f = dfs(v, min(lim - num, f));
            e[i ^ 1].f += f;
            e[i].f -= f;
            num += f;
            if (num == lim) break;
        }
        return num;
    }

    void init(int _n) {
        n = _n;
        fill(first, first + n + 1, -1);
        idx = 0;
    }

    void solve(int _s, int _t) {
        s = _s, t = _t, flow = 0;
        while (bfs()) {
            flow += dfs(s, INF);
        }
    }
}

//初始化
MaxFlow::init(n);

//建图
MaxFlow::add(u, v, f);

//计算答案
MaxFlow::solve(s, t);

flow = MCMF::flow;

//反向边有流量的正向边为答案中有流量的边
//判断一条边是否是正向边可以用边的编号的奇偶性判断
