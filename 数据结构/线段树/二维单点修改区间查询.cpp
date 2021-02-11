#define son(x) ((rt<<2)-2+x)
#define midx (xl+xr>>1)
#define midy (yl+yr>>1)
#define seg xl, xr, yl, yr
#define segall 1, n, 1, n
#define segfunc int xl, int xr, int yl, int yr
#define seg0 xl, midx, yl, midy
#define seg1 xl, midx, midy + 1, yr
#define seg2 midx + 1, xr, yl, midy
#define seg3 midx + 1, xr, midy + 1, yr
struct SegmentTree {
    ll sum;
    //ll maxn, minn;
}T[MAXN * MAXN * 4];
void push_up(int rt, segfunc) {
    T[rt].sum = T[son(0)].sum;
    //T[rt].maxn = T[son(0)].maxn;
    //T[rt].minn = T[son(0)].minn;
    if (yl < yr) {
        T[rt].sum += T[son(1)].sum;
        //T[rt].maxn = max(T[rt].maxn, T[son(1)].maxn);
        //T[rt].minn = min(T[rt].minn, T[son(1)].minn);
    }
    if (xl < xr) {
        T[rt].sum += T[son(2)].sum;
        //T[rt].maxn = max(T[rt].maxn, T[son(2)].maxn);
        //T[rt].minn = min(T[rt].minn, T[son(2)].minn);
    }
    if (yl < yr && xl < xr) {
        T[rt].sum += T[son(3)].sum;
        //T[rt].maxn = max(T[rt].maxn, T[son(3)].maxn);
        //T[rt].minn = min(T[rt].minn, T[son(3)].minn);
    }
}
void build(int rt, segfunc) {
    if (xl > xr || yl > yr) return;
    //T[rt] = {0, -INF, INF};
    T[rt] = {0};
    if (xl == xr && yl == yr) {
        T[rt].sum = arr[xl][yl];
        //T[rt].maxn = T[rt].minn = arr[xl][yl];
        return;
    }
    build(son(0), seg0);
    build(son(1), seg1);
    build(son(2), seg2);
    build(son(3), seg3);
    push_up(rt, seg);
}
void update(int rt, segfunc, int posx, int posy, ll k) {
    if (xl > xr || yl > yr) return;
    if (xl == xr && yl == yr) {
        T[rt].sum += k;
        //T[rt].minn = k;
        //T[rt].maxn = k;
        return;
    }
    if (posx <= midx && posy <= midy) {
        update(son(0), seg0, posx, posy, k);
    } else if (posx <= midx && posy > midy) {
        update(son(1), seg1, posx, posy, k);
    } else if (posx > midx && posy <= midy) {
        update(son(2), seg2, posx, posy, k);
    } else {
        update(son(3), seg3, posx, posy, k);
    }
    push_up(rt, seg);
}
ll query(int rt, segfunc, int qxl, int qyl, int qxr, int qyr) {
    if (xl > xr || yl > yr) {
        return {-INF, INF};
    }
    if (qxl <= xl && xr <= qxr && qyl <= yl && yr <= qyr) {
        return T[rt].sum;
        //return T[rt].maxn;
        //return T[rt].minn;
    }
    ll res = 0;
    //ll res = -INF;
    //ll res = INF;
    if (qxl <= midx && qyl <= midy) {
        ll tmp = query(son(0), seg0, qxl, qyl, qxr, qyr);
        res += tmp;
        //res = max(res, tmp);
        //res = min(res, tmp);
    }

    if (qxl <= midx && qyr > midy) {
        ll tmp = query(son(1), seg1, qxl, qyl, qxr, qyr);
        res += tmp;
        //res = max(res, tmp);
        //res = min(res, tmp);
    }

    if (qxr > midx && qyl <= midy) {
        ll tmp = query(son(2), seg2, qxl, qyl, qxr, qyr);
        res += tmp;
        //res = max(res, tmp);
        //res = min(res, tmp);
    }

    if (qxr > midx && qyr > midy) {
        ll tmp = query(son(3), seg3, qxl, qyl, qxr, qyr);
        res += tmp;
        //res = max(res, tmp);
        //res = min(res, tmp);
    }
    return res;
}

//建树
build(1, segall);
//将(x, y)的值加k
update(1, segall, x, y, k);
//求左上角为(x1, y1), 右下角为(x2, y2)的矩阵和
ans = query(1, segall, x1, y1, x2, y2);
