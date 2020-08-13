/*
���⣺����һ�� n ����ĵ�Ȩ���������޸ĵ�Ȩ��ѯ����� x�����С�ڵ��� d �ĵ�ĵ�Ȩ��

����ÿ����ά������Ȩֵ�߶������ֱ�ά���Ըõ�Ϊ���ĵķ���
���е������ľ����Ȩֵ���Լ��������ĵ�������׾����Ȩ
ֵ��

��ͳ�� x �ڵ��ʱ��ֻҪͳ���䵽���������������ÿ�����ĵ�
����ֵ�ۼӼ���

�������Ȳ�����logn
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2e5 + 10;
const int MAXM = 2e5 + 10;
const int INF = 1e9;
const int DEG = 20;
struct edge {
    int u,v;
    int next;
}e[MAXM * 2];
int first[MAXN];
int idx;
int n;
void add(int a, int b) {
    e[idx].u = a;
    e[idx].v = b;
    e[idx].next = first[a];
    first[a] = idx++;
}
void init() { //��ʼ���޸�
    fill(first, first + n + 1, -1);
    idx = 0;
}
namespace LCA {
    int seq[MAXN * 2];//��¼ŷ�����Ӧ�ĵ�ı��
    int dep[MAXN * 2];//��¼ŷ��������
    int pos[MAXN];//��¼�ڵ���ŷ�����е�һ�γ��ֵ�λ�ñ��
    int cnt;//ŷ����
    int n;//�ڵ�����
    int f[MAXN * 2][DEG];//ST��
    int logn[MAXN * 2];

    void st_init() {//Ԥ����log����ֹ��ѯʱӰ���ٶ�
        logn[1] = 0;
        logn[2] = 1;
        for (int i = 3; i < MAXN * 2; i++) {
            logn[i] = logn[i / 2] + 1;
        }
    }

    void init(int _n) {
        n = _n;
        cnt = 0;
    }

    void dfs(int u, int fa, int depth) {
        seq[++cnt] = u;
        pos[u] = cnt;
        dep[cnt] = depth;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (v == fa) continue;
            dfs(v, u, depth + 1);
            seq[++cnt] = u;
            dep[cnt] = depth;
        }
    }

    void solve() {//ST����
        for (int i = 1; i <= n * 2; i++) {
            f[i][0] = seq[i];
        }
        for (int j = 1; j < DEG; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n * 2; i++) {
                if (dep[pos[f[i][j - 1]]] < dep[pos[f[i + (1 << (j - 1))][j - 1]]]) {
                    f[i][j] = f[i][j - 1];
                } else {
                    f[i][j] = f[i + (1 << (j - 1))][j - 1];
                }
            }
        }
    }

    int query(int u, int v) {
        int l = min(pos[u], pos[v]);
        int r = max(pos[u], pos[v]);
        int lg = logn[r - l + 1];
        return min(f[l][lg], f[r - (1 << lg) + 1][lg]);
    }

    int get_dis(int u, int v) {
        int lca = query(u, v);
        return dep[pos[u]] + dep[pos[v]] - 2 * dep[pos[lca]];
    }
};
struct BIT {
    vector<ll> c;
    int n;
    int lowbit(int x) {
        return x & (-x);
    }

    void updata(int i, int k) {//��iλ�ü���k
        while (i <= n) {
            c[i] += k;
            i += lowbit(i);
        }
    }

    ll getsum(int i) {//��A[1] + A[2] + ... + A[i]
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
        c.resize(n + 1, 0);
    }
}T1[MAXN], T2[MAXN];
int sz[MAXN], mson[MAXN], vis[MAXN];
int tolsize, root, tol;
int belong[MAXN]; //��������ڵ�
int belongsz[MAXN]; //�����������С
void get_root(int x, int fa) {//����������
    sz[x] = 1; mson[x] = 0;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v] || v == fa) continue;
        get_root(v, x);
        sz[x] += sz[v];
        if (sz[v] > mson[x]) mson[x] = sz[v];
    }
    if (tolsize - sz[x] > mson[x]) mson[x] = tolsize - sz[x];
    if (mson[x] < mson[root]) root = x;
}
void build(int x, int fa) { //���������
    belong[x] = fa; //��¼������Ͻڵ�ĸ��ڵ�
    belongsz[x] = 1;
    vis[x] = 1;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v]) continue;
        tolsize = sz[v];root = 0;
        get_root(v, x);
        int nowroot = root;
        build(root, x);
        belongsz[x] += belongsz[nowroot];
    }
}
void modify(int x, int val) { //��x��Ȩֵ����val������Ӱ��
    int now = x;
    while (now) {
        int fa = belong[now];
        T1[now].change(LCA::get_dis(now, x) + 1, val);
        if (fa) T2[now].change(LCA::get_dis(fa, x) + 1, val);
        now = fa;
    }
}
ll query(int x, int k) { //ͳ����x����벻����k�ĵ�Ȩ��
    ll ans = 0;
    int now = x, last = 0;
    while (now) {
        int d = LCA::get_dis(now, x);
        if (d > k) {
            last = now;
            now = belong[now];
            continue;
        }
        ans += T1[now].query(1, min(k - d + 1, T1[now].n)); //ͳ�Ƹ÷��β�������Ϣ
        if (last) ans -= T2[last].query(1, min(k - d + 1, T2[last].n)); //ɾȥ��ͳ�Ƶ��ӷ��β���Ϣ
        last = now;
        now = belong[now];
    }
    return ans;
}
int main() {
    LCA::st_init(); //st��ʼ��
    int m;
    scanf("%d%d", &n, &m);
    init();
    vector<ll> val(n + 1);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &val[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    LCA::init(n);
    LCA::dfs(1, 0, 0);
    LCA::solve();
    fill(vis, vis + n + 1, 0);
    tolsize = n; root = 0;
    mson[0] = INF; //int INF
    get_root(1, 0); //�õ�����
    build(root, 0); //���������
    for (int i = 1; i <= n; i++) { //��״�����ʼ��
        T1[i].init(belongsz[i] * 2); //����ռ乻����������Щ
        T2[i].init(belongsz[i] * 2);
    }
    for (int i = 1; i <= n; i++) {
        modify(i, val[i]);
    }
    int lastans = 0;
    for (int i = 1; i <= m; i++) {
        int op,x,y;
        scanf("%d%d%d", &op, &x, &y);
        x = x ^ lastans;
        y = y ^ lastans;
        if (op == 0) {
            lastans = query(x, y);
            printf("%d\n", lastans);
        } else {
            modify(x, y - val[x]); //��x��Ȩֵ��Ϊy
            val[x] = y;
        }
    }
    return 0;
}
