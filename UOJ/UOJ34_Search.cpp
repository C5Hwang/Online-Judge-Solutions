#include <math.h>
#include <complex>
#include <stdio.h>
#include <stdlib.h>

#define pi acos(-1)
typedef std::complex<double> CN ;

const int MAX_N = 4e5 + 10 ;

int n , m ;
CN a[MAX_N] , b[MAX_N] ;

void fft(CN *a , int n  , int ty) {
	if (n == 1) return ;

	CN l[n >> 1] , r[n >> 1] ;
	for (int i = 0 ; i < n ; i += 2)
		l[i >> 1] = a[i] , r[i >> 1] = a[i + 1] ;

	///

	fft(l , n >> 1 , ty) ; fft(r , n >> 1 , ty) ;
	CN w(1 , 0) , wn(cos(ty * 2 * pi / n) , sin(ty * 2 * pi / n)) ;
	for (int i = 0 ; i < (n >> 1) ; ++i) {
		CN t = w * r[i] ;
		a[i] = l[i] + t ;
		a[i + (n >> 1)] = l[i] - t ;

		w *= wn ;
	}

}

int main() {
	int x ;
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i <= n ; ++i) scanf("%d" , &x) , a[i] = x ;
	for (int i = 0 ; i <= m ; ++i) scanf("%d" , &x) , b[i] = x ;

	m = n + m ;
	for (n = 1 ; n <= m ; n <<= 1) ;

	///
	
	fft(a , n , 1) ; fft(b , n , 1) ;
	for (int i = 0 ; i < n ; ++i) a[i] *= b[i] ;
	fft(a , n , -1) ;

	for (int i = 0 ; i <= m ; ++i)
		printf("%d " , (int)(a[i].real() / n + 0.5)) ;
	printf("\n") ;

	return 0 ;
}
