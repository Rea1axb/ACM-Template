#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define INF 0x3f3f3f3f
const int SIZE=1000+50;
int n, mp[SIZE*3][SIZE*3];
void subBuild(int xrt, int l, int r, int rt) {
    mp[xrt][rt]=0;//mp[xrt][rt]=-1;
    if(l != r) {
        int m = l + r >> 1;
        subBuild(xrt, lson);
        subBuild(xrt, rson);
    }
}
void build(int l, int r, int rt) {
    subBuild(rt, 0, n, 1);
    if(l != r) {
        int m = l + r >> 1;
        build(lson);
        build(rson);
    }
}

bool leaf;//是否是叶子结点
void subUpdate(int xrt, int y, int c, int l, int r, int rt) {
    if(l == r){
        if(leaf){
            mp[xrt][rt]+=c;
            // mp[xrt][rt]=c;
        }
        else{
            mp[xrt][rt]=mp[xrt<<1][rt]+mp[xrt<<1|1][rt];
            // mp[xrt][rt]=max(mp[xrt<<1][rt],mp[xrt<<1|1][rt]);
        }
        return ;
    }
    else {
        int m = l + r >> 1;
        if(y <= m) subUpdate(xrt, y, c, lson);
        else subUpdate(xrt, y, c, rson);
        mp[xrt][rt]=mp[xrt][rt<<1]+mp[xrt][rt<<1|1];
        // mp[xrt][rt]=max(mp[xrt][rt<<1],mp[xrt][rt<<1|1]);
    }
}
// 
void update(int x, int y, int c, int l, int r, int rt) {
    if(l==r){
        leaf=1;
        subUpdate(rt, y, c, 0, n, 1);return;
    }
    int m = l + r >> 1;
    if(x <= m) update(x, y, c, lson);
    else update(x, y, c, rson);
    leaf=0;subUpdate(rt, y, c, 0, n, 1);
}
int subQuery(int xrt, int yl, int yr, int l, int r, int rt) {
    if(yl <= l && r <= yr) return mp[xrt][rt];
    else {
        int m = l + r >> 1;
        int res=0;
        // int res=-1;
        if(yl <= m) res += subQuery(xrt, yl, yr, lson);
        // res=max(res,subQuery(xrt, yl, yr, lson));
        if(yr > m) res += subQuery(xrt, yl, yr, rson);
        // res=max(res,subQuery(xrt, yl, yr, rson));
        return res;
    }
}
// l≤xl≤xr≤r,0≤yl≤yr≤n
// 查询在(限制条件1的下界，限制条件1的上界，限制条件2的下界，限制条件2的上界，)
int query(int xl, int xr, int yl, int yr, int l, int r, int rt) {//xl<=xr,yl<=yr
    if(xl <= l && r <= xr) return subQuery(rt, yl, yr, 0, n, 1);
    else {
        int m = l + r >> 1;
        int res = 0;
        // int res=-1;
        if(xl <= m) res += query(xl, xr, yl, yr, lson);
        // res=max(res,query(xl, xr, yl, yr, lson));
        if(xr > m) res += query(xl, xr, yl, yr, rson);
        // res=max(res,query(xl, xr, yl, yr, rson))
        return res;
    }
}
