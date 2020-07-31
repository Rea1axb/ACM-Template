import java.util.*;
import java.math.*;
import java.io.*;
 
public class Main {
	public static void main(String[] args) {
		new Task().main();
	}
}
 
class fraction {
	BigInteger a, b;
 
	fraction() {
		a = BigInteger.ZERO;
		b = BigInteger.ONE;
	}
 
	fraction(BigInteger a, BigInteger b) {
		this.a = a;
		this.b = b;
	}
 
	fraction add(fraction t) {
		BigInteger d, p, q;
		p = a.multiply(t.b);
		p = p.add(t.a.multiply(b));
		q = b.multiply(t.b);
		d = p.gcd(q);
		p = p.divide(d);
		q = q.divide(d);
		return new fraction(p, q);
	}
 
	fraction substract(fraction t) {
		BigInteger p, q, d;
		p = a.multiply(t.b);
		p = p.subtract(t.a.multiply(b));
		q = b.multiply(t.b);
		d = p.gcd(q);
		p = p.divide(d);
		q = q.divide(d);
		return new fraction(p, q);
	}
 
	fraction multiply(fraction t) {
		BigInteger p, q, d;
		p = a.multiply(t.a);
		q = b.multiply(t.b);
		d = p.gcd(q);
		p = p.divide(d);
		q = q.divide(d);
		return new fraction(p, q);
	}
 
	fraction divide(fraction t) {
		BigInteger p, q, d;
		p = a.multiply(t.b);
		q = b.multiply(t.a);
		d = p.gcd(q);
		p = p.divide(d);
		q = q.divide(d);
		return new fraction(p, q);
	}
 
	fraction abs() {
		return new fraction(a.abs(), b.abs());
	}
 
	int compareTo(fraction t) {
		t = this.substract(t);
		return t.a.compareTo(BigInteger.ZERO);
	}
 
	boolean zero() {
		return a.equals(BigInteger.ZERO);
	}
}
 
class Task {
	Scanner cin = new Scanner(System.in);
	PrintStream cout = System.out;
	fraction[][] f = new fraction[211][211];
	fraction[] x = new fraction[211];
	fraction tmp;
	BigInteger ONE = BigInteger.ONE;
	BigInteger ZERO = BigInteger.ZERO;
	fraction zero = new fraction(ZERO, ONE);
	fraction r, one = new fraction(ONE, ONE);
 
	boolean gauss(int n) {
		int i, j, k, row;
		for (i = 1; i <= n; ++i) {
			row = i;
			for (j = i + 1; j <= n; ++j) {
				if (f[row][i].abs().compareTo(f[j][i].abs()) < 0) {
					row = j;
				}
			}
			if (f[row][i].compareTo(zero) == 0) {
				return false;
			}
			if (row != i) {
				for (k = i; k <= n; ++k) {
					tmp = f[row][k];
					f[row][k] = f[i][k];
					f[i][k] = tmp;
				}
				tmp = x[row];
				x[row] = x[i];
				x[i] = tmp;
			}
			for (j = i + 1; j <= n; ++j) {
				r = f[j][i].divide(f[i][i]);
				f[j][i] = zero;
				for (k = i + 1; k <= n; ++k) {
					f[j][k] = f[j][k].substract(r.multiply(f[i][k]));
				}
				x[j] = x[j].substract(r.multiply(x[i]));
			}
		}
		for (i = n; i >= 1; --i) {
			for (j = i - 1; j >= 1; --j) {
				r = f[j][i].divide(f[i][i]);
				f[j][i] = zero;
				x[j] = x[j].substract(r.multiply(x[i]));
			}
		}
		for (i = 1; i <= n; ++i) {
			x[i] = x[i].divide(f[i][i]);
		}
		return true;
	}
 
	void main() {
		int n, i, j;
		while (cin.hasNext()) {
			n = cin.nextInt();
			for (i = 1; i <= n; ++i) {
				for (j = 1; j <= n; ++j) {
					f[i][j] = new fraction(cin.nextBigInteger(), ONE);
				}
				x[i] = new fraction(cin.nextBigInteger(), ONE);
			}
			boolean ok = gauss(n);
			if (!ok) {
				cout.println("No solution.");
			} else {
				for (i = 1; i <= n; ++i) {
					if (x[i].b.compareTo(ZERO) < 0) {
						x[i].a = x[i].a.negate();//返回负值
						x[i].b = x[i].b.negate();
					}
				}
				for (i = 1; i <= n; ++i) {
					cout.print(x[i].a);
					if (x[i].b.compareTo(ONE) != 0) {
						cout.print("/" + x[i].b);
					}
					cout.println();
				}
			}
			cout.println();
 
		}
	}
}