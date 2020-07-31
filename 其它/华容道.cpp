//判断是否有解
int map[16],ans=0;
for(int i=0;i<16;i++){
    scanf("%d",&map[i]);
    if(!map[i])
        ans+=6-i%4-i/4;
    for(int j=0;j<i;j++)
        if(map[j]>map[i])
            ans++;
}
if(ans&1)
    printf("Yes\n");
else
    printf("No\n");