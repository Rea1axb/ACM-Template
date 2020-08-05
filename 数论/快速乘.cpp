ll qmul(ll x, ll y, ll mod) { // 乘法防止溢出，
  //如果不爆LL的话可以直接乘； 
  //O(1)乘法或者转化成二进制加法
 
 
    return (x * y - (long long)(x / (long double)mod * y + 1e-3) *mod + mod) % mod;
    /*
    LL ret = 0;
    while(y) {
        if(y & 1)
            ret = (ret + x) % mod;
        x = x * 2 % mod;
        y >>= 1;
    }
    return ret;
    */
}