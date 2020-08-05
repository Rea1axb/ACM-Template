const int SIZE=1e5+50;
const int col_SIZE=1e5+50;
bool col_vis[col_SIZE];
struct node{
	int l,r;int col;
}T[SIZE*3];

void build(int root,int l,int r){
	T[root].l = l;
	T[root].r = r;
	if(l == r)return ;
	int mid=(T[root].l + T[root].r)>>1;
	build(root<<1,l,mid);//注意是l（字母），不是1（数字）
	build((root<<1)+1,mid+1,r);
}
void update(int root,int l,int r,int col){
	if(T[root].l>=l && T[root].r<=r){
		T[root].col = col;return ;
	}
	else{
		if(T[root].col > 0){
			T[root<<1].col = T[root].col;
			T[(root<<1)+1].col = T[root].col;
			T[root].col = 0;
		}
		int mid = (T[root].l + T[root].r)>>1;
		if(l>mid){
			update((root<<1)+1,l,r,col);
		}
		else if(r<=mid){
			update(root<<1,l,r,col);
		}
		else{
			update(root<<1,l,mid,col);
			update((root<<1)+1,mid+1,r,col);
		}
	}
}

void Find(int root,int l,int r){
  	if(T[root].l==0 || T[root].r==0)return ;
    if(T[root].col > 0 ){
        col_vis[T[root].col] = true;
    }
    else{
        int mid = (T[ root ].l + T[ root ].r ) >> 1;
        if(l>mid){
            Find((root<<1)+1,l,r);
        }
        else if(r<=mid){
            Find(root<<1,l,r);
        }
        else{
            Find(root<<1,l,mid);
            Find((root<<1)+1,mid+1,r);
        }
    }
}
void init(int N){//N为最大的颜色
	for(int i=0;i<=N;i++){
		col_vis[i]=0;
	}
}

int tot(int l,int r,int N){//统计[l,r]内颜色范围为[1,N]共有几种
	init(N);
	Find(1,l,r);
	int tot=0;
	for(int i=0;i<=N;i++){
		if(col_vis[i])tot++;
	}
	return tot;
}
