__builtin_popcount(unsigned int n) //该函数时判断n的二进制中有多少个1

__builtin_parity(unsigned int n) //该函数是判断n的二进制中1的个数的奇偶性

__builtin_ffs(unsigned int n) //该函数判断n的二进制末尾最后一个1的位置，从一开始
int n = 1;//1
int m = 8;//1000
cout<<__builtin_ffs(n)<<endl;//输出1
cout<<__builtin_ffs(m)<<endl;//输出4

__builtin_ctz(unsigned int n) //该函数判断n的二进制末尾后面0的个数，当n为0时，和n的类型有关

__builtin_clz(unsigned int x) //__builtin_clz (unsigned int x)
int n = 1;
int m = 2;
cout<<__builtin_clz(n)<<endl;//输出31
cout<<__builtin_clz(m)<<endl;//输出30
