/*
1 <= n <= 200000
0 <= ai(pl[i]) <= 2 ^ 30
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 2e5 + 10;
int n;
int tol;
ll val[MAXN * 32];
int num[MAXN * 32];
int ch[MAXN * 32][2];
void init() {
    tol = 1;
    ch[0][0] = ch[0][1] = 0;
}
void insert(ll x) {
    int u = 0;
    for (int i = 30; i >= 0; i--) {
        int v = (x >> i) & 1;
        if (!ch[u][v]) {
            ch[tol][0] = ch[tol][1] = 0;
            ch[u][v] = tol++;
        }
        u = ch[u][v];
        num[u]++;
    }
    val[u] = x;
}
void del(ll x) {
    int u = 0;
    for (int i = 30; i >= 0; i--) {
        int v = (x >> i) & 1;
        u = ch[u][v];
        num[u]--;
    }
}
ll query(ll x) {
    int u = 0;
    for (int i = 30; i >= 0; i--) {
        int v = (x >> i) & 1;
        if(ch[u][v] && num[ch[u][v]] > 0)
            u = ch[u][v];
        else
            u = ch[u][v ^ 1];
    }
    return val[u];
}
struct node {
    int root;
    int id;
} p[MAXN];
ll p1[MAXN];
bool cmp(node a, node b) {
    return a.root < b.root;
}
int f[MAXN];
int find(int x) {
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}
int vis[MAXN];
int check() {
    for (int i = 1; i < n; i++) {
        if(find(i) != find(i + 1))
            return 1;
    }
    return 0;
}
int main() {
    init();
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &p1[i]);
        insert(p1[i]);
        f[i] = i;
    }
    sort(p1 + 1, p1 + n + 1);
    for (int i = 1; i <= n; i++) {
        p[i].id = i;
        p[i].root = i;
    }
    ll ans = 0;
    while(check()) {
        for (int i = 1; i <= n; i++) {
            p[i].root = find(p[i].id);
        }
        sort(p + 1, p + n + 1, cmp);
        int nowroot = p[1].root;
        memset(vis, 0, sizeof(vis));
        int last = 1;

        for (int i = 1; i <= n; i++) {
            if (!vis[nowroot] && p[i].root == nowroot)
                del(p1[p[i].id]);
            if (!vis[nowroot] && p[i + 1].root != nowroot) {
                vis[nowroot] = 1;
                ll minn = 1e18;
                int minj;
                ll tmp;
                for (int j = last; j <= i; j++) {
                    tmp = query(p1[p[j].id]);
                    if ((tmp ^ p1[p[j].id]) < minn) {
                        minn = (tmp ^ p1[p[j].id]);
                        minj = tmp;
                    }
                }
                ans += minn;
                int position = lower_bound(p1 + 1, p1 + n + 1, minj) - p1;
                for (int j = last; j <= i; j++) {
                    insert(p1[p[j].id]);
                }
                f[find(position)] = nowroot;
            }
            if(p[i + 1].root != nowroot) {
                nowroot = find(p[i + 1].root);
                last = i + 1;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
