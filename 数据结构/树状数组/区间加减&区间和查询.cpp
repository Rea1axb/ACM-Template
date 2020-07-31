#define LL long long
const int SIZE=10005;
ll T1[SIZE],T2[SIZE],T[SIZE];//T[]用于存结点值，用过一次即仍
int lowbit(int k){
	return k&-k;
}
void update(ll x,ll,N,ll w){//把x位置之后所有数的值+w
	for(ll i=x;i<=N;i+=lowbit(i)){
		T1[i]+=w;T2[i]+=w*(x-1);
	}
}
void range_update(ll l,ll r,ll v){//在[l,r]上加v
	update(l,v);update(r+1,-v);
}
ll sum(ll x){
	ll ans=0;
	for(ll i=x;i>0;i-=lowbit(i)){
		ans+=x*T1[i]-T2[i];
	}
	return ans;
}
ll range_ask(ll l,ll r){//返回[l,r]的和
	return sum(r)-sum(l-1);
}
void init(int N){
	for(int i=1;i<=N;i++){
		update(i,T[i]-T[i-1]);
	}
}