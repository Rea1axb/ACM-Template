#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 60000;
const ll INF = 1e18;
namespace MaxFlow {
    struct Edge {
        int v, rev;
        ll f;
    };

    int n, s, t;
    int cur[MAXN], dep[MAXN], gap[MAXN];
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
ll d[MAXN];
int main() {
    int n, m;
    int s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    MaxFlow::init(n + 2);

    int ss = n + 1, tt = n + 2; //附加源点和附加汇点
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll low, up;
        scanf("%d%d%lld%lld", &u, &v, &low, &up);
        MaxFlow::add_edge(u, v, up - low);
        d[u] -= low;
        d[v] += low;
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        if (d[i] > 0) {
            MaxFlow::add_edge(ss, i, d[i]);
            sum += d[i];
        } else {
            MaxFlow::add_edge(i, tt, -d[i]);
        }
    }
    MaxFlow::solve(ss, tt);
    ll flow1 = MaxFlow::flow;
    MaxFlow::add_edge(t, s, INF);
    MaxFlow::solve(ss, tt);
    ll flow2 = MaxFlow::flow;
    if (flow1 + flow2 != sum) { //不是满流
        printf("please go home to sleep\n");
        return 0;
    }
    //答案为(t, s)的实际流量，存在G[s].back().f中
    printf("%lld\n", MaxFlow::G[s].back().f);
    return 0;
}
