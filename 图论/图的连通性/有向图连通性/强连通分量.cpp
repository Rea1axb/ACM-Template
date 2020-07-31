/*

有向图边分类
在遍历有向图时会产生一棵DFS 树
有向图中的边可以划分为
1 DFS 树上的树边
2 连接祖先节点的回边
3 连向子树的前向边
4 连向非祖先且非子树关系节点的横跨边

首先通过DFS 确立树边
前向边对于SCC（强连通分量） 的计算没有影响
回边可以跟树边形成的路径构成环
横跨边(x,y) 是否产生贡献取决于是否有路径能够从y 抵达x
因此我们只需考虑用回边和横跨边来更新low 值

dfn[x]:x节点的时间戳，表示x节点的dfs序
low[x]:记录x子树中的点能够通过回边抵达点的最小时间戳

访问x 点时将lowx 初始化为dfnx，并将x加入栈中
对x 点连向子树的树边(x; y) 更新lowx = min(lowx; lowy)
对其它边(x; y) 若连接点被访问过且在栈中
则更新lowx = min(lowx; dfny)
当回溯后出现lowx == dfnx 时弹出栈中元素直到x 弹出
弹出元素构成一个强连通分量(标号为逆拓扑序)
*/
namespace Tarjan {
int dfn[MAXN];
int low[MAXN];
stack<int> stk;
int vis[MAXN];//记录某个点是否已入栈
int n;//节点数
int cnt;//强连通分量个数
int resnum[MAXN];//某个点所属的强连通分量编号
vector<int> res[MAXN];//强连通分量内的点
int times;

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++times;
    stk.push(u);
    vis[u] = 1;
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (!dfn[v]) {//树边
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        cnt++;
        while (!stk.empty()) {
            int cur = stk.top();
            resnum[cur] = cnt;
            res[cnt].push_back(cur);
            stk.pop();
            if (cur == u) break;
        }
    }
}

void init(int _n) {
    n = _n;
    fill(dfn, dfn + n + 1, 0);
    fill(cutedge, cutedge + n + 1, 0);
    fill(resnum, resnum + n + 1, 0);
    fill(vis, vis + n + 1, 0);
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
};
Tarjan::init(n);
Tarjan::solve();
