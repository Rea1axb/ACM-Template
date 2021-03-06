int insert(vector<ll> &vis, ll t) {
    for (int i = MAXL; i >= 0; i--) {
        if (!t & (1ll << i)) //如果第i位为0，则跳过
            continue;
        if (!vis[i]) {
            vis[i] = t;
            return 1; //插入成功
        } else {
            t ^= vis[i];
        }
    }
    return 0; //插入失败
}

/* bitset版本 */
typedef bitset<MAXL> bi;
int insert(vector<bi> &vis, bi t) {
    for (int i = MAXL; i >= 0; i--) {
        if (!t[i])
            continue;
        if (vis[i] == 0) {
            vis[i] = t;
            return 1;
        } else {
            t ^= vis[i];
        }
    }
    return 0;
}

/* 判断01异或方程组有无解和解的个数 */
typedef bitset<MAXL> bi;
int insert(vector<bi> &vis, bi &t) {
    for (int i = MAXL; i >= 1; i--) {
        if (!t[i])
            continue;
        if (vis[i] == 0) {
            vis[i] = t;
            return 1;
        } else {
            t ^= vis[i];
        }
    }
    return 0;
}
// Ax = b
vector<bi> vis(n + 1);
bool ok = 1; //有无解
int cnt = 0; //自由元数量
for (int i = 1; i <= n; i++) {
    bi x;
    for (int j = 1 j <= n; j++) {
        x[j] = A[i][j];
    }
    x[0] = b[i];
    if (!insert(vis, x) && x == 1) { //无解
        ok = 0;
        break;
    }
    if (!insert(vis, x) && x == 0) { //自由元
        cnt++;
    }
}
int num = 1 << cnt; //解的数量
