void add(int l,int r,int v)//区间加减 
{
	for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1)
	{
		if(~l & 1) T[l^1]+=v;
		if(r & 1) T[r^1]+=v;
	}
}
ll query(int n)//单点查询 
{
	ll ans=0;
	for(n+=M;n;n>>=1) ans+=T[n];
	return ans;
}