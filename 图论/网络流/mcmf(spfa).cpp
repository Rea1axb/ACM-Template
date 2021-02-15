namespace MCMF {
    struct edge {
        int u, v;
        int next;
        ll f;
        ll cost;
    } e[MAXM * 2];
    int first[MAXN];
    int idx;
    int n, s, t;
    ll flow, cost;
    //ll mincost;//最小费用
    ll dist[MAXN];
    bool vis[MAXN];
    int pre[MAXN];

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
    bool spfa() {
        queue<int> q;
        fill(vis, vis + n + 1, false);
        fill(pre, pre + n + 1, -1);
        for (int i = 1; i <= n; i++) {
            dist[i] = INF;
        }
        vis[s] = 1;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            vis[cur] = 0;
            for (int i = first[cur]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (e[i].f && dist[v] > dist[cur] + e[i].cost) {
                    dist[v] = dist[cur] + e[i].cost;
                    pre[v] = i;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = 1;
                    }
                }
            }
        }
        if (dist[t] == INF) {
            return false;
        }
        return true;
    }

    void solve(int _s, int _t) {
        s = _s;
        t = _t;
        ll res;
        flow = cost = 0;
        //mincost = INF;
        while (spfa()) {
            res = INF + 1;
            for (int i = pre[t]; i != -1; i = pre[e[i ^ 1].v]) {
                if (e[i].f < res) {
                    res = e[i].f;
                }
            }
            flow += res;
            for (int i = pre[t]; i != -1; i = pre[e[i ^ 1].v]) {
                e[i].f -= res;
                e[i ^ 1].f += res;
            }
            cost += dist[t] * res;
            //mincost = min(mincost, cost); //最小费用可行流
        }
    }
}

//初始化
MCMF::init(n);

//建图
MCMF::add(u, v, f, cost);

//计算答案
MCMF::solve(s, t);

flow = MCMF::flow;
cost = MCMF::cost;
