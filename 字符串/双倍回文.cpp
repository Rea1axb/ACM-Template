/*
    记字符串w的倒置为例如(abcd)^R=dcba，（abba)^R=abba。
    如果x能够写成w(w^R)w(w^R)的形式，则称它是一个“双倍回文"。 换句话说，若要x是双倍回文，它的长度必须是4的倍数， 而且x、x的前半部分、x的后半部分都要是回。 例如：abbaabba是一个双倍回文，而abaaba不是， 因为它的长度不是4的倍数。
    x的子串是指在x中连续的一段字符所组成的字符。 例如bc是abcd的子串，而ac不是。
    x的回文子串，就是指满足回文性质的x的子串。
    x的双倍回文子串，就是指满足双倍回文性质的x的子串。
    你的任务是，对于给定的字符串，计算它的最长双倍回文子串的长度。
*/
#define INF 0x3f3f3f3f
const int SIZE=500050;
int p[SIZE*2],q[SIZE*2];
char A[SIZE*2],str[SIZE*2];
int n;
void manacher(){
    int mx=0,id;
    for(int i=1;i<=n;i++){
        if(mx>=i)p[i]=min(mx-i,p[2*id-i]);
        else 
            p[i]=0;
        for(;str[i+p[i]+1]==str[i-p[i]];p[i]++);
        if(p[i]+i>mx)id=i,mx=p[i]+i;
    }
}
bool cmp(int a,int b){return (a-p[a])<(b-p[b]);}
int main(){
    while(~scanf("%d%s",&n,str)){
        manacher();
        int maxx=-INF;
        for(int i=0;i<n;i++)q[i]=i;
        sort(q,q+n,cmp);
        int pos=0;
        set<int>st;
        for(int i=0;i<n;i++){
            while(pos<=n&&q[pos]-p[q[pos]]<=i){
                st.insert(q[pos]);
                pos++;
            }
            set<int>::iterator it=st.upper_bound(i+p[i]/2);
            if(it!=st.begin()){
                maxx=max(maxx,(*--it-i)*4);
            }
        }
        printf("%d\n",maxx);
    }
}