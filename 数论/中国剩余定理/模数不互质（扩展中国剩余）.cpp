typedef __int128 ll;
void exgcd(ll a, ll b, ll &g, ll &x, ll &y)
{
    if (b == 0)
    {
        g = a;
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, g, y, x);
    y -= (a / b) * x;
}
bool china_flag = false;
ll a1, a2, m1, m2;
ll abs(ll x) { return x > 0 ? x : -x; }
void china()
{
    ll d = a2 - a1;
    ll g, x, y;
    exgcd(m1, m2, g, x, y);
    if (d % g == 0)
    {
        x = ((x * d / g) % (m2 / g) + (m2 / g)) % (m2 / g);
        a1 = x * m1 + a1;
        m1 = (m1 * m2) / g;
    }
    else
        china_flag = true;
}
int n;
long long as[111];
long long ms[111];//mod m =a;
ll realchina()
{
    a1 = as[0];
    m1 = ms[0];
    for (ll i = 1; i < n; i++)
    {
        a2 = as[i];//输入太多可依次输入
        m2 = ms[i];
        china();
        if (china_flag)
            return -1;
    }
    return a1;
}
