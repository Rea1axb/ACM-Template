/*
DFS优化：用dfs（栈）代替队列
一般用于判断负环，可能会更慢
*/
bool flag; //flag == 1表示存在负环
bool vis[MAXN];
ll dist[MAXN];

for (int i = 1; i <= n; i++) {
    dist[i] = INF;
    vis[i] = 0;
}
dist[s] = 0;

void spfa(int x) {
    if (vis[x]) {
        flag = 1;
        return;
    }
    vis[x] = 1;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (dist[v] > dist[x] + e[i].w) {
            dist[v] = dist[x] + e[i].w;
            spfa(v);
            if (flag) return;
        }
    }
    vis[x] = 0;
}
