/*
时间复杂度O(N^3)
最小权匹配只需将边权改为负值，最大匹配的负值即为答案
*/
namespace KM {
    int link_x[MAXN], link_y[MAXN], N;
    bool visx[MAXN], visy[MAXN];
    int que[MAXN << 1], top, tail, pre[MAXN];
    int cntx, cnty;
    ll hx[MAXN], hy[MAXN], slk[MAXN], mp[MAXN][MAXN];
    inline int check(int i) {
        visx[i] = true;
        if(link_x[i]) {
            que[tail++] = link_x[i];
            return visy[link_x[i]] = true;
        }
        while(i) {
            link_x[i] = pre[i];
            swap(i, link_y[pre[i]]);
        }
        return 0;
    }
    void bfs(int S) {
        for(int i = 1; i <= N; i++) {
            slk[i] = INF;
            visx[i] = visy[i] = false;
        }
        top = 0;
        tail = 1;
        que[0] = S;
        visy[S] = true;
        while(true) {
            ll d;
            while(top < tail) {
                for(int i = 1, j = que[top++]; i <= N; i++) {
                    if(!visx[i] && slk[i] >= (d = hx[i] + hy[j] - mp[i][j])) {
                        pre[i] = j;
                        if(d)
                            slk[i] = d;
                        else if(!check(i))
                            return;
                    }
                }
            }
            d = INF;
            for(int i = 1; i <= N; i++) {
                if(!visx[i] && d > slk[i])
                    d = slk[i];
            }
            for(int i = 1; i <= N; i++) {
                if(visx[i])
                    hx[i] += d;
                else
                    slk[i] -= d;
                if(visy[i])
                    hy[i] -= d;
            }
            for(int i = 1; i <= N; i++) {
                if(!visx[i] && !slk[i] && !check(i))
                    return;
            }
        }
    }
    void init(int _cntx, int _cnty) {
        cntx = _cntx, cnty = _cnty;
        N = max(cntx, cnty) + 1;
        for(int i = 1; i <= N; i++) {
            link_x[i] = link_y[i] = 0;
            visy[i] = false;
        }
        for(int i = 1; i <= N; i++) {
            hx[i] = 0;
            for(int j = 1; j <= N; j++) {
                if(hx[i] < mp[i][j])
                    hx[i] = mp[i][j];
            }
        }
    }
    ll solve() {
        ll ans = 0;
        for (int i = 1; i <= N; i++)
            bfs(i);
        for (int i = 1; i <= cntx; i++) {
            ans += mp[i][link_x[i]];
        }
        return ans;
    }
}
scanf("%d%d%d", &cntx, &cnty, &M);
for(int i=1; i<=M; i++)
{
    int u, v;
    ll w;
    scanf("%d%d%lld", &u, &v, &w);
    KM::mp[u][v] = w;
}
KM::init(cntx, cnty);
ans = KM::solve();
