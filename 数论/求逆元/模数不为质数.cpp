void exgcd(ll a,ll b,ll &g,ll &x,ll &y){
	if(!b)
	{
		g=a;
		x=1;
		y=0;
		return ;
	}
	exgcd(b,a%b,g,y,x);
	y-=(a/b)*x;
}
//a=1( %mod )
//ax+mod *y=1;
//x为逆元
int main()
{
	ll a,mod,x,y,g;
	cin>>a;//a为要求的逆元 
	cin>>mod;
	exgcd(a,mod,g,x,y);
	//g=1; 
	x=(x%mod+mod)%mod;
	cout<<x;//x为逆元 
}
