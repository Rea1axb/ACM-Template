/*
动态开点权值线段树合并

对于两棵线段树都有的节点，新的线段树的该节点值为两者和。

对于某一棵线段树有的节点，新的线段树保存该节点的值。

*/
struct SegmentTree {
    int lc, rc;
    int maxn, id;
}T[MAXN * 80];
int root[MAXN];
void push_up(int rt) {
    if (T[T[rt].lc].maxn >= T[T[rt].rc].maxn) {
        T[rt].maxn = T[T[rt].lc].maxn;
        T[rt].id = T[T[rt].lc].id;
    } else {
        T[rt].maxn = T[T[rt].rc].maxn;
        T[rt].id = T[T[rt].rc].id;
    }
}
void update(int &id, int l, int r, int pos, int k) { //动态开点
    if (!id) id = ++cnt;
    if (l == r) {
        T[id].maxn += k;
        T[id].id = l;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(T[id].lc, l, mid, pos, k);
    else update(T[id].rc, mid + 1, r, pos, k);
    push_up(id);
}
int Tree_merge(int x, int y, int l, int r) {
    if (!x) return y;
    if (!y) return x;
    if (l == r) {
        T[x].maxn += T[y].maxn;
        return x;
    }
    int mid = (l + r) >> 1;
    T[x].lc = Tree_merge(T[x].lc, T[y].lc, l, mid);
    T[x].rc = Tree_merge(T[x].rc, T[y].rc, mid + 1, r);
    push_up(x);
    return x;
}

fill(root, root + n + 1, 0);
//在第x棵线段树pos位置加k
update(root[x], 1, MAXVAL, pos, k);
//将第y棵线段树合并到第x棵线段树
Tree_merge(root[x], root[y], 1, MAXVAL);
