double cross(point a, point b, point c) //AC X AB
{
    return (c - a) ^ (b - a);
}
double getarea(int n)
{
    if (n < 3)
        return 0;
    int i;
    double res = 0;
    for (i = 2; i < n; i++)
    {
        res += fabs(cross(xp[s[0]], xp[s[i - 1]], xp[s[i]]) / 2.0);
    }
    return res;
}//小于0说明c在ab右侧
