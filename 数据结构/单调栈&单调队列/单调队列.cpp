int l=0,r=1;
int q[N];
for(int i=1;i<=n;i++)
{
	while(l<=r&&a[q[r]]>a[i]) r--;
	q[++r]=i;
	while(l<=r&&q[l]<i-m+1) l++;//判断条件看情况
	ans[i]=a[q[l]];
}