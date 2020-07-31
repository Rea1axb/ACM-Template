// L<=(D × x mod M )<= R
//L<=Dx-My<=R
//y==0 时直接求解 
//y !=0 时有 : Dx-R<= My <= Dx-L ,y 越小则 x 越小 
//不等式同模 D 
//得 (-R)%D <= (M%D)*y%D <= (-L)%D
// 递归求解
ll find(ll m, ll d, ll l, ll r)
{
    if (!d || l > r)
        return -1;
    if (r / d * d >= l)
        return (l - 1) / d + 1;
    ll x = find(d, m % d, ((-r) % d + d) % d, ((-l) % d + d) % d);
    if (x == -1)
        return -1;
    return (l - 1 + x * m) / d + 1;
}
int main()
{
    int n;
    ll x, y, m, d, l, r;
    scanf("%d", &n);
    while (n--)
    {
        scanf("%lld%lld%lld%lld", &m, &d, &l, &r);
        r = min(m - 1, r);
        printf("%lld\n", find(m, d, l, r));
    }
}
