#define N 110
#define eps 1e-8
#define inf 0x3f3f3f3f3f3f
struct node
{
    double u, v, w;
} k[N];
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
} p[N];
double dist(point a, point b)
{
    return sqrt((a - b) * (a - b));
}
int n, pnum;
point q[N];
int top = 0;
point cross_p(point x, point y, double a, double b, double c)
//求两个点x,y和该线的交点
{
    point ans;
    double a2 = y.y - x.y;
    double b2 = x.x - y.x;
    double c2 = x.y * y.x - y.y * x.x; //连接x,y的线段的a,b,c
    ans.y = (a * c2 - a2 * c) / (a2 * b - a * b2);
    ans.x = (b * c2 - b2 * c) / (b2 * a - b * a2);
    return ans;
}
void Hpi(double a, double b, double c)
{
    top = 0;
    for (int i = 1; i <= pnum; i++)
    {
        if (a * p[i].x + b * p[i].y + c <= eps) //如果上一个边界点满足，则记录
        {
            q[++top] = p[i];
        }
        else
        {
            if (a * p[i - 1].x + b * p[i - 1].y + c <= eps) //该节点不满足，但上一节点满足
            {
                q[++top] = cross_p(p[i - 1], p[i], a, b, c); //加入两个节点的连线与该线的交点
            }
            if (a * p[i + 1].x + b * p[i + 1].y + c <= eps) //该节点不满足，但下一节点满足
            {
                q[++top] = cross_p(p[i], p[i + 1], a, b, c);
            }
        }
    }
    for (int i = 1; i <= top; i++)
        p[i] = q[i]; //将更新好的点集返回p
    p[top + 1] = p[1], p[0] = p[top];
    pnum = top;
}
bool solve(int id)
{
    p[1] = point(0, 0);
    p[2] = point(inf, 0);
    p[3] = point(inf, inf);
    p[4] = point(0, inf);
    p[0] = p[4], p[5] = p[1];
    pnum = 4; //初始边界为第一象限四个边界点，所以起始点为4个
    double a, b, c;
    for (int i = 1; i <= n; i++)
    {
        if (i != id && k[id].u <= k[i].u && k[id].v <= k[i].v && k[id].w <= k[i].w)
            return 0; //如果有人3项多比他强，肯定达不到
        if (i == id)
            continue;
        a = (k[i].u - k[id].u) / (k[id].u * k[i].u);
        b = (k[i].v - k[id].v) / (k[id].v * k[i].v);
        c = (k[i].w - k[id].w) / (k[id].w * k[i].w); //得出ax+by=c
        Hpi(a, b, c);
        if (pnum < 3)
            return 0; //如果最后交点数<3，即无法构成平面
    }
    return pnum >= 3;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &k[i].u, &k[i].v, &k[i].w);
    for (int i = 1; i <= n; i++)
    {
        if (solve(i))
            printf("Yes\n");
        else
            printf("No\n");
    }
}

