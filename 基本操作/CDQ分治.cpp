/*
三维偏序问题
先按每个元素的属性a排序，然后第二维用归并排序，第三维用树状数组
在归并的时候考虑[l,mid]对[mid+1,r]的贡献。因为我们已经按属性 a 排过序了，
所以在排序属性 b 的时候，无论属性 a 怎么被打乱，
[mid+1,r] 所有元素的属性 a 一定不小于 [l,mid] 中所有元素的属性 a，
所以第二维是成立的。在满足前两维都是有序的时候，
类似二维偏序的解法，我们可以用树状数组来统计答案了。
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
const int MAXVAL = 2e5 + 10;
int n, k;
struct node {
    int a, b, c;
    int w;
    ll val;
}p[MAXN], tmp[MAXN];
int ans[MAXVAL];
namespace BIT {
    ll c[MAXVAL];
    int n;
    int lowbit(int x) {
        return x & (-x);
    }

    void updata(int i, int k) {
        while (i <= n) {
            c[i] += k;
            i += lowbit(i);
        }
    }

    ll getsum(int i) {
        ll res = 0;
        while (i > 0) {
            res += c[i];
            i -= lowbit(i);
        }
        return res;
    }

    void change(int x, int k) {
        updata(x, k);
    }

    ll query(int l, int r) {
        return getsum(r) - getsum(l - 1);
    }

    void init(int _n) {
        n = _n;
        fill(c, c + n + 1, 0);
    }
};
void CDQ(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    CDQ(l, mid); //递归顺序不同题目顺序不同
    CDQ(mid + 1, r);
    int p1 = l, p2 = mid + 1, tol = l;
    while (p1 <= mid && p2 <= r) {
        if (p[p1].b <= p[p2].b) {
            BIT::change(p[p1].c, p[p1].w);
            tmp[tol++] = p[p1++];
        } else {
            p[p2].val += BIT::query(1, p[p2].c);
            tmp[tol++] = p[p2++];
        }
    }
    while (p1 <= mid) {
        BIT::change(p[p1].c, p[p1].w);
        tmp[tol++] = p[p1++];
    }
    while (p2 <= r) {
        p[p2].val += BIT::query(1, p[p2].c);
        tmp[tol++] = p[p2++];
    }
    for (int i = l; i <= mid; i++) {
        BIT::change(p[i].c, -p[i].w);
    }
    for (int i = l; i <= r; i++) {
        p[i] = tmp[i];
    }
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
        p[i].w = 1;
    }
    BIT::init(k);
    sort(p + 1, p + n + 1,
         [] (node x, node y) {
             if (x.a != y.a) return x.a < y.a;
             if (x.b != y.b) return x.b < y.b;
             return x.c < y.c;
         });
    int cnt = 1;
    for (int i = 2; i <= n; i++) {
        if (p[i].a == p[cnt].a && p[i].b == p[cnt].b && p[i].c == p[cnt].c) { //重复元素对答案的影响
            p[cnt].w++;
        } else {
            p[++cnt] = p[i];
        }
    }
    CDQ(1, cnt);
    for (int i = 1; i <= cnt; i++) {
        ans[p[i].val + p[i].w - 1] += p[i].w;
    }
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }
    return 0;
}
