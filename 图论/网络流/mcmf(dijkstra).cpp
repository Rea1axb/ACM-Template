/* MCMF
 * 使用 Johnson 算法优化 dijsktra 负权最短路
 *
 * 调用：
 *     init(n) 初始化
 *     solve(s, t) 计算答案
 *     add(u, v, f, cost)建图
 *     cost - 费用， flow - 流量
 */
namespace MCMF {
    struct edge {
        int u, v;
        int next;
        ll f;//边的流量
        ll cost;//边的花费
    } e[MAXM * 2];
    struct node {
        int id;
        ll val;
        node(int a, ll b) : id(a), val(b) {}
        bool operator<(const node &t) const { return val > t.val; }
    };
    int first[MAXN];
    ll H[MAXN];
    int idx;
    int n, s, t;
    ll flow, cost;//流量和花费
    //ll mincost;//最小费用
    ll dist[MAXN], path_v[MAXN], path_e[MAXN];//path_v记录上一个点，path_e记录上一条边

    void add_edge(int u, int v, ll f, ll cost) {
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

    bool dijkstra() {
        priority_queue<node> q;
        for (int i = 1; i <= n; i++) {
            dist[i] = INF;
        }
        dist[s] = 0;
        q.push(node(s, 0));
        while (!q.empty()) {
            node cur = q.top();
            q.pop();
            if (dist[cur.id] < cur.val)
                continue;
            for (int i = first[cur.id]; i != -1; i = e[i].next) {
                int v = e[i].v;
                ll dis = dist[cur.id] + e[i].cost + H[cur.id] - H[v];
                if (e[i].f > 0 && dist[v] > dis) {
                    dist[v] = dis;
                    path_e[v] = i;
                    path_v[v] = cur.id;
                    q.push(node(v, dis));
                }
            }
        }
        if (dist[t] == INF)
            return false;
        for (int i = 0; i <= n; i++) {
            H[i] += dist[i];
        }
        ll f = INF;
        for (int v = t; v != s; v = path_v[v]) {
            f = min(f, e[path_e[v]].f);
        }
        flow += f;
        cost += f * H[t];
        //mincost = min(mincost, cost); //最小费用可行流
        for (int v = t; v != s; v = path_v[v]) {
            e[path_e[v]].f -= f;
            e[path_e[v] ^ 1].f += f;
        }
        return 1;
    }

    void solve(int _s, int _t) {
        s = _s;
        t = _t;
        flow = cost = 0;
        //mincost = INF;
        fill(H, H + n + 1, 0);
        while (dijkstra());
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
