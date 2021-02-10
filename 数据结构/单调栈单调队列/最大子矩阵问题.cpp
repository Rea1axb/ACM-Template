#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    int n;
    scanf("%d", &n);
    vector<ll> h(n + 2, 0), w(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &h[i], &w[i]);
    }
    stack<ll> stk;
    stk.push(0);
    ll ans = 0;
    for (int i = 1; i <= n + 1; i++) {
        int cur = stk.top();
        if (h[i] > h[cur]) {
            stk.push(i);
        } else {
            ll sum = 0;
            while (!stk.empty() && h[i] <= h[cur]) {
                sum += w[cur];
                ans = max(ans, sum * h[cur]);
                stk.pop();
                if (!stk.empty()) cur = stk.top();
            }
            stk.push(i);
            w[i] += sum;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
