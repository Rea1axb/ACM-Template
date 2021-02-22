//O(n)预处理阶乘逆元,O(1)求解，要求n<mod且mod为质数
void init(int n) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    finv[n] = fp(fac[n], mod - 2);
    for(int i = n - 1; i >= 0; i--) {
        finv[i] = finv[i + 1] * (i + 1) % mod;
    }
}
ll C(ll n, ll m) {
    if(m < 0 || m > n)
        return 0;
    return fac[n] * finv[n - m] % mod * finv[m] % mod;
}
