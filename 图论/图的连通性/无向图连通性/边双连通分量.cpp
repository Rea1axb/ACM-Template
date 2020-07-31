/*
dfn[x]:x�ڵ��ʱ�������ʾx�ڵ��dfs��
low[x]:��¼x�����еĵ��ܹ�ͨ���رߵִ�����Сʱ���

������(x, y)����low[x] > dfn[x]
˵�� y ���޷�ͨ����������ıߵ��� y ��������ĵ�
������(x, y)Ϊ�ţ�����1��
�Ե��£����ڵݹ��������low[x] == dfn[x]
Ҳ����˵�����븸�ڵ����ӵ�����Ϊ�ţ�����2��
���Ŵ���ɾ�����ʣ�µ�ͼ����ÿ����˫��ͨ����

����˫��ͨ���������ر�ʱ��������Ϊ�����򸸽ڵ�Ͳ����ж�
��Ϊ�����ڵ�ı�Ҳ�����ǻرߣ���Ҫ�ж��Ƿ��������ͬһ����
�ڽ�ͼʱ�������ת��Ϊ���������ʱ��¼�����ڵı�id
�����򸸽ڵ�ıߺ�����id����ͬ��ʱ��˵���ı��ǻر�
*/
namespace Tarjan {
int dfn[MAXN];
int low[MAXN];
stack<int> stk;
int n;//�ڵ���
int cnt;//˫��ͨ��������
int cutedge[MAXM * 2];//ĳ�����Ƿ�����
int resnum[MAXN];//ĳ����������˫��ͨ�������
vector<int> res[MAXN];//����ͨ�����ڵĵ�
int times;

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++times;
    stk.push(u);
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (!dfn[v]) {//����
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) {
                cutedge[i] = cutedge[i ^ 1] = 1;//�ñ�Ϊ��
            }
        } else if (v != fa) {//�ر�,������ر߼�¼��Ӧ���ǵ���õ������
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
