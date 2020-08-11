/*
对一棵树进行 DFS，无论是第一次访问还是回溯，每次到达一个结点时都将编号记录下来，
可以得到一个长度为 2*n-1 的序列，这个序列被称作这棵树的欧拉序列
从u走到v的过程中一定会经过lca(u,v)，但不会经过lca(u,v)的祖先。
因此，从u走到v的过程中经过的欧拉序最小的结点就是lca(u,v)
LCA问题可以在O(n)的时间转化为等规模的RMQ问题。
*/
namespace LCA {
    int seq[MAXN * 2];//记录欧拉序对应的点的编号
    int dep[MAXN * 2];//记录欧拉序的深度
    int pos[MAXN];//记录节点在欧拉序中第一次出现的位置编号
    int cnt;//欧拉序
    int n;//节点数量
    int f[MAXN * 2][DEG];//ST表
    int logn[MAXN * 2];

    void st_init() {//预处理log，防止查询时影响速度
        logn[1] = 0;
        logn[2] = 1;
        for (int i = 3; i < MAXN * 2; i++) {
            logn[i] = logn[i / 2] + 1;
        }
    }

    void init(int _n) {
        n = _n;
        cnt = 0;
    }

    void dfs(int u, int fa, int depth) {
        seq[++cnt] = u;
        pos[u] = cnt;
        dep[cnt] = depth;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (v == fa) continue;
            dfs(v, u, depth + 1);
            seq[++cnt] = u;
            dep[cnt] = depth;
        }
    }

    void solve() {//ST表处理
        for (int i = 1; i <= n * 2; i++) {
            f[i][0] = seq[i];
        }
        for (int j = 1; j < DEG; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n * 2; i++) {
                if (dep[f[i][j - 1]] < dep[f[i + (1 << (j - 1))][j - 1]]) {
                    f[i][j] = f[i][j - 1];
                } else {
                    f[i][j] = f[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int query(int u, int v) {
        int l = min(pos[u], pos[v]);
        int r = max(pos[u], pos[v]);
        int lg = logn[r - l + 1];
        return min(f[l][lg], f[r - (1 << lg) + 1][lg]);
    }
};
LCA::st_init(); //最开始初始化，before T--
LCA::init(n);
LCA::dfs(1, 0, 0);
LCA::solve();
ans = LCA::query(u, v);
