#pragma comment(linker, "/STACK:1024000000,1024000000")

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1
int p;
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
    for (ll i = 1; prime[i] * prime[i] <= n; i++) {
        if (n % prime[i] == 0) {
            ans -= ans / prime[i];
            while (n % prime[i] == 0)
                n /= prime[i];
        }
    }
    if (n > 1)
        ans -= ans / n;
    return ans % p;
}

ll qmi(ll m, ll k, ll p) {
    ll res = 1 % p, t = m;
    while (k) {
        if (k & 1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    sieve();
    while (T--) {
        int n;
        scanf("%d%d", &n, &p);
        ll ans = 0;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                if (i * i == n) {
                    ans = (ans + phi(n / i) * qmi(n, i - 1, p) % p) % p;
                } else {
                    ans = (ans + phi(n / i) * qmi(n, i - 1, p) % p) % p;
                    ans = (ans + phi(i) * qmi(n, n / i - 1, p) % p) % p;
                }

            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
