#include <math.h>
#include <complex>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define pi acos(-1)
typedef std::complex<double> CN ;

const int MAX_N = 3e5 + 10 ;

char ch ;
CN a[MAX_N] , b[MAX_N] ;
int n , m , x , L , rev[MAX_N] , c[MAX_N] ;

void fft(CN *a , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(a[i] , a[rev[i]]) ;
	
	for (int i = 1 ; i <= L ; ++i) {
		int len = 1 << i , hl = len >> 1 ;
		CN wn(cos(ty * 2 * pi / len) , sin(ty * 2 * pi / len)) ;
		
		for (int j = 0 ; j < n ; j += len) {
			CN w(1 , 0) ;
			
			for (int k = 0 ; k < hl ; ++k) {
				CN u = a[j + k] , t = a[j + k + hl] * w ;
				a[j + k] = u + t ; a[j + k  + hl] = u - t ;
				w *= wn ;
			}
		}
	}
}

int main() {
	scanf("%d" , &n) ; --n ; getchar() ;
	for (int i = 0 ; i <= n ; ++i) {
		ch = getchar() ; x = ch - '0' ;
		a[i] = x ;
	}
	getchar() ;
	for (int i = 0 ; i <= n ; ++i) {
		ch = getchar() ; x = ch - '0' ;
		b[i] = x ;
	}
	
	///

	m = 2 * n ;
	for (n = 1 ; n <= m ; n <<= 1 , ++L) ;
	for (int i = 0 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;
	
	///
	
	fft(a , 1) ; fft(b , 1) ;
	for (int i = 0 ; i < n ; ++i) a[i] *= b[i] ;
	fft(a , -1) ;
	
	for (int i = 0 ; i <= m ; ++i) c[m - i] = (int)(a[i].real() / n + 0.5) ;
	for (int i = 0 ; i <= m ; ++i) c[i + 1] += c[i] / 10 , c[i] %= 10 ;
	if (c[m + 1]) printf("%d" , c[m + 1]) ;
	for (int i = m ; i >= 0 ; --i) printf("%d" , c[i]) ;
	printf("\n") ;
	
	return 0 ;
}
