//把读入的数据压入到一个vector中
for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    v.push_back(a[i]);
}

//把vector去重
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());

//得到映射的值
int getid(int x) {
    return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}
