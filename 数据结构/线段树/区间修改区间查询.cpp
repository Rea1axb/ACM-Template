#define lc rt<<1
#define rc rt<<1|1
#define tmid (T[rt].l+T[rt].r>>1)

struct SegmentTree {
    int l, r;
    ll sum, add;
    //ll maxn;//区间最值
    void upd(ll val) {
        sum += val * (r - l + 1);
        //maxn += val;
        add += val;
    }

} T[MAXN << 2];

void push_up(int rt) {
    T[rt].sum = T[lc].sum + T[rc].sum;
    //T[rt].maxn = max(T[lc].maxn, T[rc].maxn);
}

void build(int rt, int l, int r) {
    T[rt] = SegmentTree{l, r, 0, 0};
    if (l == r) {
        T[rt].sum = arr[l];
        return;
    }
    build(lc, l, tmid);
    build(rc, tmid + 1, r);
    push_up(rt);
}

void push_down(int rt) {
    if (T[rt].add) {
        T[lc].upd(T[rt].add);
        T[rc].upd(T[rt].add);
        T[rt].add = 0;
    }
}

void update(int rt, int l, int r, ll k) {
    if (l <= T[rt].l && T[rt].r <= r) {
        T[rt].upd(k);
        return;
    }
    push_down(rt);
    if (l <= tmid)
        update(lc, l, r, k);
    if (r > tmid)
        update(rc, l, r, k);
    push_up(rt);
}

ll query(int rt, int l, int r) {
    if (l <= T[rt].l && T[rt].r <= r)
        return T[rt].sum;
    push_down(rt);
    ll res = 0;
//    ll res = INF;
    if (l <= tmid)
        res += query(lc, l, r);
    if (r > tmid)
        res += query(rc, l, r);
//    if (l <= tmid)
//        res = max(res, query(lc, l, r));
//    if (r > tmid)
//        res = max(res, query(rc, l, r));
    return res;
}
