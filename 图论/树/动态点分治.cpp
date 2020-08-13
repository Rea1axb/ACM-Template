/*
例题：给出一棵 n 个点的点权树，允许修改点权，询问与点 x距离差小于等于 d 的点的点权和

对于每个点维护两棵权值线段树，分别维护以该点为重心的分治
层中到这个点的距离的权值和以及到这个点的点分树父亲距离的权
值和

在统计 x 节点的时候只要统计其到点分树树根的链上每个重心的
贡献值累加即可

点分树深度不超过logn
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 10;
const int MAXM = 2e5 + 10;
const int INF = 1e9;
const int DEG = 20;
struct edge {
    int u,v;
    int next;
}e[MAXM * 2];
int first[MAXN];
int idx;
int n;
void add(int a, int b) {
    e[idx].u = a;
    e[idx].v = b;
    e[idx].next = first[a];
    first[a] = idx++;
}
void init() { //初始化修改
    fill(first, first + n + 1, -1);
    idx = 0;
}
namespace LCA {
    int seq[MAXN * 2];//记录欧拉序对应的点的编号
    int dep[MAXN * 2];//记录欧拉序的深度
    int pos[MAXN];//记录节点在欧拉序中第一次出现的位置编号
    int cnt;//欧拉序
    int n;//节点数量
    int f[MAXN * 2][DEG];//ST表
    int logn[MAXN * 2];

    void st_init() {//预处理log，防止查询时影响速度
        logn[1] = 0;
        logn[2] = 1;
        for (int i = 3; i < MAXN * 2; i++) {
            logn[i] = logn[i / 2] + 1;
        }
    }

    void init(int _n) {
        n = _n;
        cnt = 0;
    }

    void dfs(int u, int fa, int depth) {
        seq[++cnt] = u;
        pos[u] = cnt;
        dep[cnt] = depth;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (v == fa) continue;
            dfs(v, u, depth + 1);
            seq[++cnt] = u;
            dep[cnt] = depth;
        }
    }

    void solve() {//ST表处理
        for (int i = 1; i <= n * 2; i++) {
            f[i][0] = seq[i];
        }
        for (int j = 1; j < DEG; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n * 2; i++) {
                if (dep[pos[f[i][j - 1]]] < dep[pos[f[i + (1 << (j - 1))][j - 1]]]) {
                    f[i][j] = f[i][j - 1];
                } else {
                    f[i][j] = f[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int query(int u, int v) {
        int l = min(pos[u], pos[v]);
        int r = max(pos[u], pos[v]);
        int lg = logn[r - l + 1];
        return min(f[l][lg], f[r - (1 << lg) + 1][lg]);
    }

    int get_dis(int u, int v) {
        int lca = query(u, v);
        return dep[pos[u]] + dep[pos[v]] - 2 * dep[pos[lca]];
    }
};
struct BIT {
    vector<ll> c;
    int n;
    int lowbit(int x) {
        return x & (-x);
    }

    void updata(int i, int k) {//在i位置加上k
        while (i <= n) {
            c[i] += k;
            i += lowbit(i);
        }
    }

    ll getsum(int i) {//求A[1] + A[2] + ... + A[i]
        ll res = 0;
        while (i > 0) {
            res += c[i];
            i -= lowbit(i);
        }
        return res;
    }

    void change(int x, int k) {
        updata(x, k);
    }

    ll query(int l, int r) {
        return getsum(r) - getsum(l - 1);
    }

    void init(int _n) {
        n = _n;
        c.resize(n + 1, 0);
    }
}T1[MAXN], T2[MAXN];
int sz[MAXN], mson[MAXN], vis[MAXN];
int tolsize, root, tol;
int belong[MAXN]; //点分树父节点
int belongsz[MAXN]; //点分树子树大小
void get_root(int x, int fa) {//找树的重心
    sz[x] = 1; mson[x] = 0;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v] || v == fa) continue;
        get_root(v, x);
        sz[x] += sz[v];
        if (sz[v] > mson[x]) mson[x] = sz[v];
    }
    if (tolsize - sz[x] > mson[x]) mson[x] = tolsize - sz[x];
    if (mson[x] < mson[root]) root = x;
}
void build(int x, int fa) { //建立点分树
    belong[x] = fa; //记录点分树上节点的父节点
    belongsz[x] = 1;
    vis[x] = 1;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v]) continue;
        tolsize = sz[v];root = 0;
        get_root(v, x);
        int nowroot = root;
        build(root, x);
        belongsz[x] += belongsz[nowroot];
    }
}
void modify(int x, int val) { //将x点权值加上val，更新影响
    int now = x;
    while (now) {
        int fa = belong[now];
        T1[now].change(LCA::get_dis(now, x) + 1, val);
        if (fa) T2[now].change(LCA::get_dis(fa, x) + 1, val);
        now = fa;
    }
}
ll query(int x, int k) { //统计与x点距离不超过k的点权和
    ll ans = 0;
    int now = x, last = 0;
    while (now) {
        int d = LCA::get_dis(now, x);
        if (d > k) {
            last = now;
            now = belong[now];
            continue;
        }
        ans += T1[now].query(1, min(k - d + 1, T1[now].n)); //统计该分治层所有信息
        if (last) ans -= T2[last].query(1, min(k - d + 1, T2[last].n)); //删去已统计的子分治层信息
        last = now;
        now = belong[now];
    }
    return ans;
}
int main() {
    LCA::st_init(); //st初始化
    int m;
    scanf("%d%d", &n, &m);
    init();
    vector<ll> val(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &val[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    LCA::init(n);
    LCA::dfs(1, 0, 0);
    LCA::solve();
    fill(vis, vis + n + 1, 0);
    tolsize = n; root = 0;
    mson[0] = INF; //int INF
    get_root(1, 0); //得到重心
    build(root, 0); //建立点分树
    for (int i = 1; i <= n; i++) { //树状数组初始化
        T1[i].init(belongsz[i] * 2); //如果空间够，尽量开大些
        T2[i].init(belongsz[i] * 2);
    }
    for (int i = 1; i <= n; i++) {
        modify(i, val[i]);
    }
    int lastans = 0;
    for (int i = 1; i <= m; i++) {
        int op,x,y;
        scanf("%d%d%d", &op, &x, &y);
        x = x ^ lastans;
        y = y ^ lastans;
        if (op == 0) {
            lastans = query(x, y);
            printf("%d\n", lastans);
        } else {
            modify(x, y - val[x]); //将x点权值改为y
            val[x] = y;
        }
    }
    return 0;
}
