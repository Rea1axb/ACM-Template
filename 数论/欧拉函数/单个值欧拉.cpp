//直接求
ll phi(ll n)
{
    ll ans = n;
    for (ll i = 2; i * i <= n; i++){
        if (n % i == 0){
            ans -= ans / i;         //这一步就是对应欧拉函数的通式
            while (n % i == 0)  //为了保证完全消除我们刚才得到的那个i因子。
                n /= i;            //确保我们下一个得到的i是n的素因子。
        }
    }
    if (n > 1)              //如果还有素因子没有除
        ans -= ans / n;
    return ans;
}

//先用素数筛，再用素数求欧拉函数
const int N = 40000;
bool notp[N];
int prime[N], pnum;

void sieve() {
    memset(notp, 0, sizeof(notp));
    notp[0] = notp[1] = 1;
    pnum = 0;
    for (int i = 2; i < N; i++) {
        if (!(notp[i])) prime[++pnum] = i;
        for (int j = 1; j <= pnum && prime[j] * i < N; j++) {
            notp[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

ll phi(ll n) {
    ll ans = n;
    for (int i = 1; i <= pnum && prime[i] * prime[i] <= n; i++) {
        if (n % prime[i] == 0) {
            ans -= ans / prime[i];
            while (n % prime[i] == 0)
                n /= prime[i];
        }
    }
    if (n > 1)
        ans -= ans / n;
    return ans % mod;
}
