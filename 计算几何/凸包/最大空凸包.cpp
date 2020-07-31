#define N 105
struct point{
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}

    point operator-(const point &t) const
    {
        return point(x - t.x, y - t.y);
    } // b - a :   ab
    double operator*(const point &t) const
    {
        return x * t.x + y * t.y;
    } //a * b
    double operator^(const point &t) const
    {
        return x * t.y - y * t.x;
    } //a X b
    double dis(const point &t) const
    {
        return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
    } // |a-b|
} p[N], xp[N], O;
int n, pnum;
double dp[N][N], ans;
bool cmp(const point &a, const point &b)
{
    double f = (a - O) ^ (b - O); //与左下边界点的极角
    if (f == 0)
        return O.dis(a) < O.dis(b); //相等按距离排序
    else if (f > 0)
        return true;
    else
        return false;
}

void solve()
{
    memset(dp, 0, sizeof(dp));
    sort(xp + 1, xp + pnum + 1, cmp);
    for (int i = 1; i <= pnum; i++)
    {
        int j = i - 1;
        while (j && !((xp[i] - O) ^ (xp[j] - O)))
            j--;
        bool bz = (j == i - 1); //bz==0 为当前为边，==1为当前为顶点
        while (j)
        {
            int k = j - 1;
            while (k && ((xp[i] - xp[k]) ^ (xp[j] - xp[k])) > 0)
                k--;
            double area = fabs((xp[i] - O) ^ (xp[j] - O)) / 2.0;
            if (k)
                area += dp[j][k];
            if (bz)
                dp[i][j] = area;
            ans = max(ans, area), j = k;
        }
        if (bz)
        {
            for (int j = 1; j < i; j++)
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        for (int i = 1; i <= n; i++)
        {
            O = p[i], pnum = 0;
            for (int j = 1; j <= n; j++)
            {
                if (p[j].y > p[i].y || (p[j].y == p[i].y && p[j].x > p[i].x))
                {
                    xp[++pnum] = p[j];
                }
            }
            solve();
        }
        printf("%0.1f\n", ans);
    }
}
