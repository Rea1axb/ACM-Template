/*
dfn[x]:x节点的时间戳，表示x节点的dfs序
low[x]:记录x子树中的点能够通过回边抵达点的最小时间戳

访问x节点时将low[x]初始化为 dfn[x]
对x点连向子树的树边 (x, y) 更新 low[x] = min(low[x], low[y])
对x点的回边 (x, y) 更新 low[x] = min(low[x], dfn[y])
注意树边的更新是回溯后用更新后的 low[y] 更新 low[x]

对树边(x, y), 若low[y] >= dfn[x]
说明 y 和其子树中点通过回边无法抵达 x 子树以外的节点
即 x 是图G的割点，在回溯之后检测每条树边即可得到割点

在DFS过程中，用一个栈保存DFS树上的点
当检测到一个割点 x 时
将栈中的元素弹出至栈顶元素为 x 子树搜索分支的第一个点

x和弹出元素构成一个点双连通分量
注意 x 不弹出，因为割点属于多个点双连通分量

重边对点连通度无影响
*/
namespace Tarjan {
    int dfn[MAXN];
    int low[MAXN];
    stack<int> stk;
    int n;//节点数
    int cnt;//双连通分量个数
    int cut[MAXN];//某个点是否是割点
    int resnum[MAXN];//某个点所属的双连通分量编号（割点的编号无效）
    vector<int> res[MAXN];//双连通分量内的点
    int times;

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++times;
        stk.push(u);
        int child = 0;//记录子节点数量，用于判断根节点是否是割点
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {//树边
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    cut[u] = 1;//该点为割点
                    cnt++;
                    res[cnt].clear();
                    while (1) {//u和弹出元素构成一个点双
                        int cur = stk.top();
                        stk.pop();
                        resnum[cur] = cnt;
                        res[cnt].push_back(cur);
                        if (cur == v) break;
                    }
                    resnum[u] = cnt;
                    res[cnt].push_back(u);
                }
            } else if (v != fa) {//回边
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa == -1 && child == 1)
            cut[u] = 0;//若根节点只有一个子节点，则不是割点
    }

    void init(int _n) {
        n = _n;
        fill(dfn, dfn + n + 1, 0);
        fill(cut, cut + n + 1, 0);
        fill(resnum, resnum + n + 1, 0);
        while(!stk.empty()) stk.pop();
        cnt = 0;
        times = 0;
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i])
                dfs(i, -1);
        }
    }
};
Tarjan::init(n);
Tarjan::solve();
