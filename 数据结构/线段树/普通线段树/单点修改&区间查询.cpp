#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
const int SIZE = 5e5+50;
struct node{
    int l,r;int val;
}T[SIZE*3];
int arr[SIZE];// 用于存从[1,n]中的数组
void build(int l,int r,int rt){
    T[rt].l = l;T[rt].r = r;
    if(l == r){
        T[rt].val = arr[l];
        return ;
    }
    int mid = (T[rt].l + T[rt].r)>>1;
    build(lson); build(rson);
    T[rt].val = T[rt<<1].val + T[rt<<1|1].val;
}
void update(int tar,int rt,int k){// 单点修改将tar改为k
    if(T[rt].l==T[rt].r){
        T[rt].val += k;return ;
    }
    int mid = (T[rt].l + T[rt].r)>>1;
    if(tar <= mid) update(tar,rt<<1,k);
    else update(tar,rt<<1|1,k);
    T[rt].val = T[rt<<1].val + T[rt<<1|1].val;
}
int ans = 0;
void Find(int rt,int l,int r){
    if(T[rt].l>=l && T[rt].r<=r){
        ans += T[rt].val;return ;
    }
    if(T[rt<<1].r>=l) Find(rt<<1,l,r);
    if(T[rt<<1|1].l<=r) Find(rt<<1|1,l,r);
}