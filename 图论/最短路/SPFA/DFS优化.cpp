/*
DFS�Ż�����dfs��ջ���������
һ�������жϸ�����û����������
*/
bool vis[MAXN];
int path[MAXN];
bool spfa(int s)
{
    vis[s] = 1;
    for(int i = first[s];i!=-1;i=e[i].next){
        int v = e[i].v;
        if(v == path[s]) continue;
        ll w = e[i].w;
        if(dist[v]<dist[s]+w){
            dist[v] = dist[s] + w;
            path[v] = s;
            if(vis[v]) return 0;//�и���
            if(!spfa(v)) return 0;//�и���
        }
    }
    vis[s] = 0;
    return 1;
}
