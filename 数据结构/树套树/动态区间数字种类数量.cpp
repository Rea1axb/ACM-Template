/*
nxt[i]:下个 color[i] 出现的位置，如果之后没有 color[i] 则设为 n + 1
[l, r]区间的颜色数量就可以用[l, r]区间内 nxt[i] 大于等于 r + 1 的数量来表示
*/
struct Tree {
    int l, r;
    ll sum;
}T[MAXN * 80]; //空间够的话往大开，1e7级别
int root[MAXN * 80], tol;
int len;//权值上界
void init(int up) {
    len = up;
    tol = 0;
    T[tol].l = T[tol].r = T[tol].sum = 0;
    root[tol] = 0;
}
void update(int l, int r, int &now, int pos, int val) {
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

    int query(int l, int r, int k) { // 大于等于k的数量
        int ans = 0;
        if (l == k) {
            for (int i = 1; i <= cnt1; i++)
                ans -= T[rt1[i]].sum;
            for (int i = 1; i <= cnt2; i++) {
                ans += T[rt2[i]].sum;
            }
            return ans;
        }
        int mid = (l + r) >> 1;
        if (k > mid) {
            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].r;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].r;
            return query(mid + 1, r, k);
        } else {
            for (int i = 1; i <= cnt1; i++)
                ans -= T[T[rt1[i]].r].sum;
            for (int i = 1; i <= cnt2; i++)
                ans += T[T[rt2[i]].r].sum;
            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].l;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].l;
            return ans + query(l, mid, k);
        }
    }

    void change(int x, int k) {
        updata(x, abs(k), (k > 0 ? 1 : -1));
    }

    ll ask(int l, int r, int k) {
        locate(l, r);
        return query(1, len, k);
    }

    void init(int _n) {
        n = _n;
    }
}
set<int> colorpos[MAXM]; //颜色的位置
int nxt[MAXN], last[MAXN]; //链表

//初始化
init(up + 5); //因为存的是nxt，所以up=n+1
BIT::init(n);
for (int i = n; i >= 1; i--) {
    if (colorpos[color[i]].empty()) {
        nxt[i] = n + 1;
        last[i] = 0;
    } else {
        auto it = colorpos[color[i]].begin();
        nxt[i] = *it;
        last[i] = 0;
        last[*it] = i;
    }
    colorpos[color[i]].insert(i);
    BIT::change(i, nxt[i]);
}

//将color[x]修改为y
if (color[x] == y) continue;
int nxtpos = nxt[x];
int lastpos = last[x];
if (nxtpos != n + 1) {
    last[nxtpos] = lastpos;
}
if (lastpos != 0) {
    BIT::change(lastpos, -nxt[lastpos]);
    nxt[lastpos] = nxtpos;
    BIT::change(lastpos, nxt[lastpos]);
}
colorpos[color[x]].erase(x);
BIT::change(x, -nxt[x]);
if (colorpos[y].empty()) {
    last[x] = 0;
    nxt[x] = n + 1;
} else {
    auto it = colorpos[y].lower_bound(x);
    if (it == colorpos[y].end()) {
        auto rb = colorpos[y].rbegin();
        BIT::change(*rb, -nxt[*rb]);
        nxt[*rb] = x;
        BIT::change(*rb, nxt[*rb]);
        last[x] = *rb;
        nxt[x] = n + 1;
    } else {
        last[x] = last[*it];
        nxt[x] = *it;
        last[*it] = x;
        if (last[x] != 0) {
            BIT::change(last[x], -nxt[last[x]]);
            nxt[last[x]] = x;
            BIT::change(last[x], nxt[last[x]]);
        }
    }
}
color[x] = y;
colorpos[y].insert(x);
BIT::change(x, nxt[x]);

//查询区间颜色种类
ans = BIT::ask(l, r, r + 1);
