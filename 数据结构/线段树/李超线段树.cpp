/*
给定一个平面直角坐标系，支持动态插入一条线段，
询问从某一个位置x看能看到的最高的一条线段
线段树以区间为核心，维护的是每一个区间的最优势线段（中点位置最高的线段）
*/

#define lc rt<<1
#define rc rt<<1|1

struct line {
    double k, b; //区间最优势线段的k和b
    int l, r; //最优势线段的定义域
    int flag; //该区间是否有最优势线段
    double cal(int pos) {
        return k * pos + b;
    }
}T[MAXN << 2];

void build(int rt, int l, int r) {
    T[rt].k = T[rt].b = 0;
    T[rt].l = 1, T[rt].r = MAXX;
    T[rt].flag = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
void update(int rt, int l, int r, line k) {
    if (k.l <= l && r <= k.r) {
        //被插入线段完全覆盖当前区间
        if (!T[rt].flag) {
            //如果当前区间还没有最优势线段，直接将最优势线段置为k
            T[rt] = k;
        } else if (k.cal(l) - T[rt].cal(l) >= eps && k.cal(r) - T[rt].cal(r) >= eps) {
            //如果被插入线段优于区间最优势线段，直接更新
            T[rt] = k;
        } else {
            if (l == r) return;
            int mid = (l + r) >> 1;
            //保证区间最优势线段是在区间中点位置最高的线段
            if (k.cal(mid) - T[rt].cal(mid) >= eps) {
                swap(T[rt], k);
            }
            //将非最优势线段下推
            if (k.cal(l) - T[rt].cal(l) >= eps) {
                update(lc, l, mid, k);
            } else {
                update(rc, mid + 1, r, k);
            }
        }
    } else {
        //检查左右区间
        int mid = (l + r) >> 1;
        if (k.l <= mid)
            update(lc, l, mid, k);
        if (k.r > mid)
            update(rc, mid + 1, r, k);
    }
}
double query(int rt, int l, int r, int pos) { //查询在pos位置最高线段的取值
    if (!T[rt].flag) return 0;
    if (l == r) {
        return T[rt].cal(l);
    }
    int mid = (l + r) >> 1;
    double res = T[rt].cal(pos);
    if (pos <= mid)
        res = max(res, query(lc, l, mid, pos));
    else
        res = max(res, query(rc, mid + 1, r, pos));
    return res;
}

//建树
build(1, 1, MAXX);
//插入一条线段
update(1, 1, MAXX, {k, b, l, r, 1});
//查询pos处的答案
ans = query(1, 1, MAXX, pos);
