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

    int used[MAXN];
    int judge(int u, int fa, int rt) {
        used[u] = 1;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (v == fa || !e[i].f) continue;
            if (v == rt) return 0;
            if (!used[v]) {
                int ok = judge(v, u, rt);
                if (!ok) return 0;
            }
        }
        return 1;
    }
    bool maxflow_unique() {
        for (int i = 1; i <= n; i++) {
            fill(used, used + n + 1, 0);
            int ok = judge(i, -1, i);
            if (!ok) return 0;
        }
        return 1;
    }

    bool mincost_unique() {
        queue<int> q1, q2;
        vector<int> vis(n + 1);
        q1.push(s);
        vis[s] = 1;
        while (!q1.empty()) {
            int cur = q1.front();
            q1.pop();
            for (int i = first[cur]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (!vis[v] && e[i].f) {
                    vis[v] = 1;
                    q1.push(v);
                }
            }
        }
        q2.push(t);
        vis[t] = 1;
        while (!q2.empty()) {
            int cur = q2.front();
            q2.pop();
            for (int i = first[cur]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (!vis[v] && e[i ^ 1].f) {
                    vis[v] = 1;
                    q2.push(v);
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) return 0;
        }
        return 1;
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

//最大流唯一性（如果残余网络中是否存在长度大于等于3的环，则最大流不唯一）
maxflow_unique = MaxFlow::maxflow_unique();

//最小割唯一性（如果在参与网络中存在既不属于S，也不属于T的点，则最小割不唯一）
mincost_unique = MaxFlow::mincost_unique();
