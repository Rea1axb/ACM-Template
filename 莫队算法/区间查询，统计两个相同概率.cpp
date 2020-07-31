/*
    HYSBZ - 2038 小Z的袜子
    统计[L,R]区间内选两只袜子，颜色相同的概率。区间查询，统计两个相同概率。
    N,M ≤ 50000，1 ≤ L < R ≤ N，Ci ≤ N。
*/
#define ll long long
const ll SIZE=50050;
struct node{//查询
    ll L,R;
    ll id,res1,res2;
}q[SIZE];

ll c[SIZE];//n只袜子的颜色
ll n,m,unit;//n只瓦子，m次查询
ll num[SIZE];

ll com(ll nn,ll mm){
    if(mm>nn/2)mm=nn-mm;
    ll aa=1,bb=1;
    for(ll i=1;i<=mm;i++){
        aa*=nn+1-i;
        bb*=i;
        if(aa%bb==0){
            aa/=bb;
            bb=1;
        }
    }
    ll tmp=aa/bb;
    return tmp;
}

//朴素排序
bool cmp(node a,node b){
    if(a.L/unit != b.L/unit)return a.L/unit < b.L/unit;
    else return a.R < b.R;
}

//对答案进行排序
bool cmp_id(node a,node b){
    return a.id<b.id;
}

int main(){
    cin>>n>>m;
    unit=sqrt(n);//分块
    for(ll i=1;i<=n;i++)cin>>c[i];
    for(ll i=1;i<=m;i++){
        q[i].id=i;
        cin>>q[i].L>>q[i].R;
    }
    sort(q+1,q+1+m,cmp);
    ll L=1,R=0;
    ll sum=0;
    for(ll i=1;i<=m;i++){
        while(R<q[i].R){
            R++;
            if(num[c[R]]>1)sum-=com(num[c[R]],2);
            num[c[R]]++;
            if(num[c[R]]>1)sum+=com(num[c[R]],2);
        }
        while(R>q[i].R){
            if(num[c[R]]>1)sum-=com(num[c[R]],2);
            num[c[R]]--;
            if(num[c[R]]>1)sum+=com(num[c[R]],2);
            R--;
        }
        while(L<q[i].L){
            if(num[c[L]]>1)sum-=com(num[c[L]],2);
            num[c[L]]--;
            if(num[c[L]]>1)sum+=com(num[c[L]],2);
            L++;
        }
        while(L>q[i].L){
            L--;
            if(num[c[L]]>1)sum-=com(num[c[L]],2);
            num[c[L]]++;
            if(num[c[L]]>1)sum+=com(num[c[L]],2);
        }
        ll under=com(q[i].R-q[i].L+1,2);
        ll gcdd=__gcd(sum,under);
        q[i].res1=sum/gcdd;q[i].res2=under/gcdd;
    }
}