namespace Treap {
    struct node {
        int ch[2];
        ll val; //权值
        int sz; //子树大小
        int rnd;
        int tag; //标记,以区间翻转为例
    }Tree[MAXN];

    int cnt;
    int root, x, y, z;
    void init() {
        srand((unsigned)time(NULL));
        for (int i = 1; i <= cnt; i++) {
            Tree[i].sz = Tree[i].ch[0] = Tree[i].ch[1] = 0;
        }
        cnt = 0;
        root = 0;
    }
    int new_node(ll val) {
        ++cnt;
        Tree[cnt].sz = 1;
        Tree[cnt].val = val;
        Tree[cnt].rnd = rand();
        Tree[cnt].tag = 0;
        return cnt;
    }

    void update(int x) {
        int l = Tree[x].ch[0];
        int r = Tree[x].ch[1];
        Tree[x].sz = 1 + Tree[l].sz + Tree[r].sz;
    }

    void pushtag(int now) { //区间翻转为例
        swap(Tree[now].ch[0], Tree[now].ch[1]);
        int l = Tree[now].ch[0];
        int r = Tree[now].ch[1];
        if (l) {
            Tree[l].tag ^= 1;
        }
        if (r) {
            Tree[r].tag ^= 1;
        }
        Tree[now].tag = 0;
    }

    //split函数根据题目需要添加，按哪些东西分裂
    void split_val(int now, ll k, int &x, int &y) {//将以now为根的树按照权值(k)分为以l为根的树和以r为根的树。
        if (!now) {
            x = y = 0;
            return;
        }
        if (Tree[now].tag)
            pushtag(now);
        if (Tree[now].val <= k) {
            x = now;
            split_val(Tree[now].ch[1], k, Tree[now].ch[1], y);
        } else {
            y = now;
            split_val(Tree[now].ch[0], k, x, Tree[now].ch[0]);
        }
        update(now);
    }

    void split_sz(int now, int k, int &x, int &y) {//将以now为根的树按照子树大小(k)分为以l为根的树和以r为根的树。
        if (!now) {
            x = y = 0;
            return;
        }
        if (Tree[now].tag)
            pushtag(now);
        if (Tree[Tree[now].ch[0]].sz < k) {
            x = now;
            split_sz(Tree[now].ch[1], k - Tree[Tree[now].ch[0]].sz - 1, Tree[now].ch[1], y);
        } else {
            y = now;
            split_sz(Tree[now].ch[0], k, x, Tree[now].ch[0]);
        }
        update(now);
    }

    int merge(int x, int y) {//把以l为根的树和以r为根的树合并
        if(!x || !y)
            return x + y;
        if (Tree[x].rnd < Tree[y].rnd) {
            if (Tree[x].tag)
                pushtag(x);
            Tree[x].ch[1] = merge(Tree[x].ch[1], y);
            update(x);
            return x;
        } else {
            if (Tree[y].tag)
                pushtag(y);
            Tree[y].ch[0] = merge(x, Tree[y].ch[0]);
            update(y);
            return y;
        }
    }

    void insert(ll val) { //插入节点
        split_val(root, val, x, y);
        root = merge(merge(x, new_node(val)), y);
    }

    void del(ll val) { //删除节点
        split_val(root, val, x, z);
        split_val(x, val - 1, x, y);
        y = merge(Tree[y].ch[0], Tree[y].ch[1]);
        root = merge(merge(x, y), z);
    }

    int stk[MAXN];
    int build(ll * a, int n) {
        int top = 0;
        for (int i = 1; i <= n; i++) {
            int tmp = new_node(a[i]), last = 0;
            while (top && Tree[stk[top]].rnd > Tree[tmp].rnd) {
                last = stk[top];
                update(last);
                stk[top--] = 0;
            }
            if (top) {
                Tree[stk[top]].ch[1] = tmp;
            }
            Tree[tmp].ch[0] = last;
            stk[++top] = tmp;
        }
        while (top) {
            update(stk[top--]);
        }
        return stk[1];
    }

    int get_rank(ll val) { //查询排名
        split_val(root, val - 1, x, y);
        int res = Tree[x].sz - 1;
        root = merge(x, y);
        return res;
    }

    ll get_kth(int now, int k) { //查询now的子树中排名为k的数
        while (1) {
            int l = Tree[now].ch[0];
            int r = Tree[now].ch[1];
            if (k <= Tree[l].sz) {
                now = l;
            } else if (k == Tree[l].sz + 1) {
                return Tree[now].val;
            } else {
                k -= Tree[l].sz + 1;
                now = r;
            }
        }
    }

    ll get_pre(ll val) { //查询前驱
        split_val(root, val - 1, x, y);
        ll res = get_kth(x, Tree[x].sz);
        root = merge(x, y);
        return res;
    }

    ll get_next(ll val) { //查询后继
        split_val(root, val, x, y);
        ll res = get_kth(y, 1);
        root = merge(x, y);
        return res;
    }

    void print(vector<ll> &res, int now) { //中序遍历得到数组
        if (!now) return;
        if (Tree[now].tag)
            pushtag(now);
        print(res, Tree[now].ch[0]);
        res.push_back(Tree[now].val);
        print(res, Tree[now].ch[1]);
    }

    void solve(int l, int r) { //区间操作
        split_sz(root, l - 1, x, y);
        split_sz(y, r - l + 1, y, z);
        Tree[y].tag ^= 1;//区间操作，以翻转为例
        root = merge(x, merge(y, z));
    }

    ll get_sum(int l, int r) {
        split_sz(root, l - 1, x, y);
        split_sz(y, r - l + 1, y, z);
        ll res = Tree[y].sum;
        root = merge(x, merge(y, z));
        return res;
    }
}
//初始化
Treap::init();
//建树(线性)
int a[MAXN];
Treap::root = Treap::build(a, n);
//插入
Treap::insert(val);
//删除
Treap::del(val);
//排名
ans = Treap::get_rank(val);
//第k个数
ans = Treap::get_kth(Treap::root, k);
//前驱
ans = Treap::get_pre(val);
//后继
ans = Treap::get_next(val);
//打印输出数列
vector<ll> res;
Treap::print(res, Treap::root);
cout<<res;
//区间（翻转）操作
Treap::solve(l, r);
//区间（求和）操作
ans = Treap::get_sum(l, r);
