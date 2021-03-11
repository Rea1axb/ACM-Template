/*
笛卡尔树是一种二叉树，每一个结点由一个键值二元(k, w)构成。
要求k满足二叉搜索树的性质，而w满足堆的性质。
*/
//数组元素值当作键值w，而把数组下标当作键值k的笛卡尔树
int stk[MAXN];
int build(ll * a, int n) {
    int top = 0;
    for (int i = 1; i <= n; i++) {
        int k = top;
        while (k > 0 && a[stk[k]] > a[i]) k--;
        if (k) rs[stk[k]] = i;
        if (k < top) ls[i] = stk[k + 1];
        stk[++k] = i;
        top = k;
    }
    return stk[1];
}
ll a[MAXN];
int rt = build(a, n);
