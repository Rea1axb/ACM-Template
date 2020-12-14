/*
dfn[x]:x节点的时间戳，表示x节点的dfs序
low[x]:记录x子树中的点能够通过回边抵达点的最小时间戳

对树边(x, y)，若low[x] > dfn[x]
说明 y 点无法通过树边以外的边到达 y 子树以外的点
即树边(x, y)为桥（方法1）
对点下，若在递归结束后有low[x] == dfn[x]
也可以说明其与父节点连接的树边为桥（方法2）
将桥打上删除标记剩下的图就是每个边双连通分量

求解边双连通分量存在重边时，不能因为边连向父节点就不做判断
因为到父节点的边也可能是回边，需要判断是否跟树边是同一条边
在建图时将无向边转化为两条有向边时记录其属于的边id
当连向父节点的边和树边id不相同的时候说明该边是回边
*/
namespace Tarjan {
    int dfn[MAXN];
    int low[MAXN];
    int fedge[MAXN];//记录到某个点的树边
    stack<int> stk;
    int n, m;//节点数
    int cnt;//双连通分量个数
    int cutedge[MAXM * 2];//某条边是否是桥
    int resnum[MAXN];//某个点所属的双连通分量编号
    vector<int> res[MAXN];//边连通分量内的点
    int times;

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++times;
        stk.push(u);
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {//树边
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    cutedge[i] = cutedge[i ^ 1] = 1;//该边为桥
                }
            } else if (i != (fedge[u] ^ 1)) {//可能有重边，记录的是到达该点的树边
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            cnt++;
            res[cnt].clear();
            while (!stk.empty()) {
                int cur = stk.top();
                stk.pop();
                resnum[cur] = cnt;
                res[cnt].push_back(cur);
                if (cur == u) break;
            }
        }
    }

    void init(int _n, int _m) {
        n = _n;
        m = _m;
        fill(dfn, dfn + n + 1, 0);
        fill(cutedge, cutedge + m + m + 1, 0);
        fill(resnum, resnum + n + 1, 0);
        fill(fedge, fedge + n + 1, -1);
        while (!stk.empty()) stk.pop();
        cnt = 0;
        times = 0;
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i])
                dfs(i, -1);
        }
    }
}
Tarjan::init(n);
Tarjan::solve();
