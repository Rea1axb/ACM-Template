/*
例题：给出一棵边权树，一开始所有点都是白点
要求维护两种操作：
1. 颜色取反（黑白互变）
2. 查询树上最远的两个白点之间的距离
首先建出点分树，然后每一个点开两个堆。
第一个堆记录子树中所有节点到父亲节点的距离C[MAXN]，
第二个堆记录所有子节点的堆顶B[MAXN]，
那么一个节点的堆2中的最大和次大加起来就是子树中经过这个节点的最长链。
然后开一个全局的堆，记录所有堆2中最大值和次大值之和。那么全局的堆顶就是答案
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
const int MAXM = 1e5 + 10;
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
void init() {
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
        if (dep[pos[f[l][lg]]] < dep[pos[f[r - (1 << lg) + 1][lg]]]) {
            return f[l][lg];
        } else {
            return f[r - (1 << lg) + 1][lg];
        }
    }

    int get_dis(int u, int v) {
        int lca = query(u, v);
        return dep[pos[u]] + dep[pos[v]] - 2 * dep[pos[lca]];
    }
};
struct Heap {
    priority_queue<int> q, era;

    void ins(int val) {
        q.push(val);
    }

    void del(int val) {
        if (val) era.push(val);
    }

    int get_max() { //第一大元素
        while (!q.empty() && !era.empty() && era.top() == q.top()) {
            q.pop();
            era.pop();
        }
        if (q.empty()) return 0;
        return q.top();
    }

    int get_semax() { //第二大元素
        int tmp = get_max();
        del(tmp);
        int res = get_max();
        ins(tmp);
        return res;
    }
}ANS, B[MAXN], C[MAXN * 2];
int sz[MAXN], mson[MAXN], vis[MAXN];
int tolsize, root, tol;
int belong[MAXN]; //点分树父节点
int belongsz[MAXN]; //点分树子树大小
int light[MAXN], ans[MAXN]; //light为0表示白点，ans记录每个点的统计答案
int num; //记录白点数量
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
void dfs(int x, int fa, int rt, int rtfa) { //
    C[rt].ins(LCA::get_dis(x, rtfa));
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa || vis[v]) continue;
        dfs(v, x, rt, rtfa);
    }
}
void build(int x, int fa) { //建立点分树
    belong[x] = fa; //记录点分树上节点的父节点
    belongsz[x] = 1;
    vis[x] = 1;
    if (fa) {
        C[x].ins(LCA::get_dis(x, fa));
        for (int i = first[x]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (vis[v]) continue;
            dfs(v, x, x, fa);
        }
        B[fa].ins(C[x].get_max());
    }
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v]) continue;
        tolsize = sz[v];root = 0;
        get_root(v, x);
        int nowroot = root;
        build(root, x);
        belongsz[x] += belongsz[nowroot];
    }
    ans[x] = B[x].get_max() + B[x].get_semax();
    ANS.ins(ans[x]);
}
void modify(int x) {
    if (light[x]) {
        light[x] = 0;
        ++num;
        ANS.del(ans[x]);
        ans[x] = B[x].get_max() + B[x].get_semax();
        ANS.ins(ans[x]);
        int last = x;
        int now = belong[x];
        while (now) {
            B[now].del(C[last].get_max());
            C[last].ins(LCA::get_dis(now, x));
            B[now].ins(C[last].get_max());
            ANS.del(ans[now]);
            if (light[now]) {
                if (B[now].get_semax()) ans[now] = B[now].get_max() + B[now].get_semax();
                else ans[now] = 0;
            } else {
                ans[now] = B[now].get_max() + B[now].get_semax();
            }
            ANS.ins(ans[now]);
            last = now;
            now = belong[now];
        }
    } else {
        light[x] = 1;
        --num;
        ANS.del(ans[x]);
        if (B[x].get_semax()) ans[x] = B[x].get_max() + B[x].get_semax();
        else ans[x] = 0;
        ANS.ins(ans[x]);
        int now = belong[x];
        int last = x;
        while (now) {
            B[now].del(C[last].get_max());
            C[last].del(LCA::get_dis(now, x));
            B[now].ins(C[last].get_max());
            ANS.del(ans[now]);
            if (light[now]) {
                if (B[now].get_semax()) ans[now] = B[now].get_max() + B[now].get_semax();
                else ans[now] = 0;
            } else {
                ans[now] = B[now].get_max() + B[now].get_semax();
            }
            ANS.ins(ans[now]);
            last = now;
            now = belong[now];
        }
    }
}
int query() {
    if (num == 0) return -1;
    else if (num == 1) return 0;
    else return ANS.get_max();
}
int main() {
    LCA::st_init(); //st初始化
    scanf("%d", &n);
    init();
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
    num = n;
    tolsize = n; root = 0;
    mson[0] = INF; //int INF
    get_root(1, 0); //得到重心
    build(root, 0); //建立点分树
    int m;
    scanf("%d", &m);
    while (m--) {
        char c[2];
        scanf("%s", c);
        if (c[0] == 'G') {
            printf("%d\n", query());
        } else {
            int x;
            scanf("%d", &x);
            modify(x);
        }
    }
    return 0;
}
