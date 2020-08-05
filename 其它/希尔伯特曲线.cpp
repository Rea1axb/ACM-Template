#define ll long long
int two[50];//2的次方
ll f(int n, int x, int y) {//返回第几位
    if (n == 0) return 1;
    int m = two[n-1];//1 << (n - 1);//2的n-1次方
    if (x <= m && y <= m) {
        return f(n - 1, y, x);
    }
    if (x > m && y <= m) {
        return 3LL * m * m + f(n - 1, m-y+ 1, m * 2 - x + 1); // 3LL表示ll 类型的3
    }
    if (x <= m && y > m) {
        return 1LL * m * m + f(n - 1, x, y - m);
    }
    if (x > m && y > m) {
        return 2LL * m * m + f(n - 1, x - m, y - m);
    }
}
const int SIZE=1e6+50;
struct node{                                //用于存点
    int x,y;
    ll no;
}p[SIZE];
int main() {
    int n;int k;
    scanf("%d%d",&n,&k);
    two[0]=1;                               //tow[1]=2;
    for(int i=1;i<=32;i++){
        two[i]=2*two[i-1];
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d",&p[i].y,&p[i].x);      //注意y,x的读入顺序！
        p[i].no=f(k,p[i].x,p[i].y);         //用于存点的编号
    }
}