/*
    HYSBZ - 1878 统计[L,R]区间内有多少个不同的数
*/
#define ll long long
const ll SIZE=1005000;
struct node{
    ll L,R;
    ll id,res;
}q[SIZE];
ll c[SIZE];ll n,m;ll num[SIZE];ll sum=0;ll dis[SIZE];ll pos[SIZE];
bool cmp(const node& a,const node& b){//奇偶排序
    return (pos[a.L]^pos[b.L])?pos[a.L]<pos[b.L]:((pos[a.L] &1)?a.R<b.R:a.R>b.R);
}
ll ans=0;
int main(){
    scanf("%lld",&n);//n个数
    ll tmpb=sqrt(n);
    sort(q+1,q+1+m,cmp);
    ll L=1,R=0;
    for(ll i=1;i<=m;i++){
        while(L<q[i].L)ans-=!--num[c[L++]];
        while(L>q[i].L)ans+=!num[c[--L]]++;
        while(R<q[i].R)ans+=!num[c[++R]]++;
        while(R>q[i].R)ans-=!--num[c[R--]];
        dis[q[i].id]=ans;//用于输出
    }

}