//求 [i - m + 1, i]的最小值
int l = 1, r = 0;
int q[MAXN * 2];
for(int i = 1; i <= n; i++) {
    while(l <= r && q[l] < i - m + 1)
        l++;//判断条件看情况
    if (l <= r) ans = min(ans, a[q[l]);
    while(l <= r && a[q[r]] > a[i])
        r--;
    q[++r] = i;
}

deque<int> q;
for (int i = 1; i <= n; i++) {
    while (!q.empty() && q.front() < i - m + 1) {
        q.pop_front();
    }
    if (!q.empty()) ans = min(ans, a[q.front()]);
    while (!q.empty() && a[q.back()] > a[i]) {
        q.pop_back();
    }
    q.push_back(i);
}
