//矩阵快速幂
struct Matrix {
    int n, m;
    ll v[MAXN][MAXN];

    Matrix(int n, int m) : n(n), m(m) {}

    void init() {
        memset(v, 0, sizeof(v));
    }

    void init1() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                v[i][j] = (i == j);
            }
        }
    }
    Matrix operator*(const Matrix B) const {
        Matrix C(n, B.m);
        C.init();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= B.m; j++) {
                ll tmp = 0;
                for (int k = 1; k <= m; k++) {
                    tmp += v[i][k] * B.v[k][j];
                }
                C.v[i][j] = tmp % mod;
                //如果mod放里面可能会被卡
                //如果放外面里面可能会爆ll
            }
        }
        return C;
    }
    //如果矩阵是稀疏矩阵，可能会卡上面这种矩阵乘法
    //稀疏矩阵的乘法用下面这种
    /*
    Matrix operator*(const Matrix B) const {
        Matrix C(n, B.m);
        C.init();
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= m; k++) {
                if (!v[i][k])
                    continue;
                for (int j = 1; j <= B.m; j++) {
                    C.v[i][j] += v[i][k] * B.v[k][j] % mod;
                    C.v[i][j] %= mod;
                }
            }
        }
        return C;
    }
    */
    Matrix operator^(ll t) {
        Matrix ans(n, n), now(n, n);
        ans.init1();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                now.v[i][j] = v[i][j];
            }
        }
        while (t) {
            if (t & 1) {
                ans = ans * now;
            }
            now = now * now;
            t >>= 1;
        }
        return ans;
    }
};
