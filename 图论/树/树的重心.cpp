/*
以树的重心为根时，所有子树的大小都不超过整棵树大小的一半。

树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么到它们的距离和一样。

把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两棵树的重心的路径上。

在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离。
*/
int root;
int sz[MAXN];
int mson[MAXN];//最大子树大小
void get_centroid(int u, int fa) {
    sz[u] = 1;
    mson[u] = 0;
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa) continue;
        get_centroid(v, u);
        sz[u] += sz[v];
        if (sz[v] > mson[u]) mson[u] = sz[v];
    }
    mson[u] = max(mson[u], n - sz[u]);//向上的“子树”
    if (mson[u] < mson[root]) root = u;
}
