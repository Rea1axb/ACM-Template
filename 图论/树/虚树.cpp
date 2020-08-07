/*
称某次询问中被选中有关的点称为关键点
虚树就是对关键点有关的点建树，减少花在无用点上的时间
总的就是对O(k)个点进行操作，k为关键点数量
*/
namespace LCA {
    int fa[MAXN][DEG];
    int deg[MAXN];

    void bfs(int root) {
        queue<int> q;
        deg[root] = 0;
        fa[root][0] = root;
        q.push(root);
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            for (int i = 1; i < DEG; i++) {
                fa[tmp][i] = fa[fa[tmp][i - 1]][i - 1];
            }
            for (int i = first[tmp]; i != -1; i = e[i].next) {
                int v = e[i].v;
                if (v == fa[tmp][0]) continue;
                deg[v] = deg[tmp] + 1;
                fa[v][0] = tmp;
                q.push(v);
            }
        }
    }

    int query(int u, int v) {
        if (deg[u] > deg[v]) {
            swap(u, v);
        }
        int hu = deg[u], hv = deg[v];
        int tu = u, tv = v;
        for (int k = hv - hu, i = 0; k; k >>= 1, i++) {
            if (k & 1) {
                tv = fa[tv][i];
            }
        }
        if (tu == tv) {
            return tu;
        }
        for (int i = DEG - 1; i >= 0; i--) {
            if (fa[tu][i] == fa[tv][i]) {
                continue;
            }
            tu = fa[tu][i];
            tv = fa[tv][i];
        }
        return fa[tu][0];
    }
};
namespace VirtualTree {
    // 虚树部分
    // 单向边，父节点指向子节点
    // 抄完板子查找first，idx，e查错
    struct vedge {
        int u, v;
        int next;
    }ve[MAXK * 4];
    int vidx;
    int vfirst[MAXN];
    void vadd(int a, int b) {
        ve[vidx].u = a;
        ve[vidx].v = b;
        ve[vidx].next = vfirst[a];
        vfirst[a] = vidx++;
    }

    int dfn[MAXN], stk[MAXN];
    int dfncnt;
    int k; //关键点数量
    vector<int> keypoint;//关键点
    bool cmp(int a, int b) {
        return dfn[a] < dfn[b];
    }
    void get_dfn(int u, int fa) {
        dfn[u] = ++dfncnt;
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (v == fa) continue;
            get_dfn(v, u);
        }
    }
    void init() {
        dfncnt = 0;
        getdfn(1, 0);
        LCA::bfs(1);
    }

    void build(int _k, vector<int> _keypoint) { //建立虚树
        k = _k;
        keypoint = _keypoint;
        vidx = 0;
        sort(keypoint.begin(), keypoint.end(), cmp);
        int top = 1;
        stk[top] = 1;
        vfirst[1] = -1;
        for (auto key : keypoint) {
            if (key == 1) continue;
            int lca = LCA::query(key, stk[top]);
            if (lca != stk[top]) {
                while (dfn[lca] < dfn[stk[top - 1]]) {
                    vadd(stk[top - 1], stk[top]]);
                    //vadd(stk[top - 1], stk[top], dis[stk[top]]); 有边权的情况
                    top--;
                }
                if (dfn[lca] > dfn[stk[top - 1]]) {
                    vfirst[lca] = -1;
                    vadd(lca, stk[top]);
                    //vadd(lca, stk[top], dis[stk[top]]);
                    stk[top] = lca;
                } else {
                    vadd(lca, stk[top]);
                    //vadd(lca, stk[top], dis[stk[top]]);
                    top--;
                }
            }
            vfirst[key] = -1;
            stk[++top] = key;
        }
        for (int i = 1; i < top; i++) {
            vadd(stk[i], stk[i + 1]);
            //vadd(stk[i], stk[i + 1], dis[stk[i + 1]]);
        }
    }

    int solve() {
        //题目不同，solve求解不同
    }
}
VirtualTree::init();
VirtualTree::build(k, keypoint);
ans = VirtualTree::solve();
