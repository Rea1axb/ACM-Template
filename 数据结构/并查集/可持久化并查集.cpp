/*
3种操作：
1.合并a,b所在的集合;
2.回到第k次操作之后的状态;
3.询问a,b是否属于同一集合;

用主席树维护节点不同时间的并查集的fa
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10; //节点数量
const int MAXM = 2e5 + 10; //操作次数
namespace PUS {
    struct Tree {
        int l, r;
        int fa;
        int dep;
    }T[MAXM * 40];
    int tol, root[MAXM], n;
    void init(int _n) {
        n = _n;
        tol = 0;
        T[tol].l = T[tol].r = T[tol].fa = T[tol].dep = 0;
        root[tol] = 0;
    }
    void build(int &rt, int l, int r) { //初始建树
        rt = ++tol;
        if (l == r) {
            T[rt].fa = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(T[rt].l, l, mid);
        build(T[rt].r, mid + 1, r);
    }
    void merge(int pre, int &now, int l, int r, int pos, int fa) { //合并
        now = ++tol;
        T[now] = T[pre];
        if (l == r) {
            T[now].fa = fa;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            merge(T[pre].l, T[now].l, l, mid, pos, fa);
        else
            merge(T[pre].r, T[now].r, mid + 1, r, pos, fa);
    }
    void update(int rt, int l, int r, int pos) { //修改节点深度
        if (l == r) {
            T[rt].dep++;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(T[rt].l, l, mid, pos);
        else
            update(T[rt].r, mid + 1, r, pos);
    }
    int query(int rt, int l, int r, int pos) { //查询某个值在主席树中的下标
        if (l == r) return rt;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(T[rt].l, l, mid, pos);
        else
            return query(T[rt].r, mid + 1, r, pos);
    }
    int find(int rt, int pos) { //查找祖先
        int tmp = query(rt, 1, n, pos);
        if (T[tmp].fa == pos) return tmp;
        return find(rt, T[tmp].fa);
    }
}
using namespace PUS;
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    init(n);
    build(root[0], 1, n);
    for (int i = 1; i <= m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            root[i] = root[i - 1];
            int posx = find(root[i], x);
            int posy = find(root[i], y);
            if (T[posx].fa != T[posy].fa) { //按秩合并，把深度小的合并到深度大的
                if (T[posx].dep > T[posy].dep) swap(posx, posy);
                merge(root[i - 1], root[i], 1, n, T[posx].fa, T[posy].fa);
                if (T[posx].dep == T[posy].dep) //若两个点深度相同，要把合并后的根的深度+1
                    update(root[i], 1, n, T[posy].fa);
            }
        } else if (op == 2) {
            int x;
            scanf("%d", &x);
            root[i] = root[x];
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            root[i] = root[i - 1];
            int posx = find(root[i], x);
            int posy = find(root[i], y);
            if (T[posx].fa == T[posy].fa) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
    }
    return 0;
}
