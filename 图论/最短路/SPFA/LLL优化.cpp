/*
LLL�Ż���ÿ�ν���ӽڵ����Ͷ��ھ���ƽ��ֵ�Ƚϣ�
����������������β������������
�Ż���Ч���ܺã����Ǻ����ױ�����ֻҪ��1����һ��Ȩֵ�޴�ıߣ�LLL��ʧЧ��
*/
bool inq[MAXN];//�Ƿ��ڶ�����
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
