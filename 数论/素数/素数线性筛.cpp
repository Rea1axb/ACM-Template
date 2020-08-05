bool notp[N];
int prime[N],pnum;//prime里存素数
void sieve()
{
    memset(notp,0,sizeof(notp));
    notp[0]=notp[1]=1;
    pnum=0;
    for(int i=2;i<N;i++)
    {
        if(!(notp[i])) prime[++pnum]=i;
        for(int j=1;j<=pnum&&prime[j]*i<N;j++)
        {
            notp[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}