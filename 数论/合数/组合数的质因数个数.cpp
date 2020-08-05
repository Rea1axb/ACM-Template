// C(m,n)=n! / ((n - m)! * m!);
//素数筛 
//分别计算分子和分母中不同质因子的个数，相减大于 0 则对答案贡献 1
int ans=0;
    for(int i=1;i<=pnum;i++)
    {
        int tnum=0;
        int ch=prime[i];
        for(;ch<=n||ch<=m||ch<=n-m;ch*=prime[i])
        {
            if(n>=ch) tnum+=n/ch;
            if(m>=ch) tnum-=m/ch;
            if(n-m>=ch) tnum-=(n-m)/ch;
        }
//      cout<<tnum<<endl;
        if(tnum>0) ans++;
    }
    printf("%d\n",ans);