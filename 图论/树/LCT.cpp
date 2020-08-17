#pragma GCC optimize(2)
struct LCT {
    struct node {
        int fa, ch[2]; //父亲(Splay对应的链向上由轻边连着哪个节点)、左右儿子
        int reverse;//区间反转标记
        bool  is_root;   //是否是所在Splay的根
        int sz; //节点数量
        ll val; //点权
        ll sum; //路径上点权和

        ll mul; //乘法lazy标记
        ll add; //加法lazy标记

        //ll maxv; //最值
    } Tree[MAXN];
    int n;

    void init(int MN) {
        n = MN;
        for (int i = 1; i <= MN; i++) {
            Tree[i].reverse = Tree[i].fa = Tree[i].ch[0] = Tree[i].ch[1] = 0;
            Tree[i].is_root = true;
            Tree[i].val = 0;
            Tree[i].sz = 1;
            Tree[i].mul = 1;
            Tree[i].add = 0;
        }
    }

    bool getson(int x) {
        //x是否为重儿子
        return x == Tree[Tree[x].fa].ch[1];
    }
    bool isroot(int x) {
        return Tree[Tree[x].fa].ch[0] != x && Tree[Tree[x].fa].ch[1] != x;
    }
    void pushreverse(int x) {
        if (!x)
            return;
        swap(Tree[x].ch[0], Tree[x].ch[1]);
        //swap(Tree[x].lcol, Tree[x].rcol); //有些颜色问题要翻转左右颜色
        Tree[x].reverse ^= 1;
    }
    void pushmul(int x, ll val) { //打乘法lazy标记
        Tree[x].sum *= val;
        Tree[x].val *= val;
        Tree[x].mul *= val;
        Tree[x].add *= val;
    }
    void pushadd(int x, ll val) { //打加法lazy标记
        Tree[x].sum += Tree[x].sz * val;
        Tree[x].val += val;
        Tree[x].add += val;
    }
    void pushdown(int x) { //不同问题的标记下推方式不同
        //下传反转标记
        if (Tree[x].mul != 1) { //乘法标记下推
            pushmul(Tree[x].ch[0], Tree[x].mul);
            pushmul(Tree[x].ch[1], Tree[x].mul);
        }

        if (Tree[x].add) { //加法标记下推
            pushadd(Tree[x].ch[0], Tree[x].add);
            pushadd(Tree[x].ch[1], Tree[x].add);
        }
        if (Tree[x].reverse) {
            pushreverse(Tree[x].ch[0]);
            pushreverse(Tree[x].ch[1]);
            Tree[x].reverse = 0;
        }
        Tree[x].mul = 1; //乘法标记复原
        Tree[x].add = 0; //加法标记复原
    }

    void update(int x) { //不同问题写法不同
        int l = Tree[x].ch[0], r = Tree[x].ch[1];
        Tree[x].sz = 1;
        Tree[x].sum = Tree[x].val;
        //Tree[x].maxv = Tree[x].val;
        if (l) {
            Tree[x].sz += Tree[l].sz;
            Tree[x].sum += Tree[l].sum;
            //Tree[x].maxv = max(Tree[x].maxv, Tree[l].maxv);
        }
        if (r) {
            Tree[x].sz += Tree[r].sz;
            Tree[x].sum += Tree[r].sum;
            //Tree[x].maxv = max(Tree[x].maxv, Tree[r].maxv);
        }
    }

