/*
区间合数分解（d(x^k) ）//有几个因数

若 x 分解成质因子乘积的形式为 x = p1^a1 * p2^a2 * ... * pn^an，那么 d(x) = (a1 + 1) * (a2 + 1) * ... * (an + 1) .显然 d(x^k) = (a1 * k + 1) * (a2 * k + 1) * ... * (an * k + 1) .
*/

//先来发区间素数筛 2~sqrt(R)
ll num[1000010];L~R
ll d[1000010];//L~R的分解数 
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld%lld%d",&L,&R,&k);
        sieve();
        for(int i=0;i<=R-L;i++) d[i]=1,num[i]=i+L;
        for(int i=1;i<=pnum;i++)
        {
            ll st=(L+prime[i]-1)/prime[i]*prime[i];//st :L开始的第一个能整除prime[i]的数 
            for(ll j=st;j<=R;j+=prime[i])
            {
                int cnt=0;
                while(num[j-L]%prime[i]==0)
                {
                    num[j-L]/=prime[i];
                    cnt++;
                }
                d[j-L]=d[j-L]*(k*cnt%mod+1)%mod;//cn*k+1
            }
        }
        ll ans=0;
        for(int i=0;i<=R-L;i++)
        {
            if(num[i]!=1) d[i]=d[i]*(k+1)%mod;//未分解完，有大素数 
            ans=(ans+d[i])%mod;
        }
        printf("%lld\n",ans);
    }
}