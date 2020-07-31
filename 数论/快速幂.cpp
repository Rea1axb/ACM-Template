ll qmi(ll m, ll k, ll p)
{
    ll res = 1 % p, t = m % p;
    while (k)
    {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
