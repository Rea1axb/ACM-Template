/*
	给定一个长为n的序列{a1,a2,a3..}, 询问区间a1*cnt(a1) + a2*cnt(a2) + ... 的最大值, 即某个值乘上出现次数
*/
#define inf 0x3f3f3f3f3f3f
#define N 100005
#define M 4000005
typedef long long ll;
using namespace std;
struct point{
	ll l,r,id;
	ll res;
}q[N];
ll vis[M];
ll a[N],pos[N];
ll s[N],as[N];
bool cmp(const point &a,const point &b)
{
	return (pos[a.l]^pos[b.l]) ? pos[a.l] < pos[b.l] : a.r < b.r;
}
bool cmp2(const point &a,const point &b)
{
	return a.id<b.id;
}
ll rpos[N];
ll tempv[N];
int main()
{
	ll n,m;
	scanf("%lld%lld",&n,&m);
	ll b=sqrt(n);
	ll bnum=ceil((double) n/b);
	for(int i=1;i<=bnum;i++)
	{
		rpos[i]=b*i;
		for(int j=b*(i-1)+1;j<=rpos[i];j++)
		{
			pos[j]=i;
		}
	}
	rpos[bnum]=n;
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		s[i]=a[i];
	}
	sort(s+1,s+1+n);
	ll tot=unique(s+1,s+1+n)-s-1;
	for(int i=1;i<=n;i++)
	{
		as[i]=lower_bound(s+1,s+1+tot,a[i])-s;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+1+m,cmp);
	int i=1;
	for(ll k=0;k<=bnum;k++)
	{
		ll l=rpos[k]+1,r=rpos[k];
		ll ans=0;
		memset(vis,0,sizeof(vis));
		for(;pos[q[i].l]==k;i++)
		{
			if(pos[q[i].l]==pos[q[i].r])
			{
				ll res=0;
				for(int j=q[i].l;j<=q[i].r;j++)
				{
					tempv[as[j]]=0;
				}
				for(int j=q[i].l;j<=q[i].r;j++)
				{
					res=max(res,(++tempv[as[j]])*a[j]);
				}
				q[i].res=res;
				continue;
			}
			while(r<q[i].r)
			{
				r++;
				ans=max(ans,(++vis[as[r]])*a[r]);
			}
			ll temp=ans;
			while(l>q[i].l)
			{
				l--;
				ans=max(ans,(++vis[as[l]])*a[l]);
			}
			q[i].res=ans;
			while(l<rpos[k]+1)
			{
				--vis[as[l++]];
			}
			ans=temp;
		}
	}
	sort(q+1,q+1+m,cmp2);
	for(int i=1;i<=m;i++)
	{
		printf("%lld\n",q[i].res);
	}
}
