for(M=1;M<=n;M<<=1);//获得层数M
for(int i=1;i<=M<<1;i++)//初始化
{
	T[i]=0;
}
for(int i=1,x;i<=n;i++)//建树
{
	scanf("%d",&x);
	modify(i,x);
}