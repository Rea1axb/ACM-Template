//先求n！逆元
for(int i=n-1;i>=1;i--)
{
 	inv[i]=inv[i+1]*(i+1)%mod;
}
