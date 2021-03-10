/*
LuoGu_P1903
Q L R：询问区间内颜色数
R C X：修改C位置的值为X

带修莫队相当于增加了一维t，表示当前的修改次数
分块大小：n^(2/3)
时间复杂度：O(n^(5/3))
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 2e5 + 10;
const int MAXNUM = 1e6 + 10;
const int MAXQ = 2e5 + 10;
int block;
struct query {
    int l, r;
    int id;
    int ans;
    int updatenum; //这次询问之前的修改次数
}q[MAXQ];
struct update {
    int pos;
    int val1; //修改前的值
    int val2; //修改后的值
}u[MAXQ];
bool cmp_block(query a, query b) { //分块排序
    if (a.l / block != b.l / block) return a.l < b.l;
    if (a.r / block != b.r / block) return a.l / block & 1 ? a.r < b.r : a.r > b.r;
    return a.r / block & 1 ? a.id < b.id : a.id > b.id;
}
bool cmp_id(query a, query b) {
    return a.id < b.id;
}
int color[MAXN], nowcolor[MAXN], cnt[MAXNUM];
int sum;
void add(int val) {
    cnt[val]++;
    if (cnt[val] == 1) sum++;
}
void del(int val) {
    cnt[val]--;
    if (cnt[val] == 0) sum--;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
        nowcolor[i] = color[i]; //nowcolor主要用于记录修改的时候的当前值
    }
    int querycnt = 0, updatecnt = 0;
    for (int i = 1; i <= m; i++) {
        char s[5];
        scanf("%s", s);
        if (s[0] == 'Q') {
            ++querycnt;
            scanf("%d%d", &q[querycnt].l, &q[querycnt].r);
            q[querycnt].id = querycnt;
            q[querycnt].updatenum = updatecnt;
        } else {
            ++updatecnt;
            scanf("%d%d", &u[updatecnt].pos, &u[updatecnt].val2);
            u[updatecnt].val1 = nowcolor[u[updatecnt].pos];
            nowcolor[u[updatecnt].pos] = u[updatecnt].val2;
        }
    }
    block = pow(n, 2.0/3.0);
    sort(q + 1, q + querycnt + 1, cmp_block);
    sum = 0;
    for (int i = 1, l = 1, r = 0, t = 0; i <= querycnt; i++) {
        while (l > q[i].l) add(color[--l]);
        while (r < q[i].r) add(color[++r]);
        while (l < q[i].l) del(color[l++]);
        while (r > q[i].r) del(color[r--]);
        while (t < q[i].updatenum) {
            ++t;
            if (l <= u[t].pos && u[t].pos <= r) {
                del(u[t].val1);
                add(u[t].val2);
            }
            color[u[t].pos] = u[t].val2;
        }
        while (t > q[i].updatenum) {
            if (l <= u[t].pos && u[t].pos <= r) {
                del(u[t].val2);
                add(u[t].val1);
            }
            color[u[t].pos] = u[t].val1;
            t--;
        }
        q[i].ans = sum;
    }
    sort(q + 1, q + querycnt + 1, cmp_id);
    for (int i = 1; i <= querycnt; i++) {
        printf("%d\n", q[i].ans);
    }
    return 0;
}
