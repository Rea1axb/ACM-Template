/*
���ϱ����ı����Ƕ����Ʋ��
*/
const int DEG = 20;
int deg[MAXN];//������
int fa[MAXN][DEG];//��ͬ�����ʾ�����岻һ���������޸ģ������ʾ���ĵ�2^i�����ȡ�
void init() {
    fill(deg, deg + n + 1, 0);
}
void bfs(int root) {
    deg[root] = 1;
    queue<int> q;
    q.push(root);
    fa[root][0] = root;//���¸��ڵ�ĵ�һ������
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 1; i < DEG; i++) {
            fa[cur][i] = fa[fa[cur][i-1]][i-1];//���ݵ�һ�����ȣ��𲽸��µ�2^i������
        }
        for (int i = first[cur]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (deg[v]) continue;
            deg[v] = deg[cur] + 1;
            fa[v][0] = cur;//����v�ĵ�һ�����ȣ���ͬ����ĸ��·�ʽ��ͬ
            q.push(v);
        }
    }
}

/*
k�����Ȳ�ѯ
*/
int kthfa(int u, int k) {
    int bit = 0;
    while (k) {
        if (k & 1) u = fa[u][bit];
        k >>= 1;
        bit++;
    }
    return u;
}

/*
���ӣ���ʼʱ���е����ǽڵ� u ��Ȩֵ���� u �� v ��·���У����һ�����Ȩֵ��������
��������������е������ʸ��µĴ�����
*/
const int DEG = 20;
int deg[MAXN];
int fa[MAXN][DEG];//��ʾ�ӽڵ����ϣ��� 2^i ���ȸýڵ�Ȩֵ��ĵ�
void bfs(int root) {
    deg[root] = 1;
    queue<int> q;
    q.push(root);
    fa[root][0] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 1; i < DEG; i++) {
            fa[cur][i] = fa[fa[cur][i-1]][i-1];
        }
        for (int i =first[cur]; i != -1; i = e[i].next) {
            int v = e[i].v;
            if (deg[v]) continue;
            deg[v] = deg[cur] + 1;
            if (val[v] < val[cur]) {
                fa[v][0] = cur;
            } else {
                int x = cur;
                for (int j = DEG - 1; j >= 0; j--) {
                    if (fa[x][j] > 0 && val[fa[x][j]] <= val[v]) {
                        x = fa[x][j];
                    }
                }
                fa[v][0] = fa[x][0];
            }
            q.push(v);
        }
    }
}
bfs(1);
int x = u;
int ans = 0;
for (int i = DEG - 1; i >= 0; i--) {
    if (deg[fa[x][i]] >= deg[v]) {
        x = fa[x][i];
        ans += (1 << i);
    }
}
cout<<ans;
