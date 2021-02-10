#define lc rt<<1
#define rc rt<<1|1
#define tmid (T[rt].l+T[rt].r>>1)

struct SegmentTree {
    int l, r;
    ll sum, add;
} T[MAXM << 2];

void push_up(int rt) {
    T[rt].sum = T[lc].sum + T[rc].sum;
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

void update(int rt, int pos, ll k) {
    if (T[rt].l == T[rt].r) {
        T[rt].sum += k;
        return;
    }
    if (pos <= tmid)
        update(lc, pos, k);
    else
        update(rc, pos, k);
    push_up(rt);
}

ll query(int rt, int l, int r) {
    if (l <= T[rt].l && T[rt].r <= r)
        return T[rt].sum;
    ll res = 0;
    if (l <= tmid)
        res += query(lc, l, r);
    if (r > tmid)
        res += query(rc, l, r);
    return res;
}
