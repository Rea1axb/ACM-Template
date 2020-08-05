#define inf 0x3f3f3f3f
const int maxn = 1e6+5;
int ch[maxn][2];
int val[maxn],dat[maxn];
int sz[maxn],cnt[maxn];
int tot,root;
int New(int v){// 辅助函数
    val[++tot] = v;
    dat[tot] = rand();
    sz[tot] = 1;
    cnt[tot] = 1;
    return tot;
}
void pushup(int id){// 辅助函数
    sz[id] = sz[ch[id][0]] + sz[ch[id][1]] + cnt[id];
}
void build(){// 辅助函数
    root = New(-INF),ch[root][1] = New(INF);
    pushup(root);
}
void Rotate(int &id,int d){// 辅助函数
    int temp = ch[id][d ^ 1];
    ch[id][d ^ 1] = ch[temp][d];
    ch[temp][d] = id;
    id = temp;
    pushup(ch[id][d]),pushup(id);
}
void insert(int &id,int v){// 插入一个数值为v
    if(!id){
        id = New(v);return ;
    }
    if(v == val[id])cnt[id]++;
    else{
        int d = v < val[id] ? 0 : 1;
        insert(ch[id][d],v);
        if(dat[id] < dat[ch[id][d]])Rotate(id,d ^ 1);
    }
    pushup(id);
    }
void Remove(int &id,int v){// 删除一个指为v数(若有多个相同的数，因只删除一个)
    if(!id)return ;
    if(v == val[id]){
        if(cnt[id] > 1){cnt[id]--,pushup(id);return ;}
        if(ch[id][0] || ch[id][1]){
            if(!ch[id][1] || dat[ch[id][0]] > dat[ch[id][1]]){
                Rotate(id,1),Remove(ch[id][1],v);
                }
            else Rotate(id,0),Remove(ch[id][0],v);
            pushup(id);
        }
        else id = 0;
        return ;
    }
    v < val[id] ? Remove(ch[id][0],v) : Remove(ch[id][1],v);
    pushup(id);
}
int get_rank(int id,int v){// 查询v数的排名(排名定义为比当前数小的数的个数+1。 若有多个相同的数，因输出最小的排名)
    if(!id)return 0;
    if(v == val[id])return sz[ch[id][0]] + 1;
    else if(v < val[id])return get_rank(ch[id][0],v);
    else return sz[ch[id][0]] + cnt[id] + get_rank(ch[id][1],v);
}
int get_val(int id,int rank){// 查询排名为rank的数
    if(!id)return INF;
    if(rank <= sz[ch[id][0]])return get_val(ch[id][0],rank);
        else if(rank <= sz[ch[id][0]] + cnt[id])return val[id];
    else return get_val(ch[id][1],rank - sz[ch[id][0]] - cnt[id]);
}
int get_pre(int v){// 求v的前驱(前驱定义为小于v，且最大的数)
    int id = root,pre;
    while(id){
        if(val[id] < v)pre = val[id],id = ch[id][1];
        else id = ch[id][0];
    }
    return pre;
}
int get_next(int v){// 求v的后继(后继定义为大于v，且最小的数)
    int id = root,next;
    while(id){
        if(val[id] > v)next = val[id],id = ch[id][0];
        else id = ch[id][1];
    }
    return next;
}
int main(){
    build();int x;
    int shk;scanf("%d",&shk);
    while(shk--){
        int op;scanf("%d",&op);
        switch(op){
            case 1:scanf("%d",&x);insert(root,x);break;
            case 2:scanf("%d",&x);Remove(root,x);break;
            case 3:scanf("%d",&x);printf("%d\n",get_rank(root,x)-1);break;
            case 4:scanf("%d",&x);printf("%d\n",get_val(root,x+1));break;
            case 5:scanf("%d",&x);printf("%d\n",get_pre(x));break;
            case 6:scanf("%d",&x);printf("%d\n",get_next(x));break;
        }
    }
}