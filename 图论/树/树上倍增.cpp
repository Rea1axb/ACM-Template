/*
树上倍增的本质是二进制拆分
*/
const int DEG = 20;
int deg[MAXN];//点的深度
int fa[MAXN][DEG];//不同问题表示的意义不一样，可以修改，这里表示结点的第2^i个祖先。
void init() {
    fill(deg, deg + n + 1, 0);
}
void bfs(int root) {
    deg[root] = 1;
    queue<int> q;
    q.push(root);
    fa[root][0] = root;//更新根节点的第一个祖先
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 1; i < DEG; i++) {
            fa[cur][i] = fa[fa[cur][i-1]][i-1];//根据第一个祖先，逐步更新第2^i个祖先
        }
        for (int i = first[cur]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (deg[v]) continue;
            deg[v] = deg[cur] + 1;
            fa[v][0] = cur;//更新v的第一个祖先，不同问题的更新方式不同
            q.push(v);
        }
    }
}

/*
k级祖先查询
*/
int kthfa(int u, int k) {
    int bit = 0;
    while (k) {
        if (k & 1) u = fa[u][bit];
        k >>= 1;
        bit++;
    }
    return u;
}

/*
例子：开始时手中的数是节点 u 的权值，从 u 到 v 的路径中，如果一个点的权值大于手中
的数，则更新手中的数，问更新的次数。
*/
const int DEG = 20;
int deg[MAXN];
int fa[MAXN][DEG];//表示从节点往上，第 2^i 个比该节点权值大的点
void bfs(int root) {
    deg[root] = 1;
    queue<int> q;
    q.push(root);
    fa[root][0] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 1; i < DEG; i++) {
            fa[cur][i] = fa[fa[cur][i-1]][i-1];
        }
        for (int i =first[cur]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (deg[v]) continue;
            deg[v] = deg[cur] + 1;
            if (val[v] < val[cur]) {
                fa[v][0] = cur;
            } else {
                int x = cur;
                for (int j = DEG - 1; j >= 0; j--) {
                    if (fa[x][j] > 0 && val[fa[x][j]] <= val[v]) {
                        x = fa[x][j];
                    }
                }
                fa[v][0] = fa[x][0];
            }
            q.push(v);
        }
    }
}
bfs(1);
int x = u;
int ans = 0;
for (int i = DEG - 1; i >= 0; i--) {
    if (deg[fa[x][i]] >= deg[v]) {
        x = fa[x][i];
        ans += (1 << i);
    }
}
cout<<ans;
