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
        if (!vis[i]) {
            vis[i] = t;
            return 1;
        } else {
            t ^= vis[i];
        }
    }
    return 0;
}
