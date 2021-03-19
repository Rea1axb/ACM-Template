/*
题面：有n个气球，每个气球是红色或者蓝色，有k个人，每个人选择 3 个气球并猜气球的颜色。
一个人猜对两个气球或以上的颜色就可以获得奖品。
判断是否存在一个气球的着色方案使得每个人都能领奖，若有则输出一种气球的着色方案。
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
const int MAXM = 1e5 + 10;
struct edge {
    int u, v;
    int next;
}e[MAXM * 2];
int n, idx, first[MAXN];
void add(int u, int v) {
    e[idx].u = u;
    e[idx].v = v;
    e[idx].next = first[u];
    first[u] = idx++;
}
void init() {
    idx = 0;
    fill(first, first + n * 2 + 1, -1); //点数两倍
}
namespace Tarjan {
    int dfn[MAXN];
    int low[MAXN];
    stack<int> stk;
    int vis[MAXN];
    int n, cnt, resnum[MAXN];
    vector<int> res[MAXN];
    int times;

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++times;
        stk.push(u);
        vis[u] = 1;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
            } else if (vis[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            cnt++;
            res[cnt].clear();
            while (!stk.empty()) {
                int cur = stk.top();
                stk.pop();
                resnum[cur] = cnt;
                res[cnt].push_back(cur);
                vis[cur] = 0;
                if (cur == u) break;
            }
        }
    }
    void init(int _n) {
        n = _n;
        fill(dfn, dfn + n + 1, 0);
        fill(resnum, resnum + n + 1, 0);
        fill(vis, vis + n + 1, 0);
        while (!stk.empty()) stk.pop();
        cnt = 0;
        times = 0;
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i])
                dfs(i, -1);
        }
        bool flag = 1;
        for (int i = 1; i <= n / 2; i++) {
            if (resnum[i] == resnum[i + n / 2]) { //无可行解
                flag = 0;
                break;
            }
        }
        if (!flag) {
            printf("-1\n");
            return;
        }
        for (int i = 1; i <= n / 2; i++) {
            if (resnum[i] < resnum[i + n / 2]) { //选择连通块编号小的点
                printf("R");
            } else {
                printf("B");
            }
        }
    }
}
int main() {
    int k;
    scanf("%d%d", &n, &k);
    init();
    for (int i = 1; i <= k; i++) {
        int a, b, c;
        char op1, op2, op3;
        scanf("%d %c %d %c %d %c", &a, &op1, &b, &op2, &c, &op3);
        int val1 = (op1 == 'B' ? 1 : 0); //val为1表示气球是B颜色
        int val2 = (op2 == 'B' ? 1 : 0);
        int val3 = (op3 == 'B' ? 1 : 0);
        add(a + (val1 ^ 1) * n, b + val2 * n); //如果a猜错了，那么b,c猜对
        add(a + (val1 ^ 1) * n, c + val3 * n);
        add(b + (val2 ^ 1) * n, a + val1 * n); //如果b猜错了，那么a,c猜对
        add(b + (val2 ^ 1) * n, c + val3 * n);
        add(c + (val3 ^ 1) * n, a + val1 * n); //如果c猜错了，那么a,b猜对
        add(c + (val3 ^ 1) * n, b + val2 * n);
    }
    Tarjan::init(n * 2);
    Tarjan::solve();
    return 0;
}

/*输出字典序最小的方案，爆搜，O(n*m)*/
namespace TwoSAT {
    int vis[MAXN];
    int stk[MAXN];
    int top;
    int n;
    vector<int> ans;
    bool dfs(int u) {
        if (vis[u > n / 2 ? u - n / 2 : u + n / 2]) return 0;
        if (vis[u]) return 1;
        stk[++top] = u;
        vis[u] = 1;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!dfs(v)) return 0;
        }
        return 1;
    }
    void init(int _n) {
        n = _n;
        ans.clear();
    }
    bool solve() {
        fill(vis, vis + n + 1, 0);
        for (int i = 1; i <= n / 2; i++) {
            if (!vis[i] && !vis[i + n / 2]) {
                top = 0;
                if (!dfs(i)) {
                    while (top) vis[stk[top--]] = 0;
                    if (!dfs(i + n / 2)) return 0;
                }
            }
        }
        return 1;
    }
    void print() {
        for (int i = 1; i <= n / 2; i++) {
            if (vis[i]) ans.push_back(i);
            else ans.push_back(i + n / 2);
        }
    }
}
TwoSAT::init(n * 2);
ok = TwoSAT::solve();
if (ok) TwoSAT::print();
for (auto o : TwoSAT::ans)
    printf("%d\n", o);
