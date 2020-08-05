/*
    本模板需要配合矩阵快速幂食用qwq
*/
typedef long long ll;
int n;
mat A(2,2),B(2,2);
const int SIZE=1e5+50;
char str[SIZE];
struct node{
    int l,r;
    bool lazy=0;
}T[SIZE*3];
mat ma[SIZE*3][2];//0是正序，1是反序
void push_up(int root){
    ma[root][0]=ma[root<<1][0]*ma[(root<<1)|1][0];
    ma[root][1]=ma[root<<1][1]*ma[(root<<1)|1][1];
    return ;
}
void build(int root,int l,int r){
    T[root].l=l;T[root].r=r;
    if(l==r){
        if(str[l]=='A'){
            ma[root][0].n = A.n;ma[root][0].m = A.m;
            for(int i=0;i<A.n;i++)
            for(int j=0;j<A.m;j++)
                ma[root][0].v[i][j]=A.v[i][j];
            //-----------------------------------
            ma[root][1].n = B.n;ma[root][1].m = B.m;
            for(int i=0;i<B.n;i++)
            for(int j=0;j<B.m;j++)
                ma[root][1].v[i][j]=B.v[i][j];
        }
        else{
            ma[root][0].n = B.n;ma[root][0].m = B.m;
            for(int i=0;i<B.n;i++)
            for(int j=0;j<B.m;j++)
                ma[root][0].v[i][j]=B.v[i][j];
            //-----------------------------------
            ma[root][1].n = A.n;ma[root][1].m = A.m;
            for(int i=0;i<A.n;i++)
            for(int j=0;j<A.m;j++)
                ma[root][1].v[i][j]=A.v[i][j];
        }
        return ;
    }
    int mid=(T[root].l+T[root].r)>>1;
    build(root<<1,l,mid);
    build((root<<1)|1,mid+1,r);
    push_up(root); 
    return ;
}

void push_down(int root){
    if(T[root].lazy){
        swap(ma[root<<1][0],ma[root<<1][1]);
        swap(ma[(root<<1)|1][0],ma[(root<<1)|1][1]);
        T[root<<1].lazy=!T[root<<1].lazy;
        T[(root<<1)|1].lazy=!T[(root<<1)|1].lazy;
        T[root].lazy=0;
    }
}
void update(int root,int l,int r){
    if(l<=T[root].l && T[root].r<=r){
        T[root].lazy = !T[root].lazy;
        swap(ma[root][0],ma[root][1]);
        return ;
    }
    push_down(root);
    int mid = (T[root].l + T[root].r)>>1;
    if(l <= mid)update(root<<1,l,r);
    if(r > mid)update((root<<1)|1,l,r);
    push_up(root);
}

mat tmp(2,2);// 对最后的答案矩阵进行修改
void find(int root,int l,int r){
    if(l <= T[root].l && T[root].r<=r){
        tmp = tmp*ma[root][0]; 
        return;
    }
    push_down(root);
    int mid = (T[root].l + T[root].r)>>1;
    if(l <= mid)find(root<<1,l,r);
    if(mid < r)find((root<<1)|1,l,r);
    return;
}
int main(){
    A.v[0][0]=1;A.v[0][1]=0;A.v[1][0]=1;A.v[1][1]=1;
    B.v[0][0]=1;B.v[0][1]=1;B.v[1][0]=0;B.v[1][1]=1;
    int q;scanf("%d%d",&n,&q);
    scanf("%s",str+1);
    build(1,1,n);
    while(q--){
        int op;scanf("%d",&op);
        if(op==1){
            int L,R;scanf("%d%d",&L,&R);
            update(1,L,R);
        }
        else{
            int L,R;ll AA,BB;scanf("%d%d%lld%lld",&L,&R,&AA,&BB);
            tmp.v[0][0]=1;
            tmp.v[0][1]=0;
            tmp.v[1][0]=0;
            tmp.v[1][1]=1;
            mat qwq(1,2);
            qwq.v[0][0]=AA%mod;qwq.v[0][1]=BB%mod;
            find(1,L,R);
            qwq = qwq*tmp;
            qwq.display();
        }
    }
}