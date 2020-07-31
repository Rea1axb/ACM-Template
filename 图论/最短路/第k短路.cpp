int dist[1010];
int first[1010];//正向图
int rfirst[1010];//反向图
int vis[1010];
int times[1010];//点的访问次数
int idx,ridx;
struct node{
    int p,g,h;//p表示点的编号，g为点到终点的距离（估价）， h为点到起点的距离（实际）
    bool operator < (const node &t)const
    {
        return t.g+t.h<g+h;
    }
};
struct qnode{
    int id;
    int cost;
    qnode(int a,int b):id(a),cost(b){}
    bool operator < (const qnode &t) const
    {
        return t.cost < cost;
    }
};
struct edge{
    int v,next,w;
}e[100100],re[100100];
void add(int a,int b,int c)
{
    e[idx].v = b;e[idx].w = c;
    e[idx].next = first[a];
    first[a]=idx++;
}
void radd(int a,int b,int c)
{
    re[ridx].v=b;re[ridx].w=c;
    re[ridx].next = rfirst[a];
    rfirst[a]=ridx++;
}
void dijkstra(int x)
{
    priority_queue<qnode> q;
    for(int i = 1;i <= n;i++){
        vis[i]=0;
        dist[i]=INF;
    }
    dist[x]=0;
    q.push(qnode(x,0));
    while(!q.empty()){
        qnode cur = q.top();
        q.pop();
        if(vis[cur.id]) continue;
        vis[cur.id] = 1;
        for(int i = rfirst[cur.id];i!=-1;i=re[i].next){
            if(dist[re[i].v]>dist[cur.id]+re[i].w){
                dist[re[i].v] = dist[cur.id]+re[i].w;
                q.push(qnode(re[i].v,dist[re[i].v]));
            }
        }
    }
}

int A_star(int start,int end,int k)
{
    memset(times,0,sizeof(times));
    priority_queue<node> q;
    node t1;
    t1.g = t1.h = 0;
    t1.p = start;
    q.push(t1);
    while(!q.empty()){
        node t = q.top();
        q.pop();
        times[t.p]++;
        if(times[t.p]==k&&t.p==end) return t.h+t.g;
        if(times[t.p]>k) continue;
        for(int i = first[t.p];i!=-1;i=e[i].next){
            node tmp;
            tmp.p = e[i].v;
            tmp.g = dist[e[i].v];
            tmp.h = e[i].w + t.h;
            q.push(tmp);
        }
    }
    return -1;
}
void init()
{
    memset(first,-1,sizeof(first));
    memset(rfirst,-1,sizeof(rfirst));
    idx = 1;
    ridx = 1;
}
int main()
{
    scanf("%d%d",&n,&m);
    init();
    for(int i = 1;i <= m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        radd(v,u,w);
    }
    scanf("%d%d%d",&start,&end,&k);
    if(start==end) k++;//若题目要求必须走动时加上
    dijkstra(end);
    int ans = A_star(start,end,k);
    printf("%d\n",ans);
    return 0;
}