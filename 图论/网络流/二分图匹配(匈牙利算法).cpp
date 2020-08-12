/*
һ��ͼ:
1.���ڲ����ڹ������ͼ��|���ƥ��|+|��С�߸���|=|E|
2.|��������|+|��С���㸲��|=|V|

����ͼ:
|���ƥ��|=|��С���㸲��|
*/
namespace BiMatch {//�������㷨��ʱ�临�Ӷ�O(V*E)
    int n;//��ߵĵ������
    struct edge {
        int u, v;
        int next;
    } e[MAXM * 2];
    int first[MAXN];
    int idx;
    int linker[];//�ұߵĵ�
    bool used[];//�ұߵĵ�

    void add(int a, int b) {
        e[idx].u = a;
        e[idx].v = b;
        e[idx].next = first[a];
        first[a] = idx++;
    }

    void init(int _n) {
        n = _n;
        fill(first, first + n + 1, -1);
        idx = 0;
    }

    bool dfs(int u) {
        for (int i = first[u]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (!used[v]) {
                used[v] = 1;
                if (linker[v] == -1 || dfs(linker[v])) {
                    linker[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

    int hungry() {
        int res = 0;
        memset(linker, -1, sizeof(linker));
        for (int u = 1; u <= n; u++) {
            memset(used, false, sizeof(used));
            if (dfs(u)) {
                res++;
            }
        }
        return res;
    }
}
BiMatch::init(n);
BiMatch::add(u, v);
ans = BiMatch::hungry();
