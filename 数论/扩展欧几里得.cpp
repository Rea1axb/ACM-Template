void exgcd(ll a,ll b,ll &g,ll &x,ll &y)//ax+by=gcd(a,b)=g
{
    if (b == 0) {
        g = a;
        x = 1;
        y = 0;
        return;
    }
    exgcd(b,a%b,g,y,x);
    y-=(a/b)*x;
}
//ax + by = c; g;

//c%g==0时有解

//x=x*c/g,y=y*c/g;
//得到特解 :(x,y)

//dx=b/g,dy=-a/g;
//得到通解 :(x+dx*n,y+dy*n);

//得到x最小正整数解 :(x%dx+dx)%dx; 
