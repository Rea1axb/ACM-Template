/*
时间复杂度：O(n^2*sqrt(m))
增广路方法的复杂度是通过估计增广次数的上界得到的。
对于实际应用中的网络，增广次数往往很少，所以使用范围还是很广的，实用性强。
预流推进方法看似比增广路方法在复杂度上快很多，
然而实际上，预流推进方法的复杂度的上界是比较紧的。
对于一些稀疏图，预流推进方法的实际效果往往不如增广路方法。
*/
namespace MaxFlow {
    struct Edge {
        int v, rev;
        ll f;
    };
    vector<Edge> G[MAXN];
    int n, s, t;
    ll flow;
    vector<int> gap[MAXN], lst[MAXN];
    int ptr[MAXN];
    ll excess[MAXN];
    int h[MAXN], cnt[MAXN], work, hst;

    void add_edge(int u, int v, ll f) {
        G[u].push_back({v, (int)G[v].size(), f});
        G[v].push_back({u, (int)G[u].size() - 1, 0});
    }

    void updHeight(int x, int hh) {
        work++;
        if (h[x] != n + 1)
            cnt[h[x]]--;
        h[x] = hh;
        if (hh == n + 1)
            return;
        cnt[hh]++, hst = hh;
        gap[hh].push_back(x);
        if (excess[x])
            lst[hh].push_back(x), ptr[hh]++;
    }

    void globalRelabel() {
        work = 0;
        fill(h, h + n + 1, n + 1);
        fill(cnt, cnt + n + 1, 0);
        for (int i = 0; i <= hst; i++)
            lst[i].clear(), gap[i].clear(), ptr[i] = 0;
        queue<int> q;
        q.push(t);
        h[t] = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (auto &e : G[cur]) {
                if (h[e.v] == n + 1 && G[e.v][e.rev].f)
                    q.push(e.v), updHeight(e.v, h[cur] + 1);
                hst = h[cur];
            }
        }
    }

    void push(int x, Edge &e) {
        if (!excess[e.v])
            lst[h[e.v]].push_back(e.v), ptr[h[e.v]]++;
        ll res = min(excess[x], e.f);
        e.f -= res, G[e.v][e.rev].f += res;
        excess[x] -= res, excess[e.v] += res;
    }

    void discharge(int x) {
        int hh = n + 1;
        for (auto &e : G[x]) {
            if (e.f) {
                if (h[x] == h[e.v] + 1) {
                    push(x, e);
                    if (excess[x] <= 0)
                        return;
                } else {
                    hh = min(hh, h[e.v] + 1);
                }
            }
        }
        if (cnt[h[x]] > 1)
            updHeight(x, hh);
        else {
            for (int i = h[x]; i <= n; i++) {
                for (auto o : gap[i]) {
                    updHeight(o, n + 1);
                }
                gap[i].clear(), ptr[i] = 0;
            }
        }
    }

    void init(int _n) {
        n = _n;
        for (int i = 0; i <= n; i++) G[i].clear();
    }

    void solve(int _s, int _t) {
        s = _s, t = _t;
        fill(excess, excess + n + 1, 0);
        excess[s] = INF, excess[t] = -INF;
        globalRelabel();
        for (auto &e : G[s])
            push(s, e);
        while (hst >= 0) {
            while (!lst[hst].empty()) {
                int v = lst[hst].back();
                lst[hst].pop_back();
                discharge(v);
                if (work > 4 * (n + 1))
                    globalRelabel();
            }
            hst--;
        }
        flow = excess[t] + INF;
    }
}

//初始化
MaxFlow::init(n);

//建图
MaxFlow::add_edge(u, v, f);

//计算答案
MaxFlow::solve(s, t);

flow = MCMF::flow;
