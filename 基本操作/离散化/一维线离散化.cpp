//把读入的数据压入到一个vector中
vector<ll> lisan;
for (int i = 1; i <= n; i++) {
    scanf("%lld", &a[i]);
    lisan.push_back(a[i]);
}

//把vector去重
sort(lisan.begin(), lisan.end());
lisan.erase(unique(lisan.begin(), lisan.end()), lisan.end());

//得到映射的值
int getid(ll x) {
    return lower_bound(lisan.begin(), lisan.end(), x) - lisan.begin() + 1;
}
