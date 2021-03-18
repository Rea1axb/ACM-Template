/*
差分约束系统是否有解：图中是否存在负环，若图不连通需要加入一个超级源点并向
其他点连一条权值为0的边
一些情况下用栈实现并且加入超级源点能加快求答案的速度

求最大值：将符号全部转化为<=，求最短路
求最小值：将符号全部转化为>=，求最长路

不等式的标准化：
A-B=C 转化为 A-B>=C 和 A-B<=C

如果是整数域遇到 A-B<C 可以转化为 A-B<=C-1
*/

bool inq[MAXN];
ll dist[MAXN];
int cnt[MAXN];
//int stk[MAXN * 2]; 用栈取代队列相当于用dfs的性质优化，找环更快
int spfa(int s) {
    for (int i = 0; i <= n; i++) {
        dist[i] = INF; //dist[i] = -INF;最长路
        inq[i] = 0;
        cnt[i] = 0;
    }
    dist[s] = 0;
    queue<int> q;
    //int sum = 0; 所有进入队列的总数量
    q.push(s);
    cnt[s]++;
    //int top = 0;
    //stk[++top] = s;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        inq[cur] = 0;
        //sum++;
        //if (sum > 2e7) return 0; 数值大小根据数据规模和时限调整
        for (int i = first[cur]; i != -1; i = e[i].next) {
            int v = e[i].v;
            ll w = e[i].w;
            if (dist[v] > dist[cur] + w) { //dist[v] < dist[cur] + w 最长路
                dist[v] = dist[cur] + w;
                if (!inq[v]) {
                    inq[v] = 1;
                    cnt[cur]++;
                    if (cnt[cur] > n) return 0; //因为加入了超级源点，图中点的数量是n+1
                    q.push(v);
                }
            }
        }
    }
    return 1;
}
