/*
    给出一个字符串 问它最多由多少相同的字串组成
    ababab = 3
*/
const int SIZE=1000500;
int n;char s[SIZE];
int nex[SIZE];
int main(){
    int kase=1;
    while(cin>>s){
        if(s[0]=='.')break;
        Get_nex(s);//求next方法1
        int n=strlen(s);
        int tmp=n-nex[n];
        if(n%tmp==0 && nex[n]!=0)
            printf("%d\n",n/tmp);
        else printf("1\n");
    }
}