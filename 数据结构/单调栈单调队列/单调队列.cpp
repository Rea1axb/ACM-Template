//求 [i - m + 1, i]的最小值
int l = 0, r = 1;
int q[N];
for(int i = 1; i <= n; i++) {
    while(l <= r && a[q[r]] > a[i])
        r--;
    q[++r] = i;
    while(l <= r && q[l] < i - m + 1)
        l++;//判断条件看情况
    ans[i] = a[q[l]];
}

deque<int> q;
for (int i = 1; i <= n; i++) {
    while (!q.empty() && a[q.back()] > a[i]) {
        q.pop_back();
    }
    q.push_back(i);
    while (!q.empty() && q.front() < i - m + 1) {
        q.pop_front();
    }
    ans[i] = a[q.front()];
}
