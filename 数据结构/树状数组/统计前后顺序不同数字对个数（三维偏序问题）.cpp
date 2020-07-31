#define ll long long
const int SIZE=200000+50;
ll arr[3][SIZE];//数据存放为[1,n]的范围
ll tree[SIZE];
int n;//n为每组数字个数
int lowbit(int k){
    return k&-k;
}
void add(int x,int k){
    while(x<=n){
        tree[x]+=k;
        x+=lowbit(x);
    }
}
ll sum(int x){
    ll ans=0;
    while(x!=0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
int pos[SIZE];
ll CountInversions(int x,int y){
    memset(tree,0,sizeof(tree));
    for(int i=1;i<=n;i++){
        pos[arr[x][i]]=i;
    }
    ll ans=0;
    for(int i=n;i;i--){
        ans+=sum(pos[arr[y][i]]);
        add(pos[arr[y][i]],1);
    }
    return ans;
}

//求三组数中有多少对数的前后顺序在三组数中都相同(三维偏序问题)
ll invers=(CountInversions(0,1)+CountInversions(1,2)+CountInversions(2,0))/2ll;
ll tot=((ll)n*(ll)(n-1))/2ll;//这里一定要加ll!!不然会爆
printf("%lld\n",tot-invers);