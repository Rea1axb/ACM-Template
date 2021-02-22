/*
最小割集Stoer-Wagner算法
prim算法不仅仅可以求最小生成树，也可以求“最大生成树”。
求解最小割集普遍采用Stoer-Wagner算法
1.res=INF，固定一个顶点P
2.从点P用类似prim的算法扩展出“最大生成树”，记录最后扩展的顶点和最后扩展的边
3.计算最后扩展到的顶点的切割值（即与此顶点相连的所有边权和），若比res小更新res
4.合并最后扩展的那条边的两个端点为一个顶点（当然他们的边也要合并）
5.转到2，合并N-1次后结束
6.res即为所求
prim本身复杂度是O(n^2)，合并n-1次，算法复杂度即为O(n^3)
如果在prim中加堆优化，复杂度为O(n*mlogm)

*/
ll G[MAXN][MAXN];
int node[MAXN];
ll dist[MAXN];
int vis[MAXN];
ll SW(int n) {
    int cnt = n;
    ll res = INF;
    for (int i = 1; i <= n; i++) {
        node[i] = i;
    }
    while (cnt > 1) {
        int pre = 1;
        for (int i = 1; i <= n; i++) {
            vis[i] = 0;
            dist[i] = 0;
        }
        for (int i = 1; i < cnt; i++) {
            int maxj = -1;
            for (int j = 2; j <= cnt; j++) {
                if (!vis[node[j]]) {
                    dist[node[j]] += G[node[pre]][node[j]];
                    if (maxj == -1 || dist[node[maxj]] < dist[node[j]]) {
                        maxj = j;
                    }
                }
            }
            vis[node[maxj]] = 1;
            if (i == cnt - 1) {
                int s = node[pre], t = node[maxj];
                res = min(res, dist[t]);
                for (int j = 1; j <= cnt; j++) {
                    G[s][node[j]] += G[node[j]][t];
                    G[node[j]][s] += G[node[j]][t];
                }
                node[maxj] = node[cnt--];
            }
            pre = maxj;
        }
    }
    return res;
}
