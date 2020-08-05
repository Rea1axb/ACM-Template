//给定y,z,p，计算满足Y^x = Z(mod P)的最小非负整数
ll bsgs(ll a, ll b, ll p)
{
    map<int, int> H;
    H.clear();
    b %= p;
    int t = (int)sqrt(p) + 1;
    for (int i = 0; i < t; i++)
    {
        int val = (ll)b * powmod(a, i, p) % p;
        H[val] = i;
    }
    a = powmod(a, t, p);
    if (!a)
        return b ? -1 : 1;
    for (int i = 0; i <= t; i++)
    {
        int val = powmod(a, i, p);
        int j = H.find(val) == H.end() ? -1 : H[val];
        if (j >= 0 && i * t >= j)
            return i * t - j;
    }
    return -1;
}
