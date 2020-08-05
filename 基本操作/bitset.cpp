/*
C++的 bitset 在 bitset 头文件中，它是一种类似数组的结构，
它的每一个元素只能是０或１，每个元素仅用１bit空间。
*/
//-------------构造方法-------------
bitset<4> bitset1;　　//无参构造，长度为４，默认每一位为０
bitset<8> bitset2(12);　　//长度为８，二进制保存，前面用０补充
string s = "100101";
bitset<10> bitset3(s);　　//长度为10，前面用０补充
char s2[] = "10101";
bitset<13> bitset4(s2);　　//长度为13，前面用０补充
cout << bitset1 << endl;　　//0000
cout << bitset2 << endl;　　//00001100
cout << bitset3 << endl;　　//0000100101
cout << bitset4 << endl;　　//0000000010101
//--------------可用函数-------------
bitset<8> foo ("10011011");

cout << foo.count() << endl;　　//5　　count函数用来求bitset中1的位数
cout << foo.size() << endl;　　 //8　　size函数用来求bitset的大小

cout << foo.test(0) << endl;　　//true　　test函数用来查下标处的元素是０还是１
cout << foo.test(2) << endl;　　//false　

cout << foo.any() << endl;　　//true　　any函数检查bitset中是否有１
cout << foo.none() << endl;　　//false　　none函数检查bitset中是否没有１
cout << foo.all() << endl;　　//false　　all函数检查bitset中是全部为１


bitset<8> foo ("10011011");

cout << foo.flip(2) << endl;　　//10011111　　flip函数传参数时，用于将参数位取反
cout << foo.flip() << endl;　　 //01100000　　flip函数不指定参数时，将bitset每一位全部取反

cout << foo.set() << endl;　　　　//11111111　　set函数不指定参数时，将bitset的每一位全部置为１
cout << foo.set(3,0) << endl;　　//11110111　　set函数指定两位参数时，将第一参数位的元素置为第二参数的值
cout << foo.set(3) << endl;　　  //11111111　　set函数只有一个参数时，将参数下标处置为１

cout << foo.reset(4) << endl;　　//11101111　　reset函数传一个参数时将参数下标处置为０
cout << foo.reset() << endl;　　 //00000000　　reset函数不传参数时将bitset的每一位全部置为０



bitset<8> foo ("10011011");

string s = foo.to_string();　　//将bitset转换成string类型
unsigned long a = foo.to_ulong();　　//将bitset转换成unsigned long类型
unsigned long long b = foo.to_ullong();　　//将bitset转换成unsigned long long类型

cout << s << endl;　　//10011011
cout << a << endl;　　//155
cout << b << endl;　　//155