#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const double pi = acos(-1) ;
const int MAX_N = 4e5 + 10 ;

struct CP {
	double x , y ;

	friend CP operator +(CP a , CP b) {return (CP){a.x + b.x , a.y + b.y} ;}
	friend CP operator -(CP a , CP b) {return (CP){a.x - b.x , a.y - b.y} ;}
	friend CP operator *(CP a , CP b) {return (CP){a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x} ;}
} ;

int n , m , rev[MAX_N] ;
CP f[MAX_N] , g[MAX_N] , h[MAX_N] , E1[MAX_N] , E2[MAX_N] ;

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
	scanf("%d" , &n) ; --n ;
	for (int i = 0 ; i <= n ; ++i) scanf("%lf" , &f[i].x) , h[n - i] = f[i] ;
	for (int i = 1 ; i <= n ; ++i) g[i].x = 1.0 / i / i ;

	///

	int L ; m = n << 1 ;
	for (L = 0 , n = 1 ; n <= m ; n <<= 1 , ++L) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	///

	fft(f , 1) ; fft(g , 1) ; fft(h , 1) ;
	for (int i = 0 ; i < n ; ++i) E1[i] = f[i] * g[i] , E2[i] = g[i] * h[i] ;
	fft(E1 , -1) ; fft(E2 , -1) ;

	m >>= 1 ;
	for (int i = 0 ; i <= m ; ++i) printf("%0.3lf\n" , (E1[i].x - E2[m - i].x) / n) ;

	return 0 ;
}