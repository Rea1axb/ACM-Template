#define lc rt<<1
#define rc rt<<1|1
#define tmid ((T[rt].l+T[rt].r)>>1)
int sum[MAXM * 4], add[MAXM * 4];
int a[MAXM], n;
int idx;
int first[MAXM];
struct edge {
    int v, next;
} e[MAXM * 2];
int f[MAXM], son[MAXM], size[MAXM], dfn[MAXM], dep[MAXM], top[MAXM];
ll seq[MAXM];
int cnt;
/*
f是节点的父亲,son是重儿子,size是以该节点为根的子树大小, dfn是给节点重新编上的序号.
seq是与dfn相反的数组的值,表示标到的这个号表示的原节点的权值, top是目前节点所在链的顶端.
dep是结点的深度
*/

//---------------------加边和预处理--------------------------------
void eadd(int a, int b) {
    e[idx].v = b;
    e[idx].next = first[a];
    first[a] = idx++;
}
void init() {
    fill(first, first + n + 1, -1);
    fill(son, son + n + 1, 0);
    idx = 1;
    cnt = 0;
}
void dfs1(int u, int fa, int depth) {
    f[u] = fa;
    size[u] = 1;
    dep[u] = depth;
    int maxson = -1;
    for(int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if(v == fa)
            continue;
        dfs1(v, u, depth + 1);
        size[u] += size[v];
        if(size[v] > maxson)
            son[u] = v, maxson = size[v];
    }
}
void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++cnt;
    seq[cnt] = a[u];
    if(!son[u])
        return;
    dfs2(son[u], t);
    for(int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if(v != son[u] && v != f[u])
            dfs2(v, v);
    }
}


//--------------------------线段树----------------------------------
struct SegmentTree {
    int l, r;
    ll sum, add;

    void upd(ll val) {
        sum += val * (r - l + 1);
        add += val;
    }

} T[MAXM << 2];

void push_up(int rt) {
    T[rt].sum = T[lc].sum + T[rc].sum;
}

void build(int rt, int l, int r) {
    T[rt] = SegmentTree{l, r, 0, 0};
    if (l == r) {
        T[rt].sum = seq[l];
        return;
    }
    build(lc, l, tmid);
    build(rc, tmid + 1, r);
    push_up(rt);
}

void push_down(int rt) {
    if (T[rt].add) {
        T[lc].upd(T[rt].add);
        T[rc].upd(T[rt].add);
        T[rt].add = 0;
    }
}

void update(int rt, int l, int r, ll k) {
    if (l <= T[rt].l && T[rt].r <= r) {
        T[rt].upd(k);
        return;
    }
    push_down(rt);
    if (l <= tmid)
        update(lc, l, r, k);
    if (r > tmid)
        update(rc, l, r, k);
    push_up(rt);
}

ll query(int rt, int l, int r) {
    if (l <= T[rt].l && T[rt].r <= r)
        return T[rt].sum;
    push_down(rt);
    ll res = 0;
    if (l <= tmid)
        res += query(lc, l, r);
    if (r > tmid)
        res += query(rc, l, r);
    return res;
}

//----------------------------树上加、树上求和---------------------
void tadd(int x, int y, int k) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        update(1, dfn[top[x]], dfn[x], k);
        x = f[top[x]];
    }
    if(dep[x] > dep[y])
        swap(x, y);
    update(1, dfn[x], dfn[y], k);
}
ll tsum(int x, int y) {
    ll ans = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        ans = ans + query(1, dfn[top[x]], dfn[x]);
        x = f[top[x]];
    }
    if(dep[x] > dep[y])
        swap(x, y);
    ans = ans + query(1, dfn[x], dfn[y]);
    return ans;
}


int main() {
    int m;
    int num;//根节点序号
    scanf("%d%d%d%d", &n, &m, &num, &mod);
    init();
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        eadd(u, v);
        eadd(v, u);
    }
    dfs1(num, 0, 1);
    dfs2(num, num);
    build(1, 1, n);
    for(int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if(op == 1) { //将树从x到y节点最短路径上所有节点的值都加上z
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            tadd(x, y, z);
        } else if(op == 2) { //求树从x到y节点最短路径上所有节点的值之和
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%lld\n", tsum(x, y));
        } else if(op == 3) { //将以x为根节点的子树内所有节点值都加上z
            int x, z;
            scanf("%d%d", &x, &z);
            update(1, dfn[x], dfn[x] + size[x] - 1, z);
        } else if(op == 4) { //求以x为根节点的子树内所有节点值之和
            int x;
            scanf("%d", &x);
            printf("%lld\n", query(1, dfn[x], dfn[x] + size[x] - 1));
        }
    }
    return 0;
}
