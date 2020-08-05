const int SIZE=1e5+5;
//x 为要处理的字串， m 为长度 ，nextt 为next数组
void GetNext(string x,int m,int nextt[]){
    int i,j;
    j=nextt[0]=-1;
    i=0;
    while(i<m){
        while(-1!=j && x[i]!= x[j]){
            j=nextt[j];
        }
        nextt[++i]=++j;
    }
}