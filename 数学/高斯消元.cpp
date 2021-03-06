const double EPS = 1e-8;
typedef vector<double> vec;
typedef vector<vec> mat;
//解 Ax = b
//无解或无穷多解时返回一个长度为0的数组
vec gauss_jordan(const mat& A, const vec& b) {
    int n = A.size();
    mat B(n, vec(n + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];
    for (int i = 0; i < n; i++) B[i][n] = b[i];
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i; j < n; j++) {
            if (abs(B[j][i]) > abs(B[pivot][i])) pivot = j;
        }
        swap(B[i], B[pivot]);
        if (abs(B[i][i]) < EPS) return vec();//无解或无穷多解
        for (int j = i + 1; j <= n; j++) B[i][j] /= B[i][i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (!B[j][i]) continue;
                for (int k = i + 1; k <= n; k++)
                    B[j][k] -= B[j][i] * B[i][k];
            }
        }
    }
    vec x(n);
    for (int i = 0; i < n; i++) x[i] = B[i][n];
    return x;
}

//解异或方程组
bool ok = 1; //有无解
int cnt = 0; //自由元个数
vec gauss_jordan(const mat &A, const vec &b) {
    int n = A.size();
    mat B(n, vec(n + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];
    for (int i = 0; i < n; i++) B[i][n] = b[i];
    for (int r = 0, c = 0; r < n && c < n; r++, c++) {
        int pivot = r;
        for (int i = r + 1; i < n; i++) {
            if (abs(B[i][c]) > abs(B[pivot][c])) pivot = i;
        }
        swap(B[r], B[pivot]);
        if (B[r][c] == 0) {
            r--;
            continue;
        }
        for (int i = r + 1; i < n; i++) {
            if (!B[i][c]) continue;
            for (int j = c; j <= n; j++) {
                B[i][j] ^= B[r][j];
            }
        }
    }
    vec x(n);
    for (int i = 0; i < n; i++) {
        int pos = -1;
        for (int j = 0; j < n; j++) {
            if (B[i][j]) {
                pos = j;
                break;
            }
        }
        if (pos == -1 && B[i][n] == 1) { //无解
            ok = 0;
            return vec();
        }
        if (pos == -1 && B[i][n] == 0) {
            cnt++;
            continue;
        }
        x[pos] = B[i][n];
    }
    return x;
}

//解01异或方程组
typedef bitset<MAXL> bi;
vector<bi> X(n + 1);
for (int i = 1; i <= n; i++) {
    for (int j = 1 j <= n; j++) {
        x[i][j] = A[i][j];
    }
    x[i][0] = b[i];
}
bool ok = 1; //有无解
int cnt = 0; //自由元数量
vec gauss_jordan(vector<bi> X) {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++)
            if (X[j].to_string() > X[i].to_string()) swap(X[i], X[j]);
        if (X[i] == 0) {
            //这个和后面都是自由元
            cnt = n - i + 1;
            break;
        }
        if (X[i] == 1) {
            //无解
            ok = 0;
            return vec();
        }
        for (int k = n; k > 0; k--) {
            if (X[i].test(k)) {
                for (int j = 1; j <= n; j++) {
                    if (i != j && X[j].test(k)) {
                        X[j] ^= X[i];
                    }
                }
                break;
            }
        }
    }
    vec res(n + 1);
    for (int i = 1; i <= n - cnt; i++) {
        for (int k = n; k > 0; k--) {
            if (X[i].test(k)) {
                res[k] = X[i][0];
                break;
            }
        }
    }
    return res;
}
