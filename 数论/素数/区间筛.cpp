//找L~R之间的质数
ll L,R;
int k;
bool notp[N];
int prime[N],pnum;
void sieve()
{
    memset(notp,0,sizeof(notp));
    notp[0]=notp[1]=1;
    pnum=0;
    for(int i=2;i<sqrt(R);i++)
    {
        if(!(notp[i])) prime[++pnum]=i;
        for(int j=1;j<=pnum&&prime[j]*i<sqrt(R);j++)
        {
            notp[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}
bool v[1000010];//v中存L开始的数是否为素数
void interval_sieve()
{
    memset(v,1,sizeof(v));
    if(L==1) v[0]=0;
    for(int i=1;i<=pnum;i++)
    {
        for(int j=(L-1)/prime[i]+1;j<=R/prime[i];j++)
        {
            if(j>1) v[prime[i]*j-L]=0;
        }//用prime中的素数筛L~R的素数
    }
}