/*
LuoGu-P4074
给定一棵树，每个点有颜色和相应的val，第x次访问某种颜色能获得价值val[color]*W[x],
查询访问树上两点间的路径能获得的价值和，带修改。

跑树的括号序，在括号序上进行莫队操作
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
const int MAXNUM = 1e6 + 10;
const int MAXQ = 1e5 + 10;
const int DEG = 20;
int block;
struct query {
    int l, r;
    int id;
    ll ans;
    int updatenum;
}q[MAXQ];
struct update {
    int pos;
    int val1;
    int val2;
}u[MAXQ];
bool cmp_block(query a, query b) { //分块排序
    if (a.l / block != b.l / block) return a.l < b.l;
    if (a.r / block != b.r / block) return a.l / block & 1 ? a.r < b.r : a.r > b.r;
    return a.r / block & 1 ? a.id < b.id : a.id > b.id;
}
bool cmp_id(query a, query b) {
    return a.id < b.id;
}
ll val[MAXN], W[MAXN];
int color[MAXN], nowcolor[MAXN], cnt[MAXN];
int vis[MAXN];
ll sum;

void add(int _pos) {
    if (vis[_pos])
        sum -= val[color[_pos]] * W[cnt[color[_pos]]--];
    else
        sum += val[color[_pos]] * W[++cnt[color[_pos]]];
    vis[_pos] ^= 1;
}
void del(int _pos) {
    vis[_pos] ^= 1;
    if (vis[_pos])
        sum += val[color[_pos]] * W[++cnt[color[_pos]]];
    else
        sum -= val[color[_pos]] * W[cnt[color[_pos]]--];
}
void modify(int _pos, int _val) {
    if (vis[_pos]) {
        del(_pos);
        color[_pos] = _val;
        add(_pos);
    } else {
        color[_pos] = _val;
    }
}
struct edge {
    int u, v;
    int next;
}e[MAXN * 2];
int first[MAXN], idx;
int tol, id1[MAXN], id2[MAXN], pos[MAXN * 2];
//id1：点进入时候的括号序；id2：点离开时候的括号序；pos：括号序代表的点
void add_edge(int u, int v) {
    e[idx].u = u;
    e[idx].v = v;
    e[idx].next = first[u];
    first[u] = idx++;
}
void init(int _n) {
    idx = 0;
    tol = 0;
    fill(first, first + _n + 1, -1);
}
void dfs(int x, int fa) {
    id1[x] = ++tol; //括号序
    pos[tol] = x;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs(v, x);
    }
    id2[x] = ++tol; //括号序
    pos[tol] = x;
}
namespace LCA {
    int fa[MAXN][DEG];
    int dep[MAXN];

    void bfs(int root) {
        queue<int> q;
        dep[root] = 0;
        fa[root][0] = root;
        q.push(root);
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            for (int i = 1; i < DEG; i++) {
                fa[tmp][i] = fa[fa[tmp][i - 1]][i - 1];
            }
            for (int i = first[tmp]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (v == fa[tmp][0]) continue;
                dep[v] = dep[tmp] + 1;
                fa[v][0] = tmp;
                q.push(v);
            }
        }
    }

    int query(int u, int v) {
        if (dep[u] > dep[v]) {
            swap(u, v);
        }
        int hu = dep[u], hv = dep[v];
        int tu = u, tv = v;
        for (int k = hv - hu, i = 0; k; k >>= 1, i++) {
            if (k & 1) {
                tv = fa[tv][i];
            }
        }
        if (tu == tv) {
            return tu;
        }
        for (int i = DEG - 1; i >= 0; i--) {
            if (fa[tu][i] == fa[tv][i]) {
                continue;
            }
            tu = fa[tu][i];
            tv = fa[tv][i];
        }
        return fa[tu][0];
    }
}
int main() {
    int n, m, Q;
    scanf("%d%d%d", &n, &m, &Q);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &val[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &W[i]);
    }
    init(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(1, -1);
    LCA::bfs(1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
        nowcolor[i] = color[i];
    }
    int querycnt = 0, updatecnt = 0;
    for (int i = 1; i <= Q; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) { //查询
            ++querycnt;
            int x, y;
            scanf("%d%d", &x, &y);
            if (id1[x] > id1[y]) swap(x, y);
            if (LCA::query(x, y) == x) {
                q[querycnt].l = id1[x];
                q[querycnt].r = id1[y];
            } else {
                q[querycnt].l = id2[x];
                q[querycnt].r = id1[y];
            }
            q[querycnt].id = querycnt;
            q[querycnt].updatenum = updatecnt;
        } else { //修改
            ++updatecnt;
            scanf("%d%d", &u[updatecnt].pos, &u[updatecnt].val2);
            u[updatecnt].val1 = nowcolor[u[updatecnt].pos];
            nowcolor[u[updatecnt].pos] = u[updatecnt].val2;
        }
    }
    block = pow(n, 2.0/3.0);
    sort(q + 1, q + querycnt + 1, cmp_block);
    sum = 0;
    for (int i = 1, l = 1, r = 0, t = 0; i <= querycnt; i++) {
        while (l > q[i].l) add(pos[--l]);
        while (r < q[i].r) add(pos[++r]);
        while (l < q[i].l) del(pos[l++]);
        while (r > q[i].r) del(pos[r--]);
        while (t < q[i].updatenum) {
            ++t;
            modify(u[t].pos, u[t].val2);
        }
        while (t > q[i].updatenum) {
            modify(u[t].pos, u[t].val1);
            t--;
        }
        int x = pos[l], y = pos[r];
        int lca = LCA::query(x, y);
        if (lca != x && lca != y) { //此时lca没有计算贡献
            add(lca);
            q[i].ans = sum;
            del(lca);
        } else {
            q[i].ans = sum;
        }
    }
    sort(q + 1, q + querycnt + 1, cmp_id);
    for (int i = 1; i <= querycnt; i++) {
        printf("%lld\n", q[i].ans);
    }
    return 0;
}
