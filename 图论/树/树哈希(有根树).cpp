const int seed = 131;
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
    ull f[MAXN], sz[MAXN]; //f[x]:x为根的子树的hash
    int n;
    int root;
    vector<int> G[MAXN];

    void init(int _n) {
        n = _n;
        for (int i = 1; i <= n; i++)
            G[i].clear();

    }

    void add(int u, int v) {
        G[u].push_back(v);
    }

    void dfs(int u) {
        sz[u] = 1;
        f[u] = 1;
        for (auto v : G[u]) {
            dfs(v);
            sz[u] += sz[v];
            f[u] = f[u] + f[v] * prime[sz[v] + seed]; //注意 sz[v] + seed 不能超过素数的数量
            //f[u] = f[u] + f[v] * prime[G[v].size() + seed];
        }
    }

    void solve() {
        dfs1(root);
    }

    bool operator == (const TreeHash &t) const {
        if (n != t.n) return 0;
        return f[root] == t.f[t.root];
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
判断有根树同构：t1.f[root] == t2.f[root]
*/
