/*
修改时间复杂度：O(log^2(n))
查询时间复杂度：O(log^2(n))
*/

//版本1
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

    ll query(int l, int r, int k) { //主席树功能不同，查询方式不同
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
            return query(l, mid, k);
        } else {
            for (int i = 1; i <= cnt1; i++)
                ans -= T[T[rt1[i]].l].sum;
            for (int i = 1; i <= cnt2; i++)
                ans += T[T[rt2[i]].l].sum;

            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].r;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].r;
            return ans + query(mid + 1, r, k);
        }
    }

    void change(int x, int k) {
        updata(x, abs(k), k);
    }

    ll ask(int l, int r, int k) {
        locate(l, r);
        return query(1, len, k);
    }

    void init(int _n) {
        n = _n;
    }
}

init(up + 5);
BIT::init(n);
BIT::change(i, a[i]);

//将a[i]修改为val
BIT::change(i, -a[i]);
a[i] = val;
BIT::change(i, a[i]);

//查询区间内小于等于k的数值和
ans = BIT::ask(l, r, k);


//版本2
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
ll query(int now, int l, int r, int L, int R) {
    if (!now) return 0;
    if (L <= l && r <= R) return T[now].sum;
    ll ans = 0;
    int mid = (l + r) >> 1;
    if (L <= mid) ans += query(T[now].l, l, mid, L, R);
    if (R > mid) ans += query(T[now].r, mid + 1, r, L, R);
    return ans;
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

    ll query_BIT(int l, int r, int L, int R) {
        ll ans = 0;
        for (int i = r; i; i -= lowbit(i))
            ans += query(root[i], 1, len, L, R);
        for (int i = l - 1; i; i -= lowbit(i))
            ans -= query(root[i], 1, len, L, R);
        return ans;
    }

    void change(int x, int k) {
        updata(x, abs(k), k);
    }

    ll ask(int l, int r, int k) {
        return query_BIT(l, r, 1, k);
    }

    void init(int _n) {
        n = _n;
    }
}

init(up + 5);
BIT::init(n);
BIT::change(i, a[i]);

//将a[i]修改为val
BIT::change(i, -a[i]);
a[i] = val;
BIT::change(i, a[i]);

