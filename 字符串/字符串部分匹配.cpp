/*
    求a的头和b的屁股最大匹配情况
    a:riemann   b:marjorie res:rie 3
*/
const int SIZE=100050*2;
char a[SIZE],b[SIZE];
int kmp[SIZE]; //kmp为next数组
int main(){
    while(~scanf("%s%s",a,b)){
        int la=strlen(a);int lb=strlen(b);
        strcat(a,b);
        get_NEX(a);//求next方法1
        int len=la+lb;
        while(kmp[len]>la||kmp[len]>lb){
            len=kmp[len];
        }
        if(kmp[len]==0)
            printf("0\n");
        else{
            for(int i=0;i<kmp[len];i++)
                printf("%c",a[i]);
            printf(" %d\n",kmp[len]);
        }
    }
}