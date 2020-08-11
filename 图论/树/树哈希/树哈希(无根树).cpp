bool notp[MAXN * 2];
int prime[MAXN * 2], pnum;
void sieve(int n) {
    memset(notp, 0, sizeof(notp));
    notp[0] = notp[1] = 1;
    pnum = 0;
    for(int i = 2; i <= n; i++) {
        if(!(notp[i]))
            prime[++pnum] = i;
        for(int j = 1; j <= pnum && prime[j]*i <= n; j++) {
            notp[prime[j]*i] = 1;
            if(i % prime[j] == 0)
                break;
        }
    }
}
struct TreeHash {
    ull f[MAXN], g[MAXN], sz[MAXN]; //f[x]:x为根的子树的hash，g[x]:x为根的全树的hash
    int n;
    vector<int> G[MAXN];
    vector<int> asc; //排序后的排列

    void init(int _n) {
        n = _n;
        asc.clear();
        for (int i = 1; i <= n; i++)
            G[i].clear();

    }

    void add(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void dfs1(int u, int fa) {
        sz[u] = 1;
        f[u] = 1;
        for (auto v : G[u]) {
            if (v == fa) continue;
            dfs1(v, u);
            sz[u] += sz[v];
            f[u] = (f[u] + f[v] * prime[sz[v]] % mod) % mod;
        }
    }

    void dfs2(int u, int fa, ull val) {
        g[u] = (f[u] + val * prime[n - sz[u]] % mod) % mod;
        asc.push_back(g[u]);
        val = (val * prime[n - sz[u]] % mod + 1) % mod;
        for (auto v : G[u]) {
            if (v == fa) continue;
            dfs2(v, u, (val + f[u] - 1 - f[v] * prime[sz[v]] % mod + mod) % mod);
        }
    }

    void solve() {
        dfs1(1, 0);
        dfs2(1, 0, 0);
        sort(asc.begin(), asc.end());
    }

    bool operator == (const TreeHash &t) const {
        if (n != t.n) return 0;
        return asc == t.asc;
    }
}t1, t2;

//不一定要取模
sieve(); //根据题目判断筛多少素数
t1.init(n);
t2.init(n);
t1.add(u, v);
t1.solve();
t2.add(u, v);
t2.solve();
ans = t1 == t1;

/*
判断无根树同构：S(t1.f) == S(t2.f), S(x)表示数列x排序后的数列
*/
