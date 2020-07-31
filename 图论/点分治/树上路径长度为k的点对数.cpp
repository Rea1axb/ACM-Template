//
// Created by Rea1 on 2020/3/9.
//
#pragma comment(linker, "/STACK:1024000000,1024000000")

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
const int MAXN = 50010;
const int MAXM = 50010;
const int INF = 1e9;
struct edge {
    int u,v;
    ll w;
    int next;
}e[MAXM * 2];
int first[MAXN];
int idx;
int n;
void add(int a, int b, ll c) {
    e[idx].u = a;
    e[idx].v = b;
    e[idx].w = c;
    e[idx].next = first[a];
    first[a] = idx++;
}
void init() {
    fill(first, first + n + 1, -1);
    idx = 0;
}
int sz[MAXN], mson[MAXN], vis[MAXN];
ll dist[MAXN];
int tolsize, root, tol;
ll res, k;
void get_root(int x, int fa) {
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
void get_dis(int x, int fa, ll w) {
    dist[++tol] = w;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa || vis[v]) continue;
        get_dis(v, x, w + e[i].w);
    }
}
int left_bound(int l, ll x) {
    int ans = 0, r = tol;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (dist[mid] < x) l = mid + 1;
        else ans = mid, r = mid - 1;
    }
    return ans;
}
int right_bound(int l, ll x) {
    int ans = 0, r = tol;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (dist[mid] <= x) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}
ll cal(int x, ll w) {
    ll ans = 0;
    tol = 0;
    get_dis(x, 0, w);
    sort(dist + 1, dist + tol + 1);
    int l = 1;
    while (l < tol && dist[l] + dist[tol] < k) l++;
    while (l < tol && dist[l] * 2 <= k) {
        int left = left_bound(l + 1, k - dist[l]);
        int right = right_bound(l + 1, k - dist[l]);
        if (right >= left) ans += (right - left + 1);
        l++;
    }
    return ans;
}
void solve(int x) {
    vis[x] = 1;
    res += cal(x, 0);
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v]) continue;
        res -= cal(v, e[i].w);
        tolsize = sz[v];root = 0;
        get_root(v, x);
        solve(root);
    }
}
int main() {
    scanf("%d%d", &n, &k);
    init();
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v, 1);
        add(v, u, 1);
    }
    tolsize = n; root = 0;
    mson[0] = INF;
    get_root(1, 0);
    solve(root);
    printf("%lld\n", res);
    return 0;
}
