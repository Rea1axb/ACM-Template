//N 的约数之和 =(1+p1+p1^2 +……+p1^c1)*(1 +p2 + p2^2 +……+p2^c2)*…*(1+pn+pn^2 +……+pn^cn)
ll psum(ll p,int c)//psum 可求(1+pn+pn^2 +……+pn^cn)
{
    if(c==0) return 1;
    if(c&1)
    {
        return (1 + powmod(p , (c + 1) / 2) ) % mod * psum( p , (c - 1) / 2) % mod;
    }
    else
    {
        return ((1 + powmod(p , c / 2)) % mod * psum(p , c / 2 - 1) % mod + powmod(p , c)) % mod;
    }
}