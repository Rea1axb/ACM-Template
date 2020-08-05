/*
    求字符串的前缀是否为周期串，若是， 打印循环节的长度及循环次数；
*/
const int SIZE=1000500;
int n;char s[SIZE];
int nex[SIZE];
int main(){
    while(cin>>n&&n){//n为字符串长度
        cin>>s;
        Get_nex(s);//求next方法1
        for(int i=1;i<=n;i++){
            int tmp=i-nex[i];
            if(i%tmp==0 && i/tmp>1){
                printf("%d %d\n",i,i/tmp);
            }   
        }
        printf("\n");
    }
}