/*
һ�������ֱ������������bfs���
�����ı�Ȩ�и�ֵʱ���޷�������bfs
*/
int vis[MAXN];
int d[MAXN];//d[x]:�ӽڵ� x ���������� x Ϊ�����������ܹ��������Զ�ڵ�ľ���
int len;//����ֱ��
void dp(int x) {
    vis[x] = 1;
    for (int i = first[x]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (vis[v]) continue;
        dp[v];
        len = max(len, d[x] + d[v] + e[i].w);
        d[x] = max(d[x], d[v] + e[i].w);
    }
}
