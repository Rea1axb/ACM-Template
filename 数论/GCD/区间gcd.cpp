int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
int v[N], l[N], a[N], len[N];
map<ll, ll> M;
struct point
{
    int l, v;
} p[N][55];

scanf("%d", &n);
memset(v, 0, sizeof(v));
memset(len, 0, sizeof(len));
memset(l, 0, sizeof(l));
M.clear();
for (int i = 1; i <= n; i++)
	scanf("%d", &a[i]);
for (int i = 1, j; i <= n; i++) //枚举右端点
{
	for (v[i] = a[i], j = l[i] = i; j; j = l[j] - 1)
  	{
  		v[j] = gcd(v[j], a[i]);
  		while (l[j] > 1 && gcd(a[i], v[l[j] - 1]) == gcd(a[i], v[j]))
    	l[j] = l[l[j] - 1];//和自己边界l[j]-1相同,更新l[j]
		p[i][len[i]].l = l[j];
    	p[i][len[i]].v = v[j];
    	len[i]++;//边界种类++；
    	M[v[j]] += (j - l[j] + 1);//gcd为v[j]的数目++
  	}
}
int l, r, ans;
scanf("%d%d", &l, &r);
for (int i = 0; i < len[r]; i++)
{
	if (l >= p[r][i].l)
	{
    	ans = p[r][i].v;
    	break;
  	}
}
printf("%d %lld\n", ans, M[ans]);
