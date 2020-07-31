typedef unsigned long long ull;
namespace hash{
    const ull seed = 31;
    ull base[SIZE],hash[SIZE];
    void init(){
        base[0]=1;
        for(int i=1;i<SIZE;i++)base[i]=base[i-1]*seed;
    }

    ull _hash(int l,int r){
        return hash[r]-hash[l-1]*base[r-l+1];
    }

    void getHash(char str[],int len){
        for(int i = 1;i <= len;i++)hash[i] = hash[i-1]*seed + str[i]-'a';
    }
};