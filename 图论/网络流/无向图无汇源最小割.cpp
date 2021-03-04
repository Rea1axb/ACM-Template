/*
最小割集Stoer-Wagner算法
prim算法不仅仅可以求最小生成树，也可以求“最大生成树”。
求解最小割集普遍采用Stoer-Wagner算法
1.res=INF，固定一个顶点P
2.从点P用类似prim的算法扩展出“最大生成树”，记录最后扩展的顶点和最后扩展的边
3.计算最后扩展到的顶点的切割值（即与此顶点相连的所有边权和），若比res小更新res
4.合并最后扩展的那条边的两个端点为一个顶点（当然他们的边也要合并）
5.转到2，合并N-1次后结束
6.res即为所求
prim本身复杂度是O(n^2)，合并n-1次，算法复杂度即为O(n^3)
如果在prim中加堆优化，复杂度为O(n*mlogm)

*/
ll G[MAXN][MAXN];
int node[MAXN];
ll dist[MAXN];
int vis[MAXN];
ll SW(int n) {
    int cnt = n;
    ll res = INF;
    for (int i = 1; i <= n; i++) {
        node[i] = i;
    }
    while (cnt > 1) {
        int pre = 1;
        for (int i = 1; i <= n; i++) {
            vis[i] = 0;
            dist[i] = 0;
        }
        for (int i = 1; i < cnt; i++) {
            int maxj = -1;
            for (int j = 2; j <= cnt; j++) {
                if (!vis[node[j]]) {
                    dist[node[j]] += G[node[pre]][node[j]];
                    if (maxj == -1 || dist[node[maxj]] < dist[node[j]]) {
                        maxj = j;
                    }
                }
            }
            if (maxj == -1) return -1; //图不连通
            vis[node[maxj]] = 1;
            if (i == cnt - 1) {
                int s = node[pre], t = node[maxj];
                res = min(res, dist[t]);
                for (int j = 1; j <= cnt; j++) {
                    G[s][node[j]] += G[node[j]][t];
                    G[node[j]][s] += G[node[j]][t];
                }
                node[maxj] = node[cnt--];
            }
            pre = maxj;
        }
    }
    return res;
}
int main() {
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                G[i][j] = 0;
            }
        }
        for (int i = 1; i <= m; i++) {
            int u, v;
            ll w;
            scanf("%d%d%lld", &u, &v, &w);
            u++, v++;
            G[u][v] += w;
            G[v][u] += w;
        }
        printf("%lld\n", SW(n));
    }
    return 0;
}

/*
堆优化版本
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 3e3 + 10;
const int MAXM = 1e5 + 10;
const ll INF = 1e18;
struct edge {
    int u,v;
    ll w;
    int next;
}e[MAXM * 2];
int first[MAXN];
int n, m;
int idx;
int link[MAXN];
void add(int a, int b, ll c) {
    e[idx].u = a;
    e[idx].v = b;
    e[idx].w = c;
    e[idx].next = first[a];
    first[a] = idx++;
}

int f[MAXN];
void init() {
    fill(first, first + n + 1, -1);
    fill(link, link + n + 1, -1);
    for (int i = 1; i <= n; i++) f[i] = i;
    idx = 0;
}
int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}
void merge(int u, int v) {
    int p = u;
    while (link[p] != -1) {
        p = link[p];
    }
    link[p] = v;
    f[v] = u;
}
struct node {
    int id;
    ll cost;
    bool operator < (const node &t) const {
        return cost < t.cost;
    }
};
int vis[MAXN];
ll dist[MAXN];
ll mincut(int cnt, int &s, int &t) {
    for (int i = 1; i <= n; i++) {
        vis[i] = 0;
        dist[i] = 0;
    }
    priority_queue<node> q;
    t = 1;
    while (--cnt) {
        vis[s = t] = 1;
        for (int u = s; u != -1; u = link[u]) {
            for (int i = first[u]; i != -1; i = e[i].next) {
                int v = e[i].v;
                v = find(v);
                if (!vis[v]) {
                    q.push({v, dist[v] += e[i].w});
                }
            }
        }
        t = 0;
        while (!t) {
            if (q.empty()) return -1; //图不连通
            node cur = q.top();
            q.pop();
            if (dist[cur.id] == cur.cost)
                t = cur.id;
        }
    }
    return dist[t];
}
ll SW() {
    ll res = INF;
    for (int i = n, s, t; i > 1; i--) {
        res = min(res, mincut(i, s, t));
        if (res == -1)
            break;
        merge(s, t);
    }
    return res;
}
int main() {
    while (~scanf("%d%d", &n, &m)) {
        init();
        for (int i = 1; i <= m; i++) {
            int u, v;
            ll w;
            scanf("%d%d%lld", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }
        printf("%lld\n", SW());
    }
    return 0;
}
