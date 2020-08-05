const int SIZE=10500;
struct node{
    int l,r,time,id;
}q[SIZE];
struct Update{
    int x,y;
}upd[SIZE];
int l,r;
const int COLSIZE=1000500;
int col[COLSIZE];int unit;int bl[SIZE];int vis[COLSIZE];int ans=0;int res[SIZE];
void pop(int x){
    ans -= !--vis[x];
}
void push(int x){
    ans += !vis[x]++;
}
bool cmp(node a,node b){// 奇偶排序
    return (bl[a.l]^bl[b.l]) ? bl[a.l] < bl[b.l] : ((bl[a.r]^bl[b.r]) ? bl[a.r] < bl[b.r] : a.time < b.time);
}
void modify(int x){
    if(l <= upd[x].x && upd[x].x <= r){
        pop(col[upd[x].x]);
        push(upd[x].y);
    }
    swap(upd[x].y,col[upd[x].x]);
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    int tmpb=pow(double(n),double(2.0/3.0));
    for(int i=1;i<=n;i++){
        scanf("%d",&col[i]);
        bl[i]=i/tmpb;
    }
    int time=0;char ch;int x,y;
    int mm=1,updm=1;
    for(int i=1;i<=m;i++){
        cin>>ch>>x>>y;
        if(ch=='Q'){// Q查询
            q[mm].l=x;q[mm].r=y;q[mm].time=time;q[mm].id=mm;mm++;
        }
        else if(ch=='R'){// R更换画笔
            upd[updm].x=x,upd[updm].y=y;time++;updm++;
        }
    }
    sort(q+1,q+mm,cmp);
    l=1,r=0;int tp=0;
    for(int i=1;i<mm;i++){
        while(l < q[i].l)pop(col[l++]);
        while(l > q[i].l)push(col[--l]);
        while(r < q[i].r)push(col[++r]);
        while(r > q[i].r)pop(col[r--]);
        while(tp < q[i].time)modify(++tp);
        while(tp > q[i].time)modify(tp--);
        res[q[i].id]=ans;
    }
}