struct node {
    int id;
    ll cost;
    node(int a, ll b): id(a), cost(b) {}
    bool operator < (const node &t) const {
        return t.cost < cost;
    }
};
void dijkstra(int x) {
    priority_queue<node> q;
    for(int i = 1; i <= n; i++) {
        vis[i] = 0;
        dist[i] = INF;
    }
    dist[x] = 0;
    q.push(node(x, 0));
    while(!q.empty()) {
        node cur = q.top();
        q.pop();
        if(vis[cur.id])
            continue;
        vis[cur.id] = 1;
        for(int i = first[cur.id]; i != -1; i = e[i].next) {
            if(dist[e[i].v] > dist[cur.id] + e[i].w) {
                dist[e[i].v] = dist[cur.id] + e[i].w;
                q.push(node(e[i].v, dist[e[i].v]));
            }
        }
    }
}
