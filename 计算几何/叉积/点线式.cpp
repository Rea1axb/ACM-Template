struct point{
	double x,y;
};//点
struct line{
	point a,b;
};//线
double cross(point a,point b,point c)//叉积
{
	return (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x-b.x);
}//小于0说明c在ab右侧

