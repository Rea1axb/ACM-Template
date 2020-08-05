//素数筛
pair <int ,int> d[N];int dnum;//分解的质数 
bool is_prime(ll x)
{//大素数检测，可用米勒罗宾代替 
    if(x==1)
        return false;
    if(x==2||x==3)
        return true;
    if(x%6!=1&&x%6!=5)
        return false;
    int s=sqrt(x);
    for(int i=5;i<=s;i+=6)
        if(x%i==0||x%(i+2)==0)
            return false;
    return true;
}
void prime_div(ll n)
{
    dnum=0;
    if(n==0) return;
    int num;
    for(int i=1;i<=pnum;i++)
    {
        if(n%prime[i]==0)
        {
            num=0;
            while(n%prime[i]==0)
            {
                num++;
                n/=prime[i];
            }
            d[++dnum]=make_pair(prime[i],num);
        }
        if(is_prime(n))
        {
            d[++dnum]=make_pair(n,1);
            break;
        }
    } 
}
int main()
{
    ll n;
    sieve();
    while(~scanf("%lld",&n))
    {
        prime_div(n);
        for(int i=1;i<=dnum;i++)
        {
            cout<<d[i].first<<" "<<d[i].second<<endl;
        }
    }
} 