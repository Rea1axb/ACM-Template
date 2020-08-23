/*
一般的树的直径可以用两遍bfs求得
当树的边权有负值时，无法用两遍bfs
*/
int vis[MAXN];
int d[MAXN];//d[x]:从节点 x 出发走向以 x 为根的子树，能够到达的最远节点的距离
int len;//树的直径
void dp(int x) {
    vis[x] = 1;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v]) continue;
        dp[v];
        len = max(len, d[x] + d[v] + e[i].w);
        d[x] = max(d[x], d[v] + e[i].w);
    }
}
