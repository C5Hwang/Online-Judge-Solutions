#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const double pi = acos(-1) ;
const int MAX_N = 3e5 + 10 ;

struct CP {
	double x , y ;

	friend CP operator +(CP a , CP b) {return (CP){a.x + b.x , a.y + b.y} ;}
	friend CP operator -(CP a , CP b) {return (CP){a.x - b.x , a.y - b.y} ;}
	friend CP operator *(CP a , CP b) {return (CP){a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x} ;}
} ;

CP f[MAX_N] , g[MAX_N] ;
int sua , sub , sua2 , sub2 ;
int n , m , len , k , a[MAX_N] , b[MAX_N] , rev[MAX_N] ;

void fft(CP *a , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(a[i] , a[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 ;
		CP wn = (CP){cos(2 * pi * ty / L) , sin(2 * pi * ty / L)} ;

		for (int i = 0 ; i < n ; i += L) {
			CP w = (CP){1 , 0} ;
			for (int j = 0 ; j < hf ; ++j , w = w * wn) {
				CP t = a[i + j + hf] * w ;
				a[i + j + hf] = a[i + j] - t ;
				a[i + j] = a[i + j] + t ;
			}
		}
	}
}

int main() {
	scanf("%d %d" , &n , &k) ; len = n - 1 ;
	for (int i = 0 ; i <= len ; ++i) scanf("%d" , &a[i]) , sua += a[i] , sua2 += a[i] * a[i] ;
	for (int i = 0 ; i <= len ; ++i) scanf("%d" , &b[i]) , sub += b[i] , sub2 += b[i] * b[i] ;

	///

	int dl = (len << 1) + 1 ;
	for (int i = len + 1 ; i <= dl ; ++i) b[i] = b[i - len - 1] ;

	for (int i = 0 ; i <= len ; ++i) f[i].x = a[len - i] ;
	for (int i = 0 ; i <= dl ; ++i) g[i].x = b[i] ;

	int L ; m = dl + len ;
	for (n = 1 , L = 0 ; n <= m ; ++L , n <<= 1) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	///

	fft(f , 1) ; fft(g , 1) ;
	for (int i = 0 ; i < n ; ++i) f[i] = f[i] * g[i] ;
	fft(f , -1) ;

	///

	int fg = (int)(f[len].x / n + 0.5) ;
	for (int i = len + 1 ; i <= dl ; ++i) {
		int tmp = (int)(f[i].x / n + 0.5) ;
		fg = std::max(tmp , fg) ;
	}

	int suc = k * k * (len + 1) + (k << 1) * (sua - sub) ;
	for (int i = 0 ; i < k ; ++i) {
		int tmp = i * i * (len + 1) + (i << 1) * (sua - sub) ;
		suc = std::min(tmp , suc) ;
	}

	ll ans = (ll)sua2 + sub2 - (fg << 1) + suc ;
	printf("%lld\n" , ans) ;

	return 0 ;
}