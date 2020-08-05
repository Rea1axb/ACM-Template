//先求n！逆元
for(int i=n-1;i>=1;i--)
{
 	inv[i]=inv[i+1]*(i+1)%mod;ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}//最大公约      //建议直接__gcd()
ll lcm(ll a,ll b){
	return a*b/gcd(a,b);//可能会爆，快速乘
}//最大公倍
