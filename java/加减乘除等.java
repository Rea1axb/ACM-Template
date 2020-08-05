/*
加		a+b: a=a.add(b);
减		a-b: a=a.subtract(b); 
乘		a*b: a=a.multiply(b);
除		a/b: a=a.divide(b);
求余	    a%b: a=a.mod(b);
绝对值		abs a=a.abs();
转换		a=b: b=BigInteger.valueOf(a);
比较		a.compareTo(b)  =-1,a<b;
				   	 	        =0,a=b;
						          =1,a>b;
a.equals(b)   a==b返回ture
a.mod(b)　　//求余数即a%b
a.gcd(b) 　　//求最大公约数
a.max(b)　　//求最大值
a.min(b) 　　//求最小值
a.pow(b)　　//求a^b的大数
*/
public class Main {
	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
      	BigInteger a;
      	BigInteger b;
      	BigInteger t1=new BigInteger(1);
      	BigInteger t2=new BigInteger("12313");
      	int t=5;
      	BigInteger t3=BigInteger.valueOf(t);//t3=5;
      	BigDecimal d=new BigDecimal(5.3435345);
      	BigInteger dd=d.toBigInteger();//小数型转整形无四舍五入//d=5;
        BigInteger []s = new BigInteger[4040];//初始化一个4040的大数数组
    }
}