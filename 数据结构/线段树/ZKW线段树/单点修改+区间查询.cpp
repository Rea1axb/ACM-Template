void modify(int n,int v)//单点修改 
{
	for(T[n+=M]+=v,n>>=1;n;n>>=1)
		T[n]=T[n+n]+T[n+n+1];
}
ll query(int l, int r)//区间查询和，可调为最大 
{
	ll ans=0;
	for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1)
	{
		if(~l & 1) ans+=T[l^1];
		if(r & 1) ans+=T[r^1];
	}
	return ans;
}