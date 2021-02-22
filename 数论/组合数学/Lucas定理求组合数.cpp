ll C(ll n, ll m) { //要求 n < mod
    if(m < 0 || m > n)
        return 0;
    else
        return fac[n] * fp(fac[n - m], mod - 2) % mod * fp(fac[m], mod - 2) % mod;
}
//通过Lucas定理转换为 n < mod 的情况
ll Lucas(ll n, ll m) { //要求mod为质数
    if(!m)
        return 1;
    else
        return C(n % mod, m % mod) * Lucas(n / mod, m / mod) % mod;
}
