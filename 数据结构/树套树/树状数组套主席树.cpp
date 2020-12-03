struct Tree {
    int l, r;
    ll sum;
}T[MAXN * 80];
int root[MAXN * 80], tol;
int len;//权值上界
void init(int up) {
    len = up;
    tol = 0;
    T[tol].l = T[tol].r = T[tol].sum = 0;
    root[tol] = 0;
}
void update(int l, int r, int &now, int pos, int val) { //主席树功能不同，修改方式不同
    if (!now) {
        now = ++tol;
    }
    T[now].sum += val;
    if (l == r) {
        return;
    }
    int mid = (l + r) >> 1;
    if (mid >= pos)
        update(l, mid, T[now].l, pos, val);
    else
        update(mid + 1, r, T[now].r, pos, val);
}
namespace BIT {
    int n;
    int rt1[MAXN], rt2[MAXN], cnt1, cnt2;

    int lowbit(int x) {
        return x & (-x);
    }

    void updata(int i, int pos, int val) {
        while (i <= n) {
            update(1, len, root[i], pos, val);
            i += lowbit(i);
        }
    }

    void locate(int l, int r) { //找出[l,r]区间相关的点的root
        cnt1 = cnt2 = 0;
        for (int i = l - 1; i; i -= lowbit(i))
            rt1[++cnt1] = root[i];
        for (int i = r; i; i -= lowbit(i))
            rt2[++cnt2] = root[i];
    }

    ll ask(int l, int r, int k) { //主席树功能不同，查询方式不同
        ll ans = 0;
        if (r == k) {
            for (int i = 1; i <= cnt1; i++)
                ans -= T[rt1[i]].sum;
            for (int i = 1; i <= cnt2; i++)
                ans += T[rt2[i]].sum;
            return ans;
        }
        int mid = (l + r) >> 1;
        if (k <= mid) {
            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].l;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].l;
            return ask(l, mid, k);
        } else {
            for (int i = 1; i <= cnt1; i++)
                ans -= T[T[rt1[i]].l].sum;
            for (int i = 1; i <= cnt2; i++)
                ans += T[T[rt2[i]].l].sum;

            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].r;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].r;
            return ans + ask(mid + 1, r, k);
        }
    }

    void change(int x, int k) {
        updata(x, abs(k), k);
    }

    ll query(int l, int r, int k) {
        locate(l, r);
        return ask(1, len, k);
    }

    void init(int _n) {
        n = _n;
    }
}

init(up);
BIT::init(n);
BIT::change(i, a[i]);

//将a[i]修改为val
BIT::change(i, -a[i]);
a[i] = val;
BIT::change(i, a[i]);

//查询区间内小于等于k的数值和
ans = BIT::query(l, r, k);
