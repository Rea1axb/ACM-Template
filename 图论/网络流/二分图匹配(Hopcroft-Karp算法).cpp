namespace BiMatch {//Hopcroft-Karp算法，时间复杂度O(sqrt(V)*E)
    int n;//左边点的数量
    int m;//右边点的数量
    struct edge {
        int u, v;
        int next;
    } e[MAXM * 2];
    int first[MAXN];
    int idx;
    int Mx[MAXN], dx[MAXN];
    int My[], dy[];//右边的点
    bool used[];//右边的点
    ll dis;

    void add(int a, int b) {
        e[idx].u = a;
        e[idx].v = b;
        e[idx].next = first[a];
        first[a] = idx++;
    }

    void init(int _n, int _m) {
        n = _n;
        m = _m;
        fill(first, first + n + 1, -1);
        idx = 0;
    }

    bool SearchP() {
        queue<int> q;
        dis = INF;
        fill(dx, dx + n + 1, -1);
        fill(dy, dy + m + 1, -1);
        for (int i = 1; i <= n; i++) {
            if (Mx[i] == -1) {
                q.push(i);
                dx[i] = 0;
            }
        }
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (dx[cur] > dis)
                break;
            for (int i = first[cur]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (dy[v] == -1) {
                    dy[v] = dx[cur] + 1;
                    if (My[v] == -1) {
                        dis = dy[v];
                    } else {
                        dx[My[v]] = dy[v] + 1;
                        q.push(My[v]);
                    }
                }
            }
        }
        return dis != INF;
    }

    bool dfs(int u) {
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!used[v] && dy[v] == dx[u] + 1) {
                used[v] = 1;
                if (My[v] != -1 && dy[v] == dis)
                    continue;
                if (My[v] == -1 || dfs(My[v])) {
                    My[v] = u;
                    Mx[u] = v;
                    return 1;
                }
            }
        }
        return 0;
    }

    int HK() {
        int res = 0;
        fill(Mx, Mx + n + 1, -1);
        fill(My, My + m + 1, -1);
        while (SearchP()) {
            fill(used, used + m + 1, 0);
            for (int i = 1; i <= n; i++) {
                if (Mx[i] == -1 && dfs(i))
                    res++;
            }
        }
        return res;
    }
}

BiMatch::init(n, m);
BiMatch::add(u, v);
ans = BiMatch::HK();

