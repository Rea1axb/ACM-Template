/*
SLF优化+容错：
双端队列实现
令边权和为W（双向边要计算两次），val = sqrt(W)/100
假设从cur扩展出v,若dist[v] < dist[q.front()]+val,则将v插入队首，否则插入队尾
队列为空时直接插入队尾
*/
bool inq[MAXN];//是否在队列中
void spfa(int s)
{
    ll val = ;
    for(int i = 1;i <= n;i++){
        dist[i] = INF;
        inq[i] = 0;
    }
    dist[s] = 0;
    deque<int> q;
    q.push_back(s);
    while(!q.empty()){
        int cur = q.front();
        q.pop_front();
        inq[cur] = 0;
        for(int i = first[cur];i!=-1;i=e[i].next){
            int v = e[i].v;
            ll w = e[i].w;
            if(dist[v]>dist[cur]+w){
                dist[v] = dist[cur] + w;
                if(!inq[v]){
                    inq[v] = 1;
                    if(!q.empty()&&dist[v]>dist[q.front()]+val) q.push_back(v);
                    else q.push_front(v);
                }
            }
        }
    }
}
