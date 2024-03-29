//凸函数求最大值
ll ans = 0;
while (l < r) { //zbyk
    ll lmid = (l + r) >> 1, rmid = (lmid + r) >> 1;
    ll lans = cal(lmid), rans = cal(rmid);
    if (lans >= rans) {
        r = rmid;
        ans = max(lans, ans);
    } else {
        l = lmid;
        ans = max(rans, ans);
    }
}


//凹函数求最小值
ll ans = INF;
while (l < r) {
    ll lmid = (l + r) >> 1, rmid = (lmid + r) >> 1;
    ll lans = cal(lmid), rans = cal(rmid);
    if (lans <= rans) {
        r = rmid;
        ans = min(lans, ans);
    } else {
        l = lmid;
        ans = min(rans, ans);
    }
}
