/*

����ͼ�߷���
�ڱ�������ͼʱ�����һ��DFS ��
����ͼ�еı߿��Ի���Ϊ
1 DFS ���ϵ�����
2 �������Ƚڵ�Ļر�
3 ����������ǰ���
4 ����������ҷ�������ϵ�ڵ�ĺ���

����ͨ��DFS ȷ������
ǰ��߶���SCC��ǿ��ͨ������ �ļ���û��Ӱ��
�ر߿��Ը������γɵ�·�����ɻ�
����(x,y) �Ƿ��������ȡ�����Ƿ���·���ܹ���y �ִ�x
�������ֻ�迼���ûرߺͺ���������low ֵ

dfn[x]:x�ڵ��ʱ�������ʾx�ڵ��dfs��
low[x]:��¼x�����еĵ��ܹ�ͨ���رߵִ�����Сʱ���

����x ��ʱ��lowx ��ʼ��Ϊdfnx������x����ջ��
��x ����������������(x; y) ����lowx = min(lowx; lowy)
��������(x; y) �����ӵ㱻���ʹ�����ջ��
�����lowx = min(lowx; dfny)
�����ݺ����lowx == dfnx ʱ����ջ��Ԫ��ֱ��x ����
����Ԫ�ع���һ��ǿ��ͨ����(���Ϊ��������)
*/
namespace Tarjan {
int dfn[MAXN];
int low[MAXN];
stack<int> stk;
int vis[MAXN];//��¼ĳ�����Ƿ�����ջ
int n;//�ڵ���
int cnt;//ǿ��ͨ��������
int resnum[MAXN];//ĳ����������ǿ��ͨ�������
vector<int> res[MAXN];//ǿ��ͨ�����ڵĵ�
int times;

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++times;
    stk.push(u);
    vis[u] = 1;
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (!dfn[v]) {//����
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        cnt++;
        while (!stk.empty()) {
            int cur = stk.top();
            resnum[cur] = cnt;
            res[cnt].push_back(cur);
            stk.pop();
            if (cur == u) break;
        }
    }
}

void init(int _n) {
    n = _n;
    fill(dfn, dfn + n + 1, 0);
    fill(cutedge, cutedge + n + 1, 0);
    fill(resnum, resnum + n + 1, 0);
    fill(vis, vis + n + 1, 0);
    while (!stk.empty()) stk.pop();
    cnt = 0;
    times = 0;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            dfs(i, -1);
    }
}
};
Tarjan::init(n);
Tarjan::solve();
