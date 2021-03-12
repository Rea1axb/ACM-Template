/*
LuoGu-P4688
有 m 个询问，每次询问三个区间，
把三个区间中同时出现的数一个一个删掉，
问最后三个区间剩下的数的个数和，询问独立。

用 bitset 存储每一个区间内的出现过的所有权值
一组询问的答案即三个区间的长度和减去三者的并集元素个数*3。

bitset 不能很好地处理同时出现多个权值的情况。
我们可以把当前元素离散化后的权值与当前区间的的出现次数之和作为往 bitset 中插入的对象。

虽然 bitset 用空间小，但是仍然难以承受 1e5*1e5 的数据规模。
所以我们需要将询问划分成常数块分别处理，保证空间刚好足够的情况下时间复杂度不变。
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
const int MAXQ = MAXN / 3; //将询问分成三块
typedef bitset<MAXN> bi;
vector<ll> lisan;

int getid(ll x) {
    return lower_bound(lisan.begin(), lisan.end(), x) - lisan.begin() + 1;
}
int block;
struct query {
    int l, r;
    int id;
    int num;
}q[(MAXQ + 10) * 3]; //每个询问分成对三个区间的小询问
bool cmp_block(query a, query b) {
    if (a.l / block != b.l / block) return a.l < b.l;
    return (a.l / block) & 1 ? a.r < b.r : a.r > b.r;
}
ll a[MAXN];
int cnt[MAXN];
int len[MAXQ + 20]; //询问的区间总长度
bi sum;
bi ans[MAXQ + 20]; //询问的答案
void add(int val) {
    cnt[val]++;
    sum.set(val + cnt[val] - 1);
}
void del(int val) {
    sum.reset(val + cnt[val] - 1);
    cnt[val]--;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        lisan.push_back(a[i]);
    }
    sort(lisan.begin(), lisan.end());
    for (int i = 1; i <= n; i++) {
        a[i] = getid(a[i]);
    }
    int tol;

    //第一块询问
    tol = 0;
    for (int i = 1; i <= n; i++) {
        cnt[a[i]] = 0;
    }
    for (int i = 1; i <= min(MAXQ, m); i++) {
        len[i] = 0;
        for (int j = 1; j <= 3; j++) {
            ++tol;
            int l, r;
            scanf("%d%d", &l, &r);
            q[tol].l = l;
            q[tol].r = r;
            q[tol].id = tol;
            q[tol].num = i;
            len[i] += r - l + 1;
        }
        ans[i].set();
    }
    block = sqrt(n);
    sort(q + 1, q + tol + 1, cmp_block);
    sum.reset();
    for (int i = 1, l = 1, r = 0; i <= tol; i++) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].num] &= sum;
    }
    for (int i = 1; i <= min(MAXQ, m); i++) {
        printf("%d\n", len[i] - ans[i].count() * 3);
    }

    //第二块询问
    tol = 0;
    for (int i = 1; i <= n; i++) {
        cnt[a[i]] = 0;
    }
    for (int i = MAXQ + 1; i <= min(2 * MAXQ, m); i++) {
        len[i - MAXQ] = 0;
        for (int j = 1; j <= 3; j++) {
            ++tol;
            int l, r;
            scanf("%d%d", &l, &r);
            q[tol].l = l;
            q[tol].r = r;
            q[tol].id = tol;
            q[tol].num = i - MAXQ;
            len[i - MAXQ] += r - l + 1;
        }
        ans[i - MAXQ].set();
    }
    block = sqrt(n);
    sort(q + 1, q + tol + 1, cmp_block);
    sum.reset();
    for (int i = 1, l = 1, r = 0; i <= tol; i++) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].num] &= sum;
    }
    for (int i = MAXQ + 1; i <= min(MAXQ * 2, m); i++) {
        printf("%d\n", len[i - MAXQ] - ans[i - MAXQ].count() * 3);
    }

    //第三块询问
    tol = 0;
    for (int i = 1; i <= n; i++) {
        cnt[a[i]] = 0;
    }
    for (int i = MAXQ * 2 + 1; i <= min(MAXQ * 3, m); i++) {
        len[i - MAXQ * 2] = 0;
        for (int j = 1; j <= 3; j++) {
            ++tol;
            int l, r;
            scanf("%d%d", &l, &r);
            q[tol].l = l;
            q[tol].r = r;
            q[tol].id = tol;
            q[tol].num = i - MAXQ * 2;
            len[i - MAXQ * 2] += r - l + 1;
        }
        ans[i - MAXQ * 2].set();
    }
    block = sqrt(n);
    sort(q + 1, q + tol + 1, cmp_block);
    sum.reset();
    for (int i = 1, l = 1, r = 0; i <= tol; i++) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);
        ans[q[i].num] &= sum;
    }
    for (int i = MAXQ * 2 + 1; i <= min(MAXQ * 3, m); i++) {
        printf("%d\n", len[i - MAXQ * 2] - ans[i - MAXQ * 2].count() * 3);
    }
    return 0;
}

/*
LuoGu-P5355
四种区间查询：
 1.是否存在两个数差为x；
 2.是否存在两个数和为x；
 3.是否存在两个数乘积是x；
 4.是否存在两个数商是x；（无余数）

1.sum[a]==1&&sum[a+x]==1,只需判断sum&(sum<<x)
2.记b'为reverse(b)，即b'=MAXN-1-b,sum[a]==1&&rsum[a+MAXN-1-b]=1,
 只需判断rsum&(sum<<(MAXN-1-b))
3.直接枚举x的因数
4.对于x>sqrt(N)的询问，令i从1遍历到N/x，查询i和i*x是否同时存在
  对于x<sqrt(N)的询问，
  last[val]:上次val出现的位置
  le[pos]:满足在[le[pos], pos]同时出现a和a*x或同时出现a和a/y的最靠右的位置
  每扫到一个点，用val更新last[val]，用last[val*x]和last[val/x]来更新le[pos]
  对于x为当前x的所有询问，只要判断q.l是否小于等于le[q.r]
*/
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1e5 + 10;
const int MAXQ = 1e5 + 10;
typedef bitset<MAXN> bi;
int block;
struct query {
    int l, r;
    int id;
    int op;
    int x;
    int ans;
}q[MAXQ];
bool cmp_block(query a, query b) {
    if (a.l / block != b.l / block) return a.l < b.l;
    return (a.l / block) & 1 ? a.r < b.r : a.r > b.r;
}
bool cmp_id(query a, query b) {
    return a.id < b.id;
}
bool cmp_x(query a, query b) {
    return a.x < b.x;
}
int last[MAXN], le[MAXN];

