//边的计数idx从0开始，idx = 0;
ll dijkstra(int x,int y,int k)
{
    priority_queue<node> q;
    for(int i = 1;i <= cnt;i++){
        vis[i] = 0;
        dist[i] = INF;
    }
    dist[x] = 0;
    q.push(node(x,0));
    while(!q.empty()){
        node cur = q.top();
        q.pop();
        if(cur.cost>ans-e[k].w) break;  //剪枝
        if(vis[cur.id]) continue;
        vis[cur.id] = 1;
        for(int i = first[cur.id];i!=-1;i=e[i].next){
            if(i == k||i == (k^1)) continue;
            if(dist[e[i].v]>dist[cur.id]+e[i].w){
                dist[e[i].v] = dist[cur.id]+e[i].w;
                q.push(node(e[i].v,dist[e[i].v]));
            }
        }
    }
    return dist[y];
}
for(int i = 2;i <= m*2+1;i+=2){
    ans = min(ans,dijkstra(e[i].u,e[i].v,i)+e[i].w);
}
