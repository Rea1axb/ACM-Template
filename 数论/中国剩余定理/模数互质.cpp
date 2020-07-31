void exgcd(ll a,ll b,ll &g,ll &x,ll &y)
{
    if (b == 0) {
        g = a;
        x = 1;
        y = 0;
        return;
    }
    exgcd(b,a%b,g,y,x);
    y-=(a/b)*x;
}
ll n;
ll as[100005];//n  
ll ms[100005];
ll china()
{
    ll ans=0,lcm=1,x,y,g;
    for(int i=0;i<n;i++) lcm*=as[i];
    for(int i=0;i<n;i++)
    {
        ll tp=lcm/as[i];
        exgcd(tp,as[i],g,x,y);
        x=(x%as[i]+as[i])%as[i];
        ans=(ans+tp*x*ms[i])%lcm;
    }
    return (ans%lcm+lcm)%lcm;
}
