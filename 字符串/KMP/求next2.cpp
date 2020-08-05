const int SIZE=1e5+5;
void GetNext(string x,int m,int nextt[]){
    int i,j;
    j=nextt[0]=-1;
    i=0;
    while(i<m){
        while(-1!=j && x[i]!=x[j]){
            j=nextt[j];
        }
        if(x[++i]==x[++j]){
            nextt[i]=nextt[j];
        }
        else nextt[i]=j;
    }
}