bi sum;
bi rsum;
int color[MAXN];
int cnt[MAXN];
void add(int val) {
    cnt[val]++;
    if (cnt[val] == 1) {
        sum.set(val);
        rsum.set(MAXN - 1 - val);
    }
}
void del(int val) {
    if (cnt[val] == 1) {
        sum.reset(val);
        rsum.reset(MAXN - 1 - val);
    }
    cnt[val]--;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }
    block = sqrt(n);
    int limit = sqrt(MAXN);
    vector<query> vec;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &q[i].op, &q[i].l, &q[i].r, &q[i].x);
        q[i].id = i;
        if (q[i].op == 4 && q[i].x <= limit) {
            vec.push_back(q[i]);
        }
    }
    sort(vec.begin(), vec.end(), cmp_x);
    int now = -1;
    for (auto o : vec) {
        if (o.x != now) {
            now = o.x;
            memset(last, -1, sizeof(last));
            memset(le, -1, sizeof(le));
            for (int i = 1; i <= n; i++) {
                last[color[i]] = i;
                le[i] = le[i - 1];
                if (color[i] * now < MAXN && last[color[i] * now] != -1) {
                    le[i] = max(le[i], last[color[i] * now]);
                }
                if (now != 0 && color[i] % now == 0 && last[color[i] / now] != -1) {
                    le[i] = max(le[i], last[color[i] / now]);
                }
            }
        }
        if (le[o.r] != -1 && le[o.r] >= o.l) {
            q[o.id].ans = 1;
        } else {
            q[o.id].ans = 0;
        }
    }
    sort(q + 1, q + m + 1, cmp_block);
    sum.reset(), rsum.reset();
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        if (q[i].op == 4 && q[i].x <= limit) continue;
        while (l > q[i].l) add(color[--l]);
        while (r < q[i].r) add(color[++r]);
        while (l < q[i].l) del(color[l++]);
        while (r > q[i].r) del(color[r--]);
        if (q[i].op == 1) {
            if ((sum & (sum << q[i].x)).any()) {
                q[i].ans = 1;
            } else {
                q[i].ans = 0;
            }
        } else if (q[i].op == 2) {
            if ((rsum & (sum << (MAXN - 1 - q[i].x))).any()) {
                q[i].ans = 1;
            } else {
                q[i].ans = 0;
            }
        } else if (q[i].op == 3) {
            for (ll j = 1; j * j <= q[i].x; j++) {
                if (q[i].x % j == 0) {
                    if (sum.test(j) && sum.test(q[i].x / j)) {
                        q[i].ans = 1;
                        break;
                    }
                }
            }
        } else {
            for (ll j = 1; j * q[i].x < MAXN; j++) {
                if (sum.test(j) && sum.test(j * q[i].x)) {
                    q[i].ans = 1;
                    break;
                }
            }
        }
    }

    sort(q + 1, q + m + 1, cmp_id);
    for (int i = 1; i <= m; i++) {
        if (q[i].ans) {
            printf("yuno\n");
        } else {
            printf("yumi\n");
        }
    }
    return 0;
}