    void rotate(int x) {
        //将x旋转为根
        if (Tree[x].is_root)
            return;
        int k = getson(x), fa = Tree[x].fa;
        int fafa = Tree[fa].fa;
        pushdown(fa);
        pushdown(x);    //先要下传标记
        Tree[fa].ch[k] = Tree[x].ch[k ^ 1];
        if (Tree[x].ch[k ^ 1])
            Tree[Tree[x].ch[k ^ 1]].fa = fa;
        Tree[x].ch[k ^ 1] = fa;
        Tree[fa].fa = x;
        Tree[x].fa = fafa;
        if (!Tree[fa].is_root)
            Tree[fafa].ch[fa == Tree[fafa].ch[1]] = x;
        else
            Tree[x].is_root = true, Tree[fa].is_root = false;
        update(fa);
        update(x);    //如果维护了信息，就要更新节点
    }
    void push(int x) {
        if (!Tree[x].is_root)
            push(Tree[x].fa);
        pushdown(x);
    }
    int findroot(int x) {
        //找到x在原树中的根节点
        access(x);
        Splay(x);
        pushdown(x);
        while (Tree[x].ch[0])
            pushdown(x = Tree[x].ch[0]);//找到深度最小的点即为根节点
        return x;
    }
    void Splay(int x) {
        //让x成为Splay的根，且x不含右儿子
        push(x);   //在Splay到根之前，必须先传完反转标记
        for (int fa; !Tree[x].is_root; rotate(x)) {
            if (!Tree[fa = Tree[x].fa].is_root) {
                rotate((getson(x) == getson(fa)) ? fa : x);
            }
        }
    }
    void access(int x) {
        //访问某节点。作用是：对于访问的节点x，打通一条从树根（真实的LCT树）到x的重链；如果x往下是重链，那么把x往下的重边改成轻边。结束后x没有右儿子（没有深度比他大的点）
        int y = 0;
        do {
            Splay(x);
            Tree[Tree[x].ch[1]].is_root = true;
            Tree[Tree[x].ch[1] = y].is_root = false;
            update(x);    //如果维护了信息记得更新。
            x = Tree[y = x].fa;
        } while (x);
    }
    void mroot(int x) {
        //把某个节点变成树根（这里的根指的是整棵LCT的根）
        access(x);//使x与根结点处在同一棵splay中
        Splay(x);//x成为这棵splay的根,x只有左儿子
        //由于根节点所在的splay中，根节点没有左儿子（没有深度比他小的节点），将x的左右子树翻转
        pushreverse(x);
    }
    void link(int u, int v) {
        //连接u所在的LCT和v所在的LCT
        mroot(u);//先让u成为其所在LCT的根
        if(findroot(v) != u)
            Tree[u].fa = v;//如果u与v不在同一棵splay中，就把v设置为u的父亲
    }
    void cut(int u, int v) {
        //分离出两棵LCT
        mroot(u);   //先让u成为其所在LCT的根
        access(v); //让u和v在同一棵Splay中
        Splay(v);    //连接u、v，u是v的左儿子
        pushdown(v);     //先下传标记
        if (Tree[v].ch[0]) {
            Tree[Tree[v].ch[0]].fa = Tree[v].fa;
            Tree[Tree[v].ch[0]].is_root = true;
        }
        Tree[v].fa = 0;
        Tree[v].ch[0] = 0;
        //v的左孩子表示v上方相连的重链
        update(v);  //记得维护信息
    }
    bool judge(int u, int v) {
        //判断u和v是否连通
        while (Tree[u].fa)
            u = Tree[u].fa;
        while (Tree[v].fa)
            v = Tree[v].fa;
        return u == v;
    }
    void split(int u, int v) {
        //获取u->v的路径
        mroot(u);//让u成为根结点
        access(v);//访问v
        Splay(v);//把v转到根结点，此时u的父亲为v
    }
    void modify(int x, int v) {
        //改变点值
        access(x);
        Splay(x);
        Tree[x].val = v; //更改值
        update(x);
    }
} lct;
//初始化
lct.init(n);

//输入点权
scanf("%lld", &lct.Tree[i].val);

//边权
Tree[i + n].val = e[i].w;
lct.link(e[i].u, i + n);
lct.link(e[i].v, i + n);

//加边，不能加自环
lct.link(u, v);

//删边
lct.cut(u, v);

//判断两点是否连通
ans = lct.judge(u, v);

//更改点权为k
lct.modify(u, k);

//查询两点路径权值和(可以将点权设为1,查询两点间距离)
lct.split(u, v);
ans = lct.Tree[v].sum;

//将u到v路径上点权都加上c
lct.split(u, v);
lct.pushadd(v, c);

//将u到v路径上点权都乘上c
lct.split(u, v);
lct.pushmul(v, c);
