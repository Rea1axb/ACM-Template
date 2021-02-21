inline ll add(ll a, ll b) {
	a += b;
	if (a >= mod) a -= mod;
	return a;
}

inline ll sub(ll a, ll b) {
	a -= b;
	if (a < 0) a += mod;
	return a;
}

inline ll mul(ll a, ll b) {
	return a * b % mod;
}

inline ll qpow(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b & 1) res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}

inline ll inv(ll a) {
	a %= mod;
	if (a < 0) a += mod;
	ll b = mod, u = 0, v = 1;
	while (a) {
		ll t = b / a;
		b -= t * a; swap(a, b);
		u -= t * v; swap(u, v);
	}
	assert(b == 1);
	if (u < 0) u += mod;
	return u;
}
