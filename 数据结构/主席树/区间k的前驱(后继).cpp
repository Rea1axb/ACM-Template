struct Tree {
    int l, r;
    ll sum;
}T[MAXN * 40];

int root[MAXN];
int tol;

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

int query(int l, int r, int pre, int now, int k) { //k的后继, >=k的最小值
    if (l == r) { //到达叶子节点
        if (T[now].sum - T[pre].sum > 0) { //如果这个值出现过就返回这个值，没有就返回INF
            return l;
        } else {
            return INF;
        }
    }
    int mid = (l + r) >> 1;
    if (k <= mid) {
        int ans = INF;
        if (k <= l) { //剪枝，k小于l的时候，如果左子树有符合条件的直接进入左子树，不考虑右子树
            if (T[T[now].l].sum - T[T[pre].l].sum > 0) {
                ans = min(ans, query(l, mid, T[pre].l, T[now].l, k));
            } else if (T[T[now].r].sum - T[T[pre].r].sum > 0) {
                ans = min(ans, query(mid + 1, r, T[pre].r, T[now].r, k));
            }
            return ans;
        }
        //k在l到mid之间的时候，左右子树都有可能涉及，左右都找一遍寻找最优解
        if (T[T[now].l].sum - T[T[pre].l].sum > 0) {
            ans = min(ans, query(l, mid, T[pre].l, T[now].l, k));
        }
        if (T[T[now].r].sum - T[T[pre].r].sum > 0) {
            ans = min(ans, query(mid + 1, r, T[pre].r, T[now].r, k));
        }
        return ans;
    } else { //k大于mid的时候直接进入右子树，不用考虑左子树
        int ans = INF;
        if (T[T[now].r].sum - T[T[pre].r].sum > 0) {
            ans = min(ans, query(mid + 1, r, T[pre].r, T[now].r, k));
        }
        return ans;
    }
}
//int query(int l, int r, int pre, int now, int k) { //k的前驱, <=k的最大值
//    if (l == r) {
//        if (T[now].sum - T[pre].sum > 0) {
//            return l;
//        } else {
//            return -INF;
//        }
//    }
//    int mid = (l + r) >> 1;
//    if (k > mid) {
//        int ans = -INF;
//        if (k >= r) {
//            if (T[T[now].r].sum - T[T[pre].r].sum > 0) {
//                ans = max(ans, query(mid + 1, r, T[pre].r, T[now].r, k));
//            } else if (T[T[now].l].sum - T[T[pre].l].sum > 0) {
//                ans = max(ans, query(l, mid, T[pre].l, T[now].l, k));
//            }
//            return ans;
//        }
//        if (T[T[now].r].sum - T[T[pre].r].sum > 0) {
//            ans = max(ans, query(mid + 1, r, T[pre].r, T[now].r, k));
//        }
//        if (T[T[now].l].sum - T[T[pre].l].sum > 0) {
//            ans = max(ans, query(l, mid, T[pre].l, T[now].l, k));
//        }
//        return ans;
//    } else {
//        int ans = -INF;
//        if (T[T[now].l].sum - T[T[pre].l].sum > 0) {
//            ans = max(ans, query(l, mid, T[pre].l, T[now].l, k));
//        }
//        return ans;
//    }
//}

int ask(int l, int r, int k) {
    return query(1, n, root[l - 1], root[r], k);
}
