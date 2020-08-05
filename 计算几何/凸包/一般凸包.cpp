bool cmp(point a, point b)
{
    double f = (a - xp[0]) ^ (b - xp[0]); //与左下边界点的极角
    if (fabs(f) < eps)
        return a.x - xp[0].x < b.x - xp[0].x; //相等按距离排序
    else if (f > 0)
        return true;
    else
        return false;
}
void graham()
{
    for (int i = 0; i < pnum; i++) //pnum为内部点的数目
    {
        if (xp[i].y < xp[0].y || (xp[i].y == xp[0].y && xp[i].x < xp[0].x)) //找到左下方点
            swap(xp[0], xp[i]);
    }
    sort(xp + 1, xp + pnum, cmp);
    if (pnum == 1)
        stack[0] = 0, top = 0; //建栈 找凸包
    else if (pnum == 2)
        stack[0] = 0, stack[1] = 1, top = 1;
    else //内树大于三个
    {
        stack[0] = 0, stack[1] = 1;
        top = 1;
        for (int i = 2; i < pnum; i++)
        {
            while (top > 0 && ((xp[stack[top]] - xp[stack[top - 1]]) ^ (xp[i] - xp[stack[top - 1]])) <= 0) //栈顶的点在当前点和前一个点的连线左侧
            {
                top--;
            }
            stack[++top] = i;
        }
    }
} ///栈里为从左下开始的组成凸包的点
