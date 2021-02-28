//欧拉回路 or 欧拉通路

//无向图
vector<int> ans;
int visedge[MAXM * 2];
void dfs(int u) {
    for (int i = first[u]; i != -1; i = e[i].next) {
        if (visedge[i]) continue;
        visedge[i] = visedge[i ^ 1] = 1;
        dfs(e[i].v);
        ans.push_back(i);
    }
}

//有向图
vector<int> ans;
int visedge[MAXM];
void dfs(int u) {
    for (int i = first[u]; i != -1; i = e[i].next) {
        if (visedge[i]) continue;
        visedge[i] = 1;
        dfs(e[i].v);
        ans.push_back(i);
    }
}
