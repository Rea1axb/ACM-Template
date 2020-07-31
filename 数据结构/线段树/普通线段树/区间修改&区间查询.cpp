#define ll long long
const int SIZE = 1e5+5;
struct node{
    int l,r;int val;
}T[SIZE*3];
int lazy[SIZE*3];
int arr[SIZE];// arr数组用于记录[1,n]的数据
void build(int l,int r,int rt){
    T[rt].l = l;T[rt].r = r;
    if(l==r){
        T[rt].val = arr[l];return ;
    }
    int mid = (l+r)>>1;
    build(l,mid,rt<<1);//注意是l（字母），不是1（数字）
    build(mid+1,r,rt<<1|1);
    T[rt].val = T[rt<<1].val + T[rt<<1|1].val;
}
// l,r为指针，L,R是要修改的区间[L,R],为整个区间加上x
void update(int L,int R,int x,int rt){
    if(L<=T[rt].l && R>=T[rt].r){
        T[rt].val += x*(T[rt].r-T[rt].l+1);
        lazy[rt] += x;
        return ;
    }
    int mid = (T[rt].l + T[rt].r)>>1;
    if(lazy[rt]){ // 下推标记更新一波
        T[rt<<1].val += lazy[rt]*(mid-T[rt].l+1);
        T[rt<<1|1].val += lazy[rt]*(T[rt].r-mid);
        lazy[rt<<1] += lazy[rt];
        lazy[rt<<1|1] += lazy[rt];
        lazy[rt] = 0;
    }
    if(L <= mid)update(L,R,x,rt<<1);
    if(R >mid)update(L,R,x,rt<<1|1);
    T[rt].val = T[rt<<1].val + T[rt<<1|1].val;
}

ll query(int L,int R,int rt){
    // printf("rt=%d",rt);
    if(L<=T[rt].l && R>=T[rt].r)return T[rt].val;
    int mid = (T[rt].l + T[rt].r)>>1;
    if(lazy[rt]){
        T[rt<<1].val += lazy[rt]*(mid-T[rt].l+1);
        T[rt<<1|1].val += lazy[rt]*(T[rt].r-mid);
        lazy[rt<<1] += lazy[rt];
        lazy[rt<<1|1] += lazy[rt];
        lazy[rt] = 0;
    }
    ll sum=0;
    if(L <= mid)sum += query(L,R,rt<<1);
    if(R > mid)sum += query(L,R,rt<<1|1);
    return sum;
}
