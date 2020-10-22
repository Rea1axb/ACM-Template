/*
例题：
三种操作：
1.连接x, y，这条边的有效时间是k天
2.查询x点所在集合的大小
3.当天结束

对操作次数进行分治，在操作树上加删边，树上的每个节点可以看成是操作的集合
保留涵盖时间区间的有效操作，将剩余操作按时间划分到两端的子树，
退出子树的时候撤销加边操作。
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define lc rt<<1
#define rc rt<<1|1
#define tmid ((T[rt].l+T[rt].r)>>1)
const int MAXN = 1e6 + 10;
struct QUE {
    int op, day;
    int x, y;
    int ans;
} que[MAXN];
namespace DSU {
    int f[MAXN], sz[MAXN], top;
    struct node {
        int l, r;
        vector<pair<int, int> > val; // 能产生影响的边
    } T[MAXN * 2];
    struct STK {
        int x, y;
    } stk[MAXN * 2];

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            f[i] = i;
            sz[i] = 1;
        }
        top = 0;
    }

    int find(int x) { return f[x] == x ? x : find(f[x]); }

    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (sz[fx] > sz[fy]) swap(fx, fy);
        sz[fy] += sz[fx];
        stk[++top] = {fx, fy};
        f[fx] = fy;
    }

    void back(int lasttop) {
        while (top > lasttop) {
            sz[stk[top].y] -= sz[stk[top].x];
            f[stk[top].x] = stk[top].x;
            top--;
        }
    }

    void build(int rt, int l, int r) {
        T[rt] = {l, r};
        if (l == r) {
            T[rt].val.clear();
            return;
        }
        build(lc, l, tmid);
        build(rc, tmid + 1, r);
    }

    void update(int rt, int l, int r, int x, int y) {
        if (l <= T[rt].l && T[rt].r <= r) {
            T[rt].val.push_back(make_pair(x, y));
            return;
        }
        if (l <= tmid)
            update(lc, l, r, x, y);
        if (r > tmid)
            update(rc, l, r, x, y);
    }

    void solve(int rt) {
        int lasttop = top;
        for (auto tmp : T[rt].val) {
            merge(tmp.first, tmp.second);
        }

        if (T[rt].l == T[rt].r) {
            if (que[T[rt].l].op == 2) {
                que[T[rt].l].ans = sz[find(que[T[rt].l].x)];
            }
            back(lasttop);
            return;
        }
        solve(lc);
        solve(rc);
        back(lasttop);
    }
}

DSU::init(n);
DSU::build(1, 1, m);//m为操作次数

int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    DSU::init(n);
    DSU::build(1, 1, m);
    int now = 1;
    vector<int> endtime(m + 1); //记录第i天的最后一次操作是第几次操作
    for (int i = 1; i <= m; i++) {
        que[i].day = now;
        scanf("%d", &que[i].op);
        if (que[i].op == 1) {
            scanf("%d%d", &que[i].x, &que[i].y);
        } else if (que[i].op == 2) {
            scanf("%d", &que[i].x);
        } else {
            endtime[now] = i;
            now++;
        }
    }
    endtime[now] = m;
    for (int i = 1; i <= m; i++) {
        if (que[i].op == 1) {
            int right = min(now, que[i].day + k - 1);
            DSU::update(1, i, endtime[right], que[i].x, que[i].y);
        }
    }
    DSU::solve(1);
    for (int i = 1; i <= m; i++) {
        if (que[i].op == 2) {
            printf("%d\n", que[i].ans);
        }
    }
    return 0;
}
