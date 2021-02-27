ans[1] = a[1];
len = 1;

for (int i = 2; i <= n; ++i) {
    if (a[i] > ans[len]) {
        ans[++len] = a[i];
    } else {
        int pos = lower_bound(ans, ans + len, a[i]) - ans;
        ans[pos] = a[i];
    }
}

LIS = len;
