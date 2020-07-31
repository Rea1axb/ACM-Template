/*
最普通的SPFA，很有可能被卡
判环建议用dfs优化的
*/
bool inq[MAXN];//是否在队列中
int cnt[MAXN];//入队列次数
int dist[MAXN];
bool spfa(int start)
{
    queue<int> q;
    for(int i = 1;i <= n;i++){
        dist[i] = INF;
        inq[i] = 0;
        cnt[i] = 0;
    }
    dist[start] = 0;
    cnt[start] = 1;
    q.push(start);
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        inq[cur] = 0;
        for(int i = first[cur];i != -1;i = e[i].next){
            int v = e[i].v;
            int w = e[i].w;
            if(dist[v] > dist[cur] + w){
                dist[v] = dist[cur] + w;
                if(!inq[v]){
                    inq[v] = 1;
                    q.push(v);
                    if(++cnt[v] > n) return 0;
                    //若入队列次数大于n，说明存在环
                }
            }
        }
    }
    return 1;
}
