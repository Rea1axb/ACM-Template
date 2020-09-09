int s[N]，top = 0;
for(int i = 1; i <= n; i++) {
    while(top && a[s[top]] > a[i])
        top--;
    if(a[s[top]] == a[i])
        s[top] = i; //去重复操作，视情况而定
    else
        s[++top] = i;
}

stack<int> stk;
for (int i = 1; i <= n; i++) {
    while (!stk.empty() && a[stk.top()] > a[i]) {
        stk.pop();
    }
    if (!stk.empty() && a[stk.top()] == a[i])
        stk.pop();
    stk.push(i);
}
