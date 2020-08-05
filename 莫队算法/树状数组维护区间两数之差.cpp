/*
    HDU - 6534 树状数组维护区间两数之差
    i<j，|ai−aj|≤ K，n  (1≤n≤27000), m (1≤m≤27000) and K (1≤K≤109)
*/
//树状数组部分--------------
int lowbit(int k){return k&-k;}
void add(int x,int k){
    while(x<=n){
        tree[x]+=k;
        x+=lowbit(x);
    }
}
int Get_sum(int x){
    int ans=0;
    while(x!=0){
        ans+=tree[x];
        x-=lowbit(x);
    }
    return ans;
}
//-----------------------------
/*
// 统计 a[i]^a[i+1]^...a[j]=k,非树状数组
// 1 ≤ n, m ≤ 100 000, 0 ≤ k ≤ 1 000 000,(0 ≤ ai ≤ 1 000 000)
ll tmp=0;
void add(ll x){
    tmp += cnt[sum[x]^k];
    cnt[sum[x]]++;
}
void del(ll x){
    cnt[sum[x]]--;
    tmp -= cnt[sum[x]^k];
}
*/
int sum=0;
void push(int x){
    sum+=Get_sum(rr[x])-Get_sum(ll[x]-1);
    add(a[x],1);
}
void pop(int x){
    add(a[x],-1);
    sum-=Get_sum(rr[x])-Get_sum(ll[x]-1);
}

int main(){
    sort(q+1,q+1+m,cmp);
    int L=1,R=0;
    for(int i=1;i<=m;i++){
        while(L > q[i].l)push(--L);
        while(R < q[i].r)push(++R);
        while(L < q[i].l)pop(L++);
        while(R > q[i].r)pop(R--);
        display[q[i].id]=sum;//用于输出
    }
}