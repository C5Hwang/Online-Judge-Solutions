#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define ldb long double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ldb pi = acos(-1) ;
const ll INF = 5e18 , ost = 5e3 ;
const int MAX_N = 3e4 + 10 , MAX_L = 12e4 + 10 ;

struct CP {
	ldb x , y ;

	friend CP operator +(CP a , CP b) {return (CP){a.x + b.x , a.y + b.y} ;}
	friend CP operator -(CP a , CP b) {return (CP){a.x - b.x , a.y - b.y} ;}
	friend CP operator *(CP a , CP b) {return (CP){a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x} ;}
}f1[MAX_L] , g1[MAX_L] , f2[MAX_L] , g2[MAX_L] ;

int m , rev[MAX_L] ;
int n , t1 , t2 ;
ll fs[MAX_N] , zs[MAX_N] , r1[MAX_N] , r2[MAX_N] , res[MAX_N] , tmp[MAX_L] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void fft(CP *f , int ty) {
	for (int i = 0 ; i < m ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= m ; L <<= 1) {
		int hf = L >> 1 ;
		CP wn = (CP){cos(2 * pi * ty / L) , sin(2 * pi * ty / L)} ;

		for (int i = 0 ; i < m ; i += L) {
			CP w = (CP){1 , 0} ;
			for (int j = 0 ; j < hf ; ++j , w = w * wn) {
				CP tmp = f[i + j + hf] * w ;
				f[i + j + hf] = f[i + j] - tmp ;
				f[i + j] = f[i + j] + tmp ;
			}
		}
	}
}

void work(int n) {
	int L = 0 ;
	for (m = 1 ; m <= n ; m <<= 1 , ++L) ;
	for (int i = 0 ; i < m ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	fft(f1 , 1) ; fft(f2 , 1) ; fft(g1 , 1) ; fft(g2 , 1) ;
	for (int i = 0 ; i < m ; ++i) {
		CP t1 = f1[i] * g1[i] , t2 = f1[i] * g2[i] , t3 = f2[i] * g1[i] , t4 = f2[i] * g2[i] ;
		f1[i] = t1 ; f2[i] = t2 ; g1[i] = t3 ; g2[i] = t4 ;
	}
	fft(f1 , -1) ; fft(f2 , -1) ; fft(g1 , -1) ; fft(g2 , -1) ;

	for (int i = 0 ; i < m ; ++i) {
		ll t1 = (ll)(f1[i].x / m + 0.5) , t2 = (ll)(f2[i].x / m + 0.5) ;
		ll t3 = (ll)(g1[i].x / m + 0.5) , t4 = (ll)(g2[i].x / m + 0.5) ;

		tmp[i] = ost * ost * t1 + ost * (t2 + t3) + t4 ;
	}
}

int main() {
	freopen("graph.in" , "r" , stdin) ;
	freopen("graph.out" , "w" , stdout) ;

	n = read() ;
	for (int i = 0 ; i < n ; ++i) {
		int a = read() ;
		if (a < 0) fs[++t1] = -a ;
		else zs[++t2] = a ;
	}

	///

	std::sort(fs + 1 , fs + 1 + t1) ;
	std::sort(zs + 1 , zs + 1 + t2) ;

	if (!t1) {
		for (int i = 1 ; i <= t2 ; ++i) fs[i] = zs[i] ;
		t1 = t2 ; t2 = 0 ;
	}

	///

	//fs * fs
	if (t1 >= 2) {
		for (int i = 2 ; i <= t1 ; ++i)
			f1[i - 2].x = g1[i - 2].x = fs[i] / ost , f1[i - 2].y = g1[i - 2].y = 0 ,
			f2[i - 2].x = g2[i - 2].x = fs[i] % ost , f2[i - 2].y = g2[i - 2].y = 0 ;

		work(t1 << 1) ;
		for (int i = 0 ; i < t1 - 1 ; ++i) r1[i + 2] = tmp[i] >> 1 ;

		res[1] = 0 ; res[2] = fs[1] * fs[2] ;
		for (int i = 3 ; i <= t1 ; ++i) {
			res[i] = res[i - 1] + fs[1] * fs[i] ;
			if (!(i & 1)) res[i] = std::min(res[i] , r1[i - 1] + fs[1] * fs[i]) ;
		}
		res[1] = fs[1] * fs[2] ;
	}

	//fs * zs
	for (int i = 0 ; i < m ; ++i)
		f1[i].x = f1[i].y = g1[i].x = g1[i].y = 0 ,
		f2[i].x = f2[i].y = g2[i].x = g2[i].y = 0 ;
	for (int i = t1 - 1 ; i ; --i)
		f1[t1 - 1 - i].x = fs[i] / ost , f1[t1 - 1 - i].y = 0 ,
		f2[t1 - 1 - i].x = fs[i] % ost , f2[t1 - 1 - i].y = 0 ;
	for (int i = 1 ; i <= t2 ; ++i)
		g1[i - 1].x = zs[i] / ost , g1[i - 1].y = 0 ,
		g2[i - 1].x = zs[i] % ost , g2[i - 1].y = 0 ;

	work(n) ; r2[t1] = 0 ;
	for (int i = 0 ; i < t1 - 1 ; ++i) r2[t1 - 1 - i] = tmp[i] ;
	for (int i = 2 ; i <= t2 ; ++i) zs[i] += zs[i - 1] ;

	ll ans = INF ;
	for (int i = 0 ; i < std::min(t2 , t1) ; ++i) {
		int j = t1 - i ;
		ll tmp = res[j - 1] - fs[t1] * (zs[t2] - zs[i]) - r2[j] ;

		ans = std::min(tmp , ans) ;
	}

	///

	if (!t2) printf("%lld\n" , res[t1]) ;
	else printf("%lld\n" , ans) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}