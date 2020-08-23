void add(int L,int R,int v)//区间修改  
{
	L+=M-1,R+=M+1;
	for(int l=L,r=R;l^r^1;l>>=1,r>>=1)
	{
		if(~l & 1) lazy[l^1]+=v,T[l^1]+=v;
		if(r & 1) lazy[r^1]+=v,T[r^1]+=v;
	}
	for(int l=L>>1,r=R>>1;l;l>>=1,r>>=1)
	{
		T[l]=max(T[l+l],T[l+l+1])+lazy[l];
		T[r]=max(T[r+r],T[r+r+1])+lazy[r];
	}
}
int query(int l, int r)//区间查询 
{
	int lmax=-inf,rmax=-inf;
	for(l+=M-1,r+=M+1;l^r^1;l>>=1,r>>=1)
	{
		if(lazy[l]&&lmax!=-inf) lmax+=lazy[l];
		if(lazy[r]&&rmax!=-inf) rmax+=lazy[r];
		if(~l & 1) lmax=max(lmax,T[l^1]);
		if(r & 1) rmax=max(rmax,T[r^1]); 
	}
	for(;l;l>>=1,r>>=1)
	{
		lmax+=lazy[l],rmax+=lazy[r];
	}
	return max(lmax,rmax);
}