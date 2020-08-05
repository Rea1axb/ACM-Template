//---------------data.cpp----------------
int main()
{
    freopen("in","w",stdout);
    srand(time(0));
    int n,m,q;
    n = rand()%100000;
    m = rand()%100000;
    q = rand()%100000;
    printf("%d %d %d\n",n,m,q);
    for(int i = 1;i <= q;i++){
        int a = rand()%n+1;
        int b = rand()%n+1;
        int c = rand()%2;
        printf("%d %d %d\n",a,b,c);
    }
    return 0;
}

//----------------1.cpp&&2.cpp-----------------------
int main()
{
    freopen("in","r",stdin);
    freopen("1.out","w",stdout);
    //freopen("2.out","w",stdout);
    .....
}

//----------------duipai.cpp-------------------------
int main()//Windows
{
    int cases = 0;
    do{
        if(cases) printf("#%d AC\n",cases);
        cases++;
        system("data.exe > data.txt");
        system("1.exe < data.txt > 1.txt");
        system("2.exe < data.txt > 2.txt");
    }while(!system("fc 1.txt 2.txt"));
    printf("#%d WA",cases);
    return 0;
}
int main()//Linux
{
    int i;
    for (i=1;i<=1000;i++)
        {
            system("./data");
            system("./1");
            system("./2");
            printf("%d : ",i);
            if (system("diff 1.out 2.out"))
                {
                    printf("WA\n");
                    return 0;
                }
            else printf("AC\n");
        }
    return 0;
}