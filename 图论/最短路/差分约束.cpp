/*
差分约束系统是否有解：图中是否存在负环，若图不连通需要加入一个超级源点并向
其他点连一条权值为0的边

求最大值：将符号全部转化为<=，求最短路
求最小值：将符号全部转化为>=，求最长路

不等式的标准化：
A-B=C 转化为 A-B>=C 和 A-B<=C

如果是整数域遇到 A-B<C 可以转化为 A-B<=C-1
*/

bool inq[MAXN];
ll dist[MAXN];
int cnt[MAXN];
int spfa(int s) {
    for (int i = 0; i <= n; i++) {
        dist[i] = INF; //dist[i] = -INF;
        inq[i] = 0;
        cnt[i] = 0;
    }
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        inq[cur] = 0;
        cnt[cur]++;
        if (cnt[cur] > n) return 0; //因为加入了超级源点，图中点的数量是n+1
        for (int i = first[cur]; i != -1; i = e[i].next) {
            int v = e[i].v;
            ll w = e[i].w;
            if (dist[v] > dist[cur] + w) { //dist[v] < dist[cur] + w
                dist[v] = dist[cur] + w;
                if (!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return 1;
}
