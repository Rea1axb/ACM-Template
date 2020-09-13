#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
struct Tree {
    int l, r;
    ll sum;
}T[MAXN * 40];
int root[MAXN];
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

int query(int l, int r, int pre, int now, int k) { //区间 <= k 的数量
    if (r <= k) {
        return T[now].sum - T[pre].sum;
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if (l <= k)
        res += query(l, mid, T[pre].l, T[now].l, k);
    if (mid + 1 <= k)
        res += query(mid + 1, r, T[pre].r, T[now].r, k);
    return res;
}

//int query(int l, int r, int pre, int now, int k) { //区间 >= k 的数量
//    if (l >= k) {
//        return T[now].sum - T[pre].sum;
//    }
//    int mid = (l + r) >> 1;
//    int res = 0;
//    if (mid >= k)
//        res += query(l, mid, T[pre].l, T[now].l, k);
//    if (r >= k)
//        res += query(mid + 1, r, T[pre].r, T[now].r, k);
//    return res;
//}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> val(n + 1);
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
        int posk = getid(k);
        if (lisan[posk - 1] != k) posk--; // <= k
        int ans = query(1, n, root[l - 1], root[r], posk);
        printf("%d\n", ans);
    }
    return 0;
}
