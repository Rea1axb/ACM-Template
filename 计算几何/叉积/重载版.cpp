struct point
{
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}
    point operator+(const point &t) const
    {
        return point(x + t.x, y + t.y);
    } //a + b
    point operator-(const point &t) const
    {
        return point(x - t.x, y - t.y);
    } //a - b
    double operator*(const point &t) const
    {
        return x * t.x + y * t.y;
    } //a * b
    double operator^(const point &t) const
    {
        return x * t.y - y * t.x;
    } //a X b
    double dis(const point &t)
    {
        return sqrt((x - t.x) * (x - t.x) + 
					(y - t.y) * (y - t.y));
    }
};
