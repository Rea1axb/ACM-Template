int sum[MAXM*4],add[MAXM*4];
int a[MAXM],n;
int idx;
int first[MAXM];
struct edge{
	int v,next;
}e[MAXM*2];
int f[MAXM],son[MAXM],size[MAXM],dfn[MAXM],dep[MAXM],top[MAXM],seq[MAXM];
int cnt;
int mod;
/*
f是节点的父亲,son是重儿子,size是以该节点为根的子树大小, dfn是给节点重新编上的序号.
seq是与dfn相反的数组,表示标到的这个号表示的原节点, top是目前节点所在链的顶端.
dep是结点的深度
*/

//---------------------加边和预处理--------------------------------
void eadd(int a,int b)
{
	e[idx].v = b;
	e[idx].next = first[a];
	first[a] = idx++;
}
void init()
{
    memset(first,-1,sizeof(first));
    idx = 1;
    cnt = 0;
}
void dfs1(int u,int fa,int depth)
{
	f[u] = fa; size[u] = 1; dep[u] = depth;
	int maxson = -1;
	for(int i = first[u];i != -1;i = e[i].next){
		int v = e[i].v;
		if(v == fa) continue;
		dfs1(v,u,depth+1);
		size[u] += size[v];
		if(size[v]>maxson) son[u] = v,maxson = size[v];
	}
}
void dfs2(int u,int t)
{
	top[u] = t;
	dfn[u] = ++cnt;
	seq[cnt] = a[u];
	if(!son[u]) return;
	dfs2(son[u],t);
	for(int i = first[u];i != -1;i = e[i].next){
		int v = e[i].v;
		if(v != son[u]&&v != f[u]) dfs2(v,v);
    }
}


//--------------------------线段树----------------------------------
void pushup(int rt)
{
	sum[rt] = (sum[rt<<1]+sum[rt<<1|1])%mod;
}
void build(int l,int r,int rt)
{
	if(l == r){
		sum[rt] = seq[l]%mod;
		return;
	}
	int m = (l+r)>>1;
	build(l,m,rt<<1);
	build(m+1,r,rt<<1|1);
	pushup(rt);
}
void pushdown(int rt,int ln,int rn)
{
	if(add[rt]){
		add[rt<<1] = (add[rt<<1] + add[rt])%mod;
		add[rt<<1|1] = (add[rt<<1|1] + add[rt])%mod;
		sum[rt<<1] = (sum[rt<<1] + add[rt]*ln%mod)%mod;
		sum[rt<<1|1] = (sum[rt<<1|1] + add[rt]*rn%mod)%mod;
		add[rt] = 0;
	}
}
void update(int L,int R,int C,int l,int r,int rt)
{
	if(L <= l&&r <= R){
		sum[rt] = (sum[rt] + C*(r-l+1)%mod)%mod;
		add[rt] = (add[rt] + C)%mod;
		return;
	}
	int m = (l+r)>>1;
	pushdown(rt,m-l+1,r-m);
	if(L <= m) update(L,R,C,l,m,rt<<1);
	if(R >  m) update(L,R,C,m+1,r,rt<<1|1);
	pushup(rt);
}

ll query(int L,int R,int l,int r,int rt)
{
	if(L <= l&&r <= R){
		return sum[rt];
	}
	int m = (l+r)>>1;
	pushdown(rt,m-l+1,r-m);
	ll ans = 0;
	if(L <= m) ans = (ans + query(L,R,l,m,rt<<1))%mod;
	if(R >  m) ans = (ans + query(L,R,m+1,r,rt<<1|1))%mod;
	return ans;
}


//----------------------------树上加、树上求和---------------------
void tadd(int x,int y,int k)
{
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        update(dfn[top[x]],dfn[x],k,1,n,1);
        x = f[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    update(dfn[x],dfn[y],k,1,n,1);
}
ll tsum(int x,int y)
{
    ll ans = 0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        ans = (ans + query(dfn[top[x]],dfn[x],1,n,1))%mod;
        x = f[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    ans = (ans + query(dfn[x],dfn[y],1,n,1))%mod;
    return ans;
}


int main()
{
	int m;
	int num;//根节点序号
	scanf("%d%d%d%d",&n,&m,&num,&mod);
	init();
	for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
	}
	for(int i = 1;i <= n-1;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        eadd(u,v);
        eadd(v,u);
	}
	dfs1(num,0,1);
	dfs2(num,num);
	build(1,n,1);
	for(int i = 1;i <= m;i++){
        int op;
        scanf("%d",&op);
        if(op == 1){//将树从x到y节点最短路径上所有节点的值都加上z
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            tadd(x,y,z%mod);
        }
        else if(op == 2){//求树从x到y节点最短路径上所有节点的值之和
            int x,y;
            scanf("%d%d",&x,&y);
            printf("%lld\n",tsum(x,y));
        }
        else if(op == 3){//将以x为根节点的子树内所有节点值都加上z
            int x,z;
            scanf("%d%d",&x,&z);
            update(dfn[x],dfn[x]+size[x]-1,z%mod,1,n,1);
        }
        else if(op == 4){//求以x为根节点的子树内所有节点值之和
            int x;
            scanf("%d",&x);
            printf("%lld\n",query(dfn[x],dfn[x]+size[x]-1,1,n,1)%mod);
        }
	}
	return 0;
}
