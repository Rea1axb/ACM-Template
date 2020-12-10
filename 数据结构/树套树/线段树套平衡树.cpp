/*
对于线段树上的某一个节点，建立一棵平衡树，包含该节点所覆盖的序列。
具体操作时我们可以将序列元素一个个插入，每经过一个线段树节点，
就将该元素加入到该节点的平衡树中。

每个元素加入logN个平衡树，空间复杂度O((N+Q)logN)

基本修改查询时间复杂度O(log^2(N))
*/

/*
例题：
1.查询k在区间内的排名
2.查询区间内排名为k的值
3.修改某一位值上的数值
4.查询k在区间内的前驱(前驱定义为严格小于x，且最大的数，若不存在输出-2147483647)
5.查询k在区间内的后继(后继定义为严格大于x，且最小的数，若不存在输出2147483647)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 5e4 + 10;
namespace Treap {
    struct node {
        int ch[2];
        ll val; //权值
        ll sum;
        int sz; //子树大小
        int rnd;
    }Tree[MAXN * 80];

    int cnt;
    int root[MAXN << 2], x, y, z;
    void init(int n) {
        srand((unsigned)time(NULL));
        for (int i = 1; i <= cnt; i++) {
            Tree[i].sz = Tree[i].ch[0] = Tree[i].ch[1] = 0;
        }
        cnt = 0;
        for (int i = 1; i <= n * 4; i++) {
            root[i] = 0;
        }
    }
    int new_node(ll val) {
        ++cnt;
        Tree[cnt].sz = 1;
        Tree[cnt].val = val;
        Tree[cnt].sum = val;
        Tree[cnt].rnd = rand();
        return cnt;
    }

    void update(int x) {
        int l = Tree[x].ch[0];
        int r = Tree[x].ch[1];
        Tree[x].sz = 1 + Tree[l].sz + Tree[r].sz;
        Tree[x].sum = Tree[x].val + Tree[l].sum + Tree[r].sum;
    }


    //split函数根据题目需要添加，按哪些东西分裂
    void split_val(int now, ll k, int &x, int &y) {//将以now为根的树按照权值(k)分为以l为根的树和以r为根的树。
        if (!now) {
            x = y = 0;
            return;
        }
        if (Tree[now].val <= k) {
            x = now;
            split_val(Tree[now].ch[1], k, Tree[now].ch[1], y);
        } else {
            y = now;
            split_val(Tree[now].ch[0], k, x, Tree[now].ch[0]);
        }
        update(now);
    }

    void split_sz(int now, int k, int &x, int &y) {//将以now为根的树按照子树大小(k)分为以l为根的树和以r为根的树。
        if (!now) {
            x = y = 0;
            return;
        }
        if (Tree[Tree[now].ch[0]].sz < k) {
            x = now;
            split_sz(Tree[now].ch[1], k - Tree[Tree[now].ch[0]].sz - 1, Tree[now].ch[1], y);
        } else {
            y = now;
            split_sz(Tree[now].ch[0], k, x, Tree[now].ch[0]);
        }
        update(now);
    }

    int merge(int x, int y) {//把以l为根的树和以r为根的树合并
        if(!x || !y)
            return x + y;
        if (Tree[x].rnd < Tree[y].rnd) {
            Tree[x].ch[1] = merge(Tree[x].ch[1], y);
            update(x);
            return x;
        } else {
            Tree[y].ch[0] = merge(x, Tree[y].ch[0]);
            update(y);
            return y;
        }
    }

    void insert(int pos, ll val) { //插入节点
        split_val(root[pos], val, x, y);
        root[pos] = merge(merge(x, new_node(val)), y);
    }

    void del(int pos, ll val) { //删除节点
        split_val(root[pos], val, x, z);
        split_val(x, val - 1, x, y);
        y = merge(Tree[y].ch[0], Tree[y].ch[1]);
        root[pos] = merge(merge(x, y), z);
    }

    int get_rank(int pos, ll val) { //查询小于等于val的数量
        split_val(root[pos], val - 1, x, y);
        int res = Tree[x].sz;
        root[pos] = merge(x, y);
        return res;
    }

    ll get_kth(int now, int k) { //查询now的子树中排名为k的数
        while (1) {
            int l = Tree[now].ch[0];
            int r = Tree[now].ch[1];
            if (k <= Tree[l].sz) {
                now = l;
            } else if (k == Tree[l].sz + 1) {
                return Tree[now].val;
            } else {
                k -= Tree[l].sz + 1;
                now = r;
            }
        }
    }

    ll get_pre(int pos, ll val) { //查询前驱
        split_val(root[pos], val - 1, x, y);
        if (Tree[x].sz == 0) return -INT_MAX;
        ll res = get_kth(x, Tree[x].sz);
        root[pos] = merge(x, y);
        return res;
    }

    ll get_next(int pos, ll val) { //查询后继
        split_val(root[pos], val, x, y);
        if (Tree[y].sz == 0) return INT_MAX;
        ll res = get_kth(y, 1);
        root[pos] = merge(x, y);
        return res;
    }
}
#define lc rt<<1
#define rc rt<<1|1
#define tmid ((T[rt].l+T[rt].r)>>1)
struct SegmentTree {
    int l, r;
}T[MAXN << 2];
void build(int rt, int l, int r) {
    T[rt] = SegmentTree{l, r};
    if (l == r) {
        return;
    }
    build(lc, l, tmid);
    build(rc, tmid + 1, r);
}
void update_del(int rt, int pos, ll val) {
    Treap::del(rt, val);
    if (T[rt].l == T[rt].r) return;
    if (pos <= tmid) {
        update_del(lc, pos, val);
    } else {
        update_del(rc, pos, val);
    }
}
void update_ins(int rt, int pos, ll val) {
    Treap::insert(rt, val);
    if (T[rt].l == T[rt].r) return;
    if (pos <= tmid) {
        update_ins(lc, pos, val);
    } else {
        update_ins(rc, pos, val);
    }
}
ll query1(int rt, int l, int r, ll k) {
    if (l <= T[rt].l && T[rt].r <= r) {
        return Treap::get_rank(rt, k);
    }
    ll res = 0;
    if (l <= tmid)
        res += query1(lc, l, r, k);
    if (r > tmid)
        res += query1(rc, l, r, k);
    return res;
}
ll query2(int l, int r, ll k) { //多一个二分，时间多一个logN
    int left = 0, right = 1e8 + 1;
    while (left < right) {
        int mid = (left + right) >> 1;
        ll tmp1 = query1(1, l, r, mid) + 1;
        ll tmp2 = query1(1, l, r, mid + 1) + 1;
        if (tmp1 < k) {
            if (tmp2 > k) return mid;
            else left = mid + 1;
        } else if (tmp1 == k){
            if (tmp2 == k) left = mid + 1;
            else return mid;
        } else {
            right = mid;
        }
    }
    return right;
}
ll query3(int rt, int l, int r, ll k) {
    if (l <= T[rt].l && T[rt].r <= r) {
        return Treap::get_pre(rt, k);
    }
    ll res = -INT_MAX;
    if (l <= tmid)
        res = max(res, query3(lc, l, r, k));
    if (r > tmid)
        res = max(res, query3(rc, l, r, k));
    return res;
}
ll query4(int rt, int l, int r, ll k) {
    if (l <= T[rt].l && T[rt].r <= r) {
        return Treap::get_next(rt, k);
    }
    ll res = INT_MAX;
    if (l <= tmid)
        res = min(res, query4(lc, l, r, k));
    if (r > tmid)
        res = min(res, query4(rc, l, r, k));
    return res;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<ll> val(n + 1);
    Treap::init(n);
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &val[i]);
        update_ins(1, i, val[i]);
    }
    while (m--) {
        int op, x, y, z;
        scanf("%d%d%d", &op, &x, &y);
        if (op == 1) {
            scanf("%d", &z);
            printf("%lld\n", query1(1, x, y, z) + 1);
        } else if (op == 2) {
            scanf("%d", &z);
            printf("%lld\n", query2(x, y, z));
        } else if (op == 3) {
            update_del(1, x, val[x]);
            val[x] = y;
            update_ins(1, x, val[x]);
        } else if (op == 4) {
            scanf("%d", &z);
            printf("%lld\n", query3(1, x, y, z));
        } else if (op == 5) {
            scanf("%d", &z);
            printf("%lld\n", query4(1, x, y, z));
        }
    }
    return 0;
}
