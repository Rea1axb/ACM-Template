/*
LLL优化：每次将入队节点距离和队内距离平均值比较，
如果更大则插入至队尾，否则插入队首
优化的效果很好，但是很容易被卡：只要向1连接一条权值巨大的边，LLL就失效了
*/
bool inq[MAXN];//是否在队列中
void spfa(int s)
{
    for(int i = 1;i <= n;i++){
        dist[i] = INF;
        inq[i] = 0;
    }
    int num = 0;
    ll x = 0;
    dist[s] = 0;
    deque<int> q;
    q.push_back(s);
    inq[s] = 1;
    num++;
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        num--;
        x-=dist[cur];
        while(num&&dist[cur]>x/num){
            q.push_back(cur);
            cur = q.front();
            q.pop_front();
        }
        inq[cur] = 0;
        for(int i = first[cur];i != -1;i = e[i].next){
            int v = e[i].v;
            ll w = e[i].w;
            if(dist[v]>dist[cur]+w){
                dist[v] = dist[cur]+w;
                if(!inq[v]){
                    inq[v] = 1;
                    if(!q.empty()&&dist[v]<dist[q.front()]) q.push_front(v);
                    else q.push_back(v);
                    num++;
                    x+=dist[v];
                }
            }
        }
    }
}
