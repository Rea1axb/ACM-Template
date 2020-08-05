//atan2函数计算（时间短，精度低） 
struct point{
    double x, y;
    double angle;
    bool operator<(const point &t)
    {
        return angle < t.angle;
    }
} p[N];
bool cmp(point a, point b)
{
    if (a.angle == b.angle)
        return a.x < b.x;
    else
    {
        return a.angle < b.angle;
    }
}
for (int i = 1; i <= n; i++)
{
    cin >> p[i].x >> p[i].y;
    p[i].angle = atan2(p[i].y, p[i].x);
}
sort(a + 1, a + 1 + n, cmp);
