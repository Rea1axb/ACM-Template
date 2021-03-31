/*
不支持修改
只能处理可重复贡献问题，如区间最值、区间按位与、区间按位或、区间GCD等
预处理时间 O(nlogn)
查询时间 O(1)
处理区间GCD的预处理时间为O(n(logw+logx)),查询时间为O(logw)w为值域
*/
namespace ST {
    ll f[MAXN][DEG];
    int logn[MAXN];
    int n;

    void init() {//预处理log，防止查询时影响速度
        logn[1] = 0;
        logn[2] = 1;
        for (int i = 3; i < MAXN; i++) {
            logn[i] = logn[i / 2] + 1;
        }
    }

    void solve() {
        for (int j = 1; j < DEG; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);//倍增处理
            }
        }
    }

    ll query(int l, int r) {
        int lg = logn[r - l + 1];
        return max(f[l][lg], f[r - (1 << lg) + 1][lg]);
    }

}
ST::init(); //最开始初始化，before T--
ST::n = n;
for (int i = 1; i <= n; i++)
    ST::f[i][0] = val[i];
ST::solve();
ans = ST::query(l, r);

