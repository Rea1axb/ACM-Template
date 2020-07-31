int s[N]，top=0;
for(int i=1;i<=n;i++)
{
	while(top&&a[s[top]]>a[i]) top--;
	if(s[top]==a[i]) s[top]=i;//去重复操作，视情况而定
	s[++top]=i;
}