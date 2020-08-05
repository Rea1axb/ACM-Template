//这是将sqrt（5）精确到100位的二分			
BigDecimal d=new BigDecimal(5);
BigDecimal eps=new BigDecimal("0.00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 00000 01");//（100个0）
BigDecimal l=new BigDecimal("2.236067977499789696");
BigDecimal r=new BigDecimal("2.236067977499789697");
BigDecimal mid;
BigDecimal t1=new BigDecimal(1);
BigDecimal t2=new BigDecimal(2);
while(l.multiply(l).subtract(d).abs().compareTo(eps)==1)
{
	mid=l.add(r).divide(t2);
	if(mid.multiply(mid).compareTo(d)<0)
	{
		l=mid;
	}
	else r=mid;
}