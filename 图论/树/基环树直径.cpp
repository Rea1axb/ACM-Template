/*
例题：求基环树森林的直径和
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 1e6 + 10;
const int MAXM = 1e6 + 10;

int n;
struct edge {
    int u, v;
    ll w;
    int next;
}e[MAXM * 2];
int first[MAXN];
int idx;

void add(int u, int v, int w) {
    e[idx].v = v;
    e[idx].w = w;
    e[idx].next = first[u];
    first[u] = idx++;
}

int dfn[MAXN], tol; //dfs序
int pre[MAXN], inloop[MAXN]; //pre:父节点; inloop:是否在环中
vector<int> loop; //环
ll sum[MAXN * 2]; //环拆成链后的前缀和
int q[MAXN * 2]; //队列
ll d[MAXN], len; //d[x]:x在非环子树中能到的最远距离; len:非环子树直径

void init() {
    fill(first, first + n + 1, -1);
    idx = 0;
    tol = 0;
}
void get_loop(int u, int fa) { //找环
    dfn[u] = ++tol;
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa) continue;
        if (!dfn[v]) {
            pre[v] = u;
            get_loop(v, u);
        } else {
            if (dfn[v] > dfn[u]) { //注意自环的影响
                inloop[v] = 1;
                loop.push_back(v);
                while (v != u) {
                    v = pre[v];
                    inloop[v] = 1;
                    loop.push_back(v);
                }
            }
        }
    }
}

void dp(int u, int fa) { //求非环子树的直径
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa || inloop[v]) continue;
        dp(v, u);
        len = max(len, d[u] + d[v] + e[i].w);
        d[u] = max(d[u], d[v] + e[i].w);
    }
}
void get_val(int u, int fa, int cnt) { //计算环拆成两倍长的链后的前缀和
    if (cnt == loop.size()) return;
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (i == fa || v != loop[cnt])
            continue;
        sum[cnt] = sum[cnt - 1] + e[i].w;
        get_val(v, i ^ 1, cnt + 1);
        return;
    }
}
ll solve(int u) {
    ll res;
    loop.clear();
    get_loop(u, 0);
    len = 0;
    int sz = loop.size();
    for (int i = 0; i < sz; i++) {
        dp(loop[i], 0);
        loop.push_back(loop[i]); //将环拆成两倍长的链
    }
    res = len;
    sz *= 2;
    get_val(loop[0], -1, 1);

    //单调队列
    int l = 1, r = 0;
    for (int i = 1; i <= sz; i++) {
        while (l <= r && q[l] <= i - sz / 2)
            l++;
        if (l <= r)
            res = max(res, sum[i - 1] - sum[q[l] - 1] + d[loop[i - 1]] + d[loop[q[l] - 1]]);
        while (l <= r && d[loop[i - 1]] - sum[i - 1] > d[loop[q[r] - 1]] - sum[q[r] - 1])
            r--;
        q[++r] = i;
    }
    return res;
}
int main() {
    scanf("%d", &n);
    init();
    for (int i = 1; i <= n; i++) {
        int v;
        int w;
        scanf("%d%d", &v, &w);
        add(i, v, w);
        add(v, i, w);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            ans += solve(i);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
