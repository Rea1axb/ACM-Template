/*
dfn[x]:x�ڵ��ʱ�������ʾx�ڵ��dfs��
low[x]:��¼x�����еĵ��ܹ�ͨ���رߵִ�����Сʱ���

����x�ڵ�ʱ��low[x]��ʼ��Ϊ dfn[x]
��x���������������� (x, y) ���� low[x] = min(low[x], low[y])
��x��Ļر� (x, y) ���� low[x] = min(low[x], dfn[y])
ע�����ߵĸ����ǻ��ݺ��ø��º�� low[y] ���� low[x]

������(x, y), ��low[y] >= dfn[x]
˵�� y ���������е�ͨ���ر��޷��ִ� x ��������Ľڵ�
�� x ��ͼG�ĸ�㣬�ڻ���֮����ÿ�����߼��ɵõ����

��DFS�����У���һ��ջ����DFS���ϵĵ�
����⵽һ����� x ʱ
��ջ�е�Ԫ�ص�����ջ��Ԫ��Ϊ x ����������֧�ĵ�һ����

x�͵���Ԫ�ع���һ����˫��ͨ����
ע�� x ����������Ϊ������ڶ����˫��ͨ����

�ر߶Ե���ͨ����Ӱ��
*/
namespace Tarjan {
    int dfn[MAXN];
    int low[MAXN];
    stack<int> stk;
    int n;//�ڵ���
    int cnt;//˫��ͨ��������
    int cut[MAXN];//ĳ�����Ƿ��Ǹ��
    int resnum[MAXN];//ĳ����������˫��ͨ������ţ����ı����Ч��
    vector<int> res[MAXN];//˫��ͨ�����ڵĵ�
    int times;

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++times;
        stk.push(u);
        int child = 0;//��¼�ӽڵ������������жϸ��ڵ��Ƿ��Ǹ��
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!dfn[v]) {//����
                child++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    cut[u] = 1;//�õ�Ϊ���
                    cnt++;
                    res[cnt].clear();
                    while (stk.top() != u) {//u�͵���Ԫ�ع���һ����˫��ע���㲻����
                        int cur = stk.top();
                        resnum[cur] = cnt;
                        res[cnt].push_back(cur);
                        stk.pop();
                    }
                    resnum[u] = cnt;
                    res[cnt].push_back(u);
                }
            } else if (v != fa) {//�ر�
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa == -1 && child == 1)
            cut[u] = 0;//�����ڵ�ֻ��һ���ӽڵ㣬���Ǹ��
    }

    void init(int _n) {
        n = _n;
        fill(dfn, dfn + n + 1, 0);
        fill(cut, cut + n + 1, 0);
        fill(resnum, resnum + n + 1, 0);
        while(!stk.empty()) stk.pop();
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
