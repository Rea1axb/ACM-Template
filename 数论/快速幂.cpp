ll qpow(ll m, ll k) {
    ll res = 1, t = m % mod;
    while (k) {
        if (k&1) res = res * t % mod;
        t = t * t % mod;
        k >>= 1;
    }
    return res;
}
