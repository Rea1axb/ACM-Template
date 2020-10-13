#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
struct Tree {
    int l, r;
    ll sum;
}T[MAXN * 40];//如果update次数很多要相应增大空间
int root[MAXN];
int tol;
map<int,int> pos;

void init() {
    tol = 0;
    T[tol].l = T[tol].r = T[tol].sum = 0;
    root[tol] = 0;
    pos.clear();
}

void update(int l, int r, int &now, int pre, int pos, int add) {
    T[++tol] = T[pre], T[tol].sum += add, now = tol;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (mid >= pos)
        update(l, mid, T[now].l, T[pre].l, pos, add);
    else
        update(mid + 1, r, T[now].r, T[pre].r, pos, add);
}

int query(int l, int r, int rt, int left) {
    if (l >= left)
        return T[rt].sum;
    int mid = (l + r) >> 1;
    if (mid >= left)
        return query(l, mid, T[rt].l, left) + T[T[rt].r].sum;
    else
        return query(mid + 1, r, T[rt].r, left);
}
int main() {
    int n;
    scanf("%d", &n);
    init();
    vector<int> val(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
        if (!pos.count(val[i])) {
            update(1, n, root[i], root[i - 1], i, 1);
        } else {
            int tmp;
            update(1, n, tmp, root[i - 1], pos[a[i]], -1);
            update(1, n, root[i], tmp, i, 1);
        }
        pos[a[i]] = i;
    }
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        int ans = query(1, n, root[r], l);
        printf("%d\n", ans);
    }
    return 0;
}
