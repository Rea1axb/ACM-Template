/*
一般图:
1.对于不存在孤立点的图，|最大匹配|+|最小边覆盖|=|E|
2.|最大独立集|+|最小顶点覆盖|=|V|

二分图:
|最大匹配|=|最小顶点覆盖|

最小路径覆盖：有向图中，能经过所有点的最小路径(不是边)数

DAG最小路径覆盖：
把原图每个点i拆成xi和yi构建二分图，
若原图存在边i->j，则在二分图中连边xi->yi，
原图最小路径覆盖即为|原图的顶点|-|二分图最大匹配|

*/
namespace BiMatch {//匈牙利算法，时间复杂度O(V*E)
    int n;//左边的点的数量
    struct edge {
        int u, v;
        int next;
    } e[MAXM * 2];
    int first[MAXN];
    int idx;
    int linker[];//右边的点
    bool used[];//右边的点

    void add(int a, int b) {
        e[idx].u = a;
        e[idx].v = b;
        e[idx].next = first[a];
        first[a] = idx++;
    }

    void init(int _n) {
        n = _n;
        fill(first, first + n + 1, -1);
        idx = 0;
    }

    bool dfs(int u) {
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!used[v]) {
                used[v] = 1;
                if (linker[v] == -1 || dfs(linker[v])) {
                    linker[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

    int hungry() {
        int res = 0;
        memset(linker, -1, sizeof(linker));
        for (int u = 1; u <= n; u++) {
            memset(used, false, sizeof(used));
            if (dfs(u)) {
                res++;
            }
        }
        return res;
    }
}
BiMatch::init(n);
BiMatch::add(u, v);
ans = BiMatch::hungry();
