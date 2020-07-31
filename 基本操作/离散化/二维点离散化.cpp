#define ll long long
const int SIZE=1e5;
struct point{
    ll x,y;
}p[SIZE];
bool cmp_x(point a,point b){return a.x < b.x;}
bool cmp_y(point a,point b){return a.y < b.y;}
void Discrete(int n){//n个点,下标[1,n]
    sort(p+1,p+n+1,cmp_x);
    int last=p[1].x,num=1;
    p[1].x = num = 1;
    for(int i=2;i<=n;i++){
        if(p[i].x == last)p[i].x=num;
        else{
            last = p[i].x;
            p[i].x=++num;
        }
    }
    sort(p+1,p+n+1,cmp_y);
    last=p[1].y,num=1;
    p[1].y=num=1;
    for(int i=2;i<=n;i++){
        if(p[i].y == last)p[i].y=num;
        else{
            last=p[i].y;
            p[i].y=++num;
        }
    }
}