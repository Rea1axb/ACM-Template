/*
	HDU5975 有n个集合，第 i 个集合的数是[i-lowbit(i)+1,i-1]+i
	第一种方式是集合[a,b]共有多少个数=lowbit之和？(sol1)
	第二种方式是数字x在几个集合里面？(sol2)
	long long型注意！
*/
#define ll long long
ll lowbit(ll x){
	return x&(-x);
}
ll sum(ll x){			//计算[1,x]中所有数lowbit(k)之和
	ll ans=0ll;
	for(ll p=1ll;p<=x;p<<=1){
		ans+=(x/p-x/(p<<1))*p;
	}
	return ans;
}
ll sol1(ll x,ll y){		//计算[x,y]中所有树的lowbit(k)之和
	return sum(y)-sum(x-1ll);
}
ll sol2(ll x,ll n){		
	ll res=0ll;
	while(x<=n){
		res++;
		x+=lowbit(x);
	}
	return res;
}