//查询区间内小于等于k的数值和
ans = BIT::ask(l, r, k);

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
const int MAXN = 1e5 + 10;
vector<ll> lisan;
int getid(ll x) {
    return lower_bound(lisan.begin(), lisan.end(), x) - lisan.begin() + 1;
}
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
    ll query1(int l, int r, int k) { //区间小于等于k的数量
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
            return query1(l, mid, k);
        } else {
            for (int i = 1; i <= cnt1; i++)
                ans -= T[T[rt1[i]].l].sum;
            for (int i = 1; i <= cnt2; i++)
                ans += T[T[rt2[i]].l].sum;
            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].r;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].r;
            return ans + query1(mid + 1, r, k);
        }

    }
    ll query2(int l, int r, int k) { //区间第k小
        if (l == r) return l;
        int mid = (l + r) >> 1;
        ll ans = 0;
        for (int i = 1; i <= cnt1; i++)
            ans -= T[T[rt1[i]].l].sum;
        for (int i = 1; i <= cnt2; i++)
            ans += T[T[rt2[i]].l].sum;
        if (ans >= k) {
            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].l;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].l;
            return query2(l, mid, k);
        } else {
            for (int i = 1; i <= cnt1; i++)
                rt1[i] = T[rt1[i]].r;
            for (int i = 1; i <= cnt2; i++)
                rt2[i] = T[rt2[i]].r;
            return query2(mid + 1, r, k - ans);
        }
    }
    ll query3(int l, int r, int k) { //区间小于等于k的最大值，不存在返回INT_MIN
        if (l == r) {
            ll res = 0;
            for (int i = 1; i <= cnt1; i++)
                res -= T[rt1[i]].sum;
            for (int i = 1; i <= cnt2; i++)
                res += T[rt2[i]].sum;
            if (res > 0) return l;
            return INT_MIN;
        }
        int mid = (l + r) >> 1;
        if (k > mid) {
            ll ans = INT_MIN;
            ll resl = 0, resr = 0;
            for (int i = 1; i <= cnt1; i++) {
                resl -= T[T[rt1[i]].l].sum;
                resr -= T[T[rt1[i]].r].sum;
            }
            for (int i = 1; i <= cnt2; i++) {
                resl += T[T[rt2[i]].l].sum;
                resr += T[T[rt2[i]].r].sum;
            }
            if (k >= r) {
                if (resr > 0) {
                    for (int i = 1; i <= cnt1; i++) {
                        rt1[i] = T[rt1[i]].r;
                    }
                    for (int i = 1; i <= cnt2; i++) {
                        rt2[i] = T[rt2[i]].r;
                    }
                    ans = max(ans, query3(mid + 1, r, k));
                } else if (resl > 0) {
                    for (int i = 1; i <= cnt1; i++) {
                        rt1[i] = T[rt1[i]].l;
                    }
                    for (int i = 1; i <= cnt2; i++) {
                        rt2[i] = T[rt2[i]].l;
                    }
                    ans = max(ans, query3(l, mid, k));
                }
                return ans;
            }
            vector<int> tmp1(cnt1 + 1);
            vector<int> tmp2(cnt2 + 1);
            for (int i = 1; i <= cnt1; i++) {
                tmp1[i] = rt1[i];
            }
            for (int i = 1; i <= cnt2; i++) {
                tmp2[i] = rt2[i];
            }
            if (resr > 0) {

                for (int i = 1; i <= cnt1; i++) {
                    rt1[i] = T[tmp1[i]].r;
                }
                for (int i = 1; i <= cnt2; i++) {
                    rt2[i] = T[tmp2[i]].r;
                }
                ans = max(ans, query3(mid + 1, r, k));
            }
            if (resl > 0) {
                for (int i = 1; i <= cnt1; i++) {
                    rt1[i] = T[tmp1[i]].l;
                }
                for (int i = 1; i <= cnt2; i++) {
                    rt2[i] = T[tmp2[i]].l;
                }
                ans = max(ans, query3(l, mid, k));
            }
            return ans;
        } else {
            ll ans = INT_MIN;
            ll resl = 0;
            for (int i = 1; i <= cnt1; i++) {
                resl -= T[T[rt1[i]].l].sum;
            }
            for (int i = 1; i <= cnt2; i++) {
                resl += T[T[rt2[i]].l].sum;
            }
            if (resl > 0) {
                for (int i = 1; i <= cnt1; i++) {
                    rt1[i] = T[rt1[i]].l;
                }
                for (int i = 1; i <= cnt2; i++) {
                    rt2[i] = T[rt2[i]].l;
                }
                ans = max(ans, query3(l, mid, k));
            }
            return ans;
        }
    }
    ll query4(int l, int r, int k) { //区间大于等于k的最小值，不存在返回INT_MAX
        if (l == r) {
            ll res = 0;
            for (int i = 1; i <= cnt1; i++)
                res -= T[rt1[i]].sum;
            for (int i = 1; i <= cnt2; i++)
                res += T[rt2[i]].sum;
            if (res > 0) return l;
            return INT_MAX;
        }
        int mid = (l + r) >> 1;
        if (k <= mid) {
            ll ans = INT_MAX;
            ll resl = 0, resr = 0;
            ll res = 0;
            for (int i = 1; i <= cnt1; i++) {
                res -= T[rt1[i]].sum;
                resl -= T[T[rt1[i]].l].sum;
                resr -= T[T[rt1[i]].r].sum;
            }
            for (int i = 1; i <= cnt2; i++) {
                res += T[rt2[i]].sum;
                resl += T[T[rt2[i]].l].sum;
                resr += T[T[rt2[i]].r].sum;
            }
            if (k <= l) {
                if (resl > 0) {
                    for (int i = 1; i <= cnt1; i++) {
                        rt1[i] = T[rt1[i]].l;
                    }
                    for (int i = 1; i <= cnt2; i++) {
                        rt2[i] = T[rt2[i]].l;
                    }
                    ans = min(ans, query4(l, mid, k));
                } else if (resr > 0) {
                    for (int i = 1; i <= cnt1; i++) {
                        rt1[i] = T[rt1[i]].r;
                    }
                    for (int i = 1; i <= cnt2; i++) {
                        rt2[i] = T[rt2[i]].r;
                    }
                    ans = min(ans, query4(mid + 1, r, k));
                }
                return ans;
            }
            vector<int> tmp1(cnt1 + 1);
            vector<int> tmp2(cnt2 + 1);
            for (int i = 1; i <= cnt1; i++) {
                tmp1[i] = rt1[i];
            }
            for (int i = 1; i <= cnt2; i++) {
                tmp2[i] = rt2[i];
            }
            if (resl > 0) {

                for (int i = 1; i <= cnt1; i++) {
                    rt1[i] = T[tmp1[i]].l;
                }
                for (int i = 1; i <= cnt2; i++) {
                    rt2[i] = T[tmp2[i]].l;
                }
                ans = min(ans, query4(l, mid, k));
            }
            if (resr > 0) {
                for (int i = 1; i <= cnt1; i++) {
                    rt1[i] = T[tmp1[i]].r;
                }
                for (int i = 1; i <= cnt2; i++) {
                    rt2[i] = T[tmp2[i]].r;
                }
                ans = min(ans, query4(mid + 1, r, k));
            }
            return ans;
        } else {
            ll ans = INT_MAX;
            ll resr = 0;
            for (int i = 1; i <= cnt1; i++) {
                resr -= T[T[rt1[i]].r].sum;
            }
            for (int i = 1; i <= cnt2; i++) {
                resr += T[T[rt2[i]].r].sum;
            }
            if (resr > 0) {
                for (int i = 1; i <= cnt1; i++) {
                    rt1[i] = T[rt1[i]].r;
                }
                for (int i = 1; i <= cnt2; i++) {
                    rt2[i] = T[rt2[i]].r;
                }
                ans = min(ans, query4(mid + 1, r, k));
            }
            return ans;
        }
    }

    void change(int x, int pos, int k) {
        updata(x, pos, k);
    }

    ll ask1(int l, int r, int k) { //查询区间k的排名
        locate(l, r);
        return query1(1, len, k - 1) + 1;
    }
    ll ask2(int l, int r, int k) { //查询区间第k小的数
        locate(l, r);
        return query2(1, len, k);
    }
    ll ask3(int l, int r, int k) { //查询区间严格小于k的最大值
        locate(l, r);
        return query3(1, len, k - 1);
    }
    ll ask4(int l, int r, int k) { //查询区间严格大于k的最小值
        locate(l, r);
        return query4(1, len, k + 1);
    }

    void init(int _n) {
        n = _n;
    }
}
struct que {
    int op;
    int x, y, z;
};
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<ll> val(n + 1);
    lisan.clear();
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &val[i]);
        lisan.push_back(val[i]);
    }
    vector<que> q(m + 1);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &q[i].op);
        if (q[i].op == 3) {
            scanf("%d%d", &q[i].x, &q[i].y);
            lisan.push_back(q[i].y);
        } else {
            scanf("%d%d%d", &q[i].x, &q[i].y, &q[i].z);
            if (q[i].op != 2) {
                lisan.push_back(q[i].z);
            }
        }
    }
    sort(lisan.begin(), lisan.end());
    lisan.erase(unique(lisan.begin(), lisan.end()), lisan.end());
    int up = lisan.size() + 1;
    init(up + 5);
    BIT::init(n);
    for (int i = 1; i <= n; i++) {
        BIT::change(i, getid(val[i]), 1);
    }
    for (int i = 1; i <= m; i++) {
        if (q[i].op == 1) { //区间k的排名
            printf("%lld\n", BIT::ask1(q[i].x, q[i].y, getid(q[i].z)));
        } else if (q[i].op == 2) { //区间第k小的数
            printf("%lld\n", lisan[BIT::ask2(q[i].x, q[i].y, q[i].z) - 1]);
        } else if (q[i].op == 3) { //单点修改
            BIT::change(q[i].x, getid(val[q[i].x]), -1);
            val[q[i].x] = q[i].y;
            BIT::change(q[i].x, getid(val[q[i].x]), 1);
        } else if (q[i].op == 4) { //区间k的前驱（严格小于k）
            ll tmp = BIT::ask3(q[i].x, q[i].y, getid(q[i].z));
            if (tmp == INT_MIN) {
                printf("%d\n", 1 + INT_MIN);
            } else {
                printf("%lld\n", lisan[tmp - 1]);
            }

        } else if (q[i].op == 5) { //区间k的后继（严格大于k）
            ll tmp = BIT::ask4(q[i].x, q[i].y, getid(q[i].z));
            if (tmp == INT_MAX) {
                printf("%d\n", INT_MAX);
            } else {
                printf("%lld\n", lisan[tmp - 1]);
            }
        }
    }
    return 0;
}
