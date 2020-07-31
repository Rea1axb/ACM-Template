//可求最大内接圆，最大半平面交面积
struct point{
    double x, y;
    point() {}
    point(double a, double b) { x = a, y = b; }
    point operator-(const point &t) const
    {
        return point(x - t.x, y - t.y);
    }
    double operator*(const point &t) const
    {
        return x * t.x + y * t.y;
    }
    double operator^(const point &t) const
    {
        return x * t.y - y * t.x;
    }
    double dis(const point &t)
    {
        return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
    }
} p[N], xp[N];
struct line
{
    point s, e;
    double k;
    line() {}
    line(point a, point b) { s = a, e = b, k = atan2(b.y - a.y, b.x - a.x); }
    point operator&(const line &b) const //求两直线交点
    {
        point res = s;
        double t = ((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e));
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        return res;
    }
};
double dist(point a, point b)
{
    return sqrt((a - b) * (a - b));
}
int n;
int ans_s; //相交点数
line L[N], q[N];
point ans[N]; //存点
bool cmp(line a, line b)
{
    if (fabs(a.k - b.k) <= eps)
        return ((a.s - b.s) ^ (b.e - b.s)) < 0; //平行取下
    return a.k < b.k;
}
void Hpi() //保证多边形逆时针建边
{
    int tot = 1;
    sort(L, L + n, cmp);
    for (int i = 1; i < n; i++)
    {
        if (fabs(L[i].k - L[i - 1].k) > eps)
        {
            L[tot++] = L[i];
        } //因为平行的时候，左边的线段先判断，所以可以去除无效判定
    }
    int l = 0, r = 1;
    q[0] = L[0];
    q[1] = L[1]; //模拟双端 ，每条线取左删右（顺时针建边取右删左）
    for (int i = 2; i < tot; i++)
    {
        if (fabs((q[r].e - q[r].s) ^ (q[r - 1].e - q[r - 1].s)) <= eps ||
            fabs((q[l].e - q[l].s) ^ (q[l + 1].e - q[l + 1].s)) <= eps)
            return;                                                               //半平面交不存在
        while (l < r && (((q[r] & q[r - 1]) - L[i].s) ^ (L[i].e - L[i].s)) > eps) //上一个交点在下一条线的右侧，不在半平面交上
            r--;
        while (l < r && (((q[l] & q[l + 1]) - L[i].s) ^ (L[i].e - L[i].s)) > eps) // 同上
            l++;
        q[++r] = L[i]; //加入新边
    }
    while (l < r && (((q[r] & q[r - 1]) - L[l].s) ^ (L[l].e - L[l].s)) > eps)
        r--;
    while (l < r && (((q[l] & q[l - 1]) - L[r].s) ^ (L[r].e - L[r].s)) > eps)
        l++;
    if (r <= l + 1)
        return; //如果只有2个或以下的点，构不成平面
    for (int i = l; i < r; i++)
    {
        ans[ans_s++] = q[i] & q[i + 1];
    } //ans里存交点
    ans[ans_s++] = q[l] & q[r];
}
