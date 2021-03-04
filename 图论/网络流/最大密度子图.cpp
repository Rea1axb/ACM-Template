#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1010;
const int MAXM = 1e5 + 10;
const ll INF = 1e18;
const double eps = 1e-8;
namespace MaxFlow {
    struct Edge {
        int v, rev;
        double f;
    };

    int n, s, t;
    int cur[MAXN], dep[MAXN], gap[MAXN];
    double flow;
    vector<Edge> G[MAXN];

    void add(int u, int v, double f) {
        G[u].push_back({v, (int) G[v].size(), f});
        G[v].push_back({u, (int) G[u].size() - 1, 0});
    }

    double dfs(int u, double lim) {
        if (u == t)
            return lim;
        double num = 0;
        for (int &i = cur[u], v; i < G[u].size(); ++i) {
            double f = G[u][i].f;
            if (dep[v = G[u][i].v] == dep[u] - 1 && f > eps) {
                f = dfs(v, min(lim - num, f));
                G[v][G[u][i].rev].f += f;
                G[u][i].f -= f;
                num += f;
                if (lim - num <= eps) return num;
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
        for (gap[0] = n; dep[s] <= n; ) {
            flow += dfs(s, INF);
        }
    }

    vector<int> getans() {
        vector<int> vis(n + 1);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            for (auto e : G[now]) {
                if (!vis[e.v] && e.f > eps) {
                    q.push(e.v);
                    vis[e.v] = 1;
                }
            }
        }
        return vis;
    }
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pair<int, int> > E(m + 1);
    vector<int> deg(n + 1);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &E[i].first, &E[i].second);
        deg[E[i].first]++, deg[E[i].second]++;
    }
    if (m == 0) {
        printf("1\n1\n");
        return 0;
    }
    double left = 0, right = m + 1;
    double limit = 1.0 / n / n; //查找精度
    while (right - left >= limit) {
        double mid = (left + right) / 2;
        MaxFlow::init(n + 2);
        int s = n + 1, t = s + 1;
        for (int i = 1; i <= n; i++) {
            MaxFlow::add(s, i, m);
            MaxFlow::add(i, t, 2 * mid - deg[i] + m);
        }
        for (int i = 1; i <= m; i++) {
            MaxFlow::add(E[i].first, E[i].second, 1);
            MaxFlow::add(E[i].second, E[i].first, 1);
        }
        MaxFlow::solve(s, t);
        double res = (m * n - MaxFlow::flow) / 2;
        if (res > eps) {
            left = mid;
        } else {
            right = mid;
        }
    }
    MaxFlow::init(n + 2);
    int s = n + 1, t = s + 1;
    for (int i = 1; i <= n; i++) {
        MaxFlow::add(s, i, m);
        MaxFlow::add(i, t, 2 * left - deg[i] + m);
    }
    for (int i = 1; i <= m; i++) {
        MaxFlow::add(E[i].first, E[i].second, 1);
        MaxFlow::add(E[i].second, E[i].first, 1);
    }
    MaxFlow::solve(s, t);
    vector<int> vis = MaxFlow::getans();
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            ans.push_back(i);
        }
    }
    printf("%d\n", ans.size());
    for (auto o : ans) { //输出最大密度子图中的点
        printf("%d\n", o);
    }
    return 0;
}
