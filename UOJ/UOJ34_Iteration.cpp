#include <math.h>
#include <complex>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define pi acos(-1)
typedef std::complex<double> CN ;

const int MAX_N = 4e5 + 10 ;

CN a[MAX_N] , b[MAX_N] ;
int n , m , L , rex[MAX_N] ;

void fft(CN *a , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rex[i]) std::swap(a[i] , a[rex[i]]) ;

	for (int i = 1 ; i <= L ; ++i) {
		int len = (1 << i) , hl = len >> 1 ;
		CN wn(cos(ty * 2 * pi / len) , sin(ty * 2 * pi / len)) ;

		for (int j = 0 ; j < n ; j += len) {
			CN w(1 , 0) ;

			for (int k = 0 ; k < hl ; ++k) {
				CN u = a[j + k] , t = a[j + k + hl] * w ;
				a[j + k] = u + t ;
				a[j + k + hl] = u - t ;
				w *= wn ;
			}
		}
	}
}

int main() {
	int x ;
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i <= n ; ++i) scanf("%d" , &x) , a[i] = x ;
	for (int i = 0 ; i <= m ; ++i) scanf("%d" , &x) , b[i] = x ;

	///

	m += n ; for (n = 1 , L = 0 ; n <= m ; n <<= 1 , ++L) ;
	for (int i = 0 ; i < n ; ++i) rex[i] = (rex[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	///
	
	fft(a , 1) ; fft(b , 1) ;
	for (int i = 0 ; i <= n ; ++i) a[i] *= b[i] ;
	fft(a , -1) ;

	for (int i = 0 ; i <= m ; ++i)
		printf("%d " , (int)(a[i].real() / n + 0.5)) ;
	printf("\n") ;

	return 0 ;
}
