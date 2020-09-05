#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
struct Tree {
    int l, r;
    ll sum;
}T[MAXN * 40];
int root[MAXN], val[MAXN];
int tol;
vector<int> lisan;

int getid(int x) {
    return lower_bound(lisan.begin(), lisan.end(), x) - lisan.begin() + 1;
}

void init() {
    tol = 0;
    T[tol].l = T[tol].r = T[tol].sum = 0;
    root[tol] = 0;
}

void update(int l, int r, int &now, int pre, int pos) {
    T[++tol] = T[pre], T[tol].sum++, now = tol;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (mid >= pos)
        update(l, mid, T[now].l, T[pre].l, pos);
    else
        update(mid + 1, r, T[now].r, T[pre].r, pos);
}

int query(int l, int r, int pre, int now, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int sum = T[T[now].l].sum - T[T[pre].l].sum;
    if (sum >= k)
        return query(l, mid, T[pre].l, T[now].l, k);
    else
        return query(mid + 1, r, T[pre].r, T[now].r, k - sum);
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    lisan.clear();
    init();
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        lisan.push_back(val[i]);
    }
    sort(lisan.begin(), lisan.end());
    lisan.erase(unique(lisan.begin(), lisan.end()), lisan.end());
    for (int i = 1;i  <= n; i++) {
        update(1, n, root[i], root[i - 1], getid(val[i]));
    }
    for (int i = 1; i <= m; i++) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int ans = lisan[query(1, n, root[l - 1], root[r], k)- 1];
        printf("%d\n", ans);
    }
    return 0;
}
