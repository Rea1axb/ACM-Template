struct Node{
	ll pre,suf,max,sum;
}T[200000],null;
Node merge(Node l, Node r)
{
	Node res;
	res.sum=l.sum+r.sum;//区间和 
	res.pre=max(l.pre,l.sum+r.pre);//最大前缀 
	res.suf=max(r.suf,l.suf+r.sum);//最大 
	res.max=max(l.max,r.max);//最大子段和 
	res.max=max(res.max,l.suf+r.pre);
	return res;
}
void modify(int n,int v)//单点修改 
{
	for(T[n+=M]={v,v,v,v},n>>=1;n;n>>=1)
		T[n]=merge(T[n+n],T[n+n+1]);
}
ll query(int l, int r)//查询 
{
	Node resl(null),resr(null);
//	resl.pre=resl.suf=resl.sum=0;
//	resr.pre=resr.suf=resr.sum=0;
	resl.max=resr.max=-inf;
	for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1)
	{
		if(~l & 1) resl=merge(resl,T[l^1]);
		if(r & 1) resr=merge(T[r^1],resr);
	}
	return merge(resl,resr).max;
}