int pos[MAXN][MAXN];//pos[i][j]:i到j的最短路的路径的第一步
vector<int> path;//最小环路径
int ans;//最小环
//ans == INF  说明无环
void getpath(int x,int y)
{
    int tmp = pos[x][y];
    if (!tmp) {
        path.push_back(y);
        return ;
    }
    getpath(x, tmp);
    getpath(tmp, y);
}
void floyd()
{
    ans = INF;
    memcpy(dist,g,sizeof(dist));
    for(int k = 1;k <= N;k++){
        for(int i = 1;i < k;i++){
            if (g[k][i] == INF) continue;
            for(int j = i+1;j < k;j++){
                if (dist[i][j] == INF || g[k][j] == INF) continue;
                if(dist[i][j]+g[k][j]+g[i][k]<ans){
                    ans = dist[i][j]+g[k][j]+g[i][k];
                    path.clear();
                    path.push_back(i);
                    getpath(i, j);
                    path.push_back(k);
                }
            }
        }
        for(int i = 1;i <= N;i++){
            if (dist[i][k] == INF) continue;
            for(int j = 1;j <= N;j++){
                if (dist[k][j] == INF) continue;
                if(dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j] = dist[i][k]+dist[k][j];
                    pos[i][j] = k;
                }
            }
        }
    }
}
