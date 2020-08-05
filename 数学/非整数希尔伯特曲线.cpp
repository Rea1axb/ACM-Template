const int SIZE=2e5+5;
struct node{
    string id;string name;
    bool operator < (const node &b) const {
        return id<b.id;
    }
}a[SIZE];
string f(double x,double y,double s,int dp){
    double mid = s/2;
    string ans;
    if(dp >= 1){
        if(x <= mid && y<= mid)ans = "1" + f(y,x,mid,dp-1);
        else if(x <= mid && y>mid)ans = "2" + f(x,y-mid,mid,dp-1);
        else if(x >mid && y>mid)ans="3" + f(x-mid,y-mid,mid,dp-1);
        else ans = "4" + f(mid-y,s-x,mid,dp-1);
    }
    return ans;
}
int main(){
    int n,k; //n个数，边长为k
    while(~scanf("%d %d",&n,&k)){
        int x,y;
        for(int i=1;i<=n;i++){
            string strtmp;
            cin>>x>>y>>strtmp;
            a[i].name=strtmp;
            a[i].id=f(x,y,k,30);
        }
    }
}