/*

一般特征：
1.对子树的询问
2.没有修改

时间复杂度：
根节点到树上任意节点的轻边数量不超过logn条，一个节点只会因为轻边而被重新遍历一遍，
所以节点的遍历次数=logn+1，总时间复杂度：O(nlogn)

基本步骤：
1.遍历非重儿子，求出它们的答案，不保留贡献
2.遍历重儿子，求出答案，保留贡献
3.继承重儿子信息，遍历非重儿子，加入信息


*/



/*
例题：求出每个节点的子树中出现次数最多的颜色编号，如果有多种颜色数量最多，求多种颜色编号的和
*/

int son[MAXN], sz[MAXN], nowson;
//son:记录节点的重儿子，sz:记录子树大小， nowson:当前的重儿子
int color[MAXN], cnt[MAXN], maxcnt;
ll ans[MAXN], sum;

void dfs1(int u, int fa) { //轻重链剖分
    sz[u] = 1;
    int maxson = -1;
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > maxson) {
            son[u] = v;
            maxson = sz[v];
        }
    }
}

void update(int u, int fa, int val) {
    cnt[color[u]] += val;
    if (cnt[color[u]] > maxcnt) {
        maxcnt = cnt[color[u]];
        sum = color[u];
    } else if (cnt[color[u]] == maxcnt) {
        sum += color[u];
    } //统计方式因问题的不同而不同
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa || v == nowson) continue;
        update(v, u, val); //将轻儿子信息加上
    }
}

void dfs2(int u, int fa, bool keep) { //keep表示是否保留该节点的贡献
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == fa || v == son[u]) continue;
        dfs2(v, u, 0); //先遍历其非重儿子，获取答案，但不保留贡献
    }
    if (son[u]) {
        dfs2(son[u], u, 1); //遍历重儿子，保留贡献
        nowson = son[u];
    }
    update(u, fa, 1); //继承重儿子信息，将非重儿子信息加上去
    nowson = 0; //若该节点为非重儿子，保证能够把子树的贡献全部删去
    ans[u] = sum; //更新答案方式因问题的不同而不同
    if (!keep) { //删除贡献，不保留信息
        update(u, fa, -1);
        sum = 0;
        maxcnt = 0;
    }
}
