#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const double pi = acos(-1) ;
const int MAX_N = 24e4 + 10 ;

struct CP {
	double x , y ;

	friend CP operator +(CP a , CP b) {return (CP){a.x + b.x , a.y + b.y} ;}
	friend CP operator -(CP a , CP b) {return (CP){a.x - b.x , a.y - b.y} ;}
	friend CP operator *(CP a , CP b) {return (CP){a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x} ;}
} ;

int n , deg , ans[MAX_N] , rev[MAX_N] ;
CP f[MAX_N] , g[MAX_N] , h[MAX_N] , t[MAX_N] ;

void fft(CP *f , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 ;
		CP wn = (CP){cos(2 * pi * ty / L) , sin(2 * pi * ty / L)} ;

		for (int i = 0 ; i < n ; i += L) {
			CP w = (CP){1 , 0} ;

			for (int j = 0 ; j < hf ; ++j , w = w * wn) {
				CP t = f[i + j + hf] * w ;
				f[i + j + hf] = f[i + j] - t ;
				f[i + j] = f[i + j] + t ;
			}
		}
	}
}

void getans(int p) {
	for (int i = 0 ; i <= deg ; ++i) {
		int tmp = (int)(t[i].x / n + 0.5) ;

		ans[i] += tmp / p ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int a , a2 , a3 ;
		scanf("%d" , &a) ; a2 = a + a ; a3 = a2 + a ;

		++f[a].x ; ++g[a2].x ; ++h[a3].x ;

		deg = std::max(deg , a3) ; ++ans[a] ;
	}

	///

	int L = 0 ; n = 1 ;
	for (; n <= deg ; n <<= 1 , ++L) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	///

	fft(f , 1) ; fft(g , 1) ; fft(h , 1) ;
	for (int i = 0 ; i < n ; ++i) t[i] = f[i] * f[i] - g[i] ;
	fft(t , -1) ; getans(2) ;

	for (int i = 0 ; i < n ; ++i)
		t[i] = f[i] * f[i] * f[i] - (CP){3 , 0} * f[i] * g[i] + (CP){2 , 0} * h[i] ;
	fft(t , -1) ; getans(6) ;

	for (int i = 0 ; i <= deg ; ++i)
		if (ans[i]) printf("%d %d\n" , i , ans[i]) ;

	return 0 ;
}