#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db pi = acos(-1) ;
const int MAX_N = 4e6 + 10 ;

struct CP {
	db x , y ;

	friend CP operator +(CP a , CP b) {return (CP){a.x + b.x , a.y + b.y} ;}
	friend CP operator -(CP a , CP b) {return (CP){a.x - b.x , a.y - b.y} ;}
	friend CP operator *(CP a , CP b) {return (CP){a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x} ;}
}f[MAX_N] , g[MAX_N] ;

int n , m , rev[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void fft(CP *f , int ty) {
	for (int i = 0 ; i < n ; ++i) if (i < rev[i]) std::swap(f[i] , f[rev[i]]) ;

	for (int L = 2 ; L <= n ; L <<= 1) {
		int hf = L >> 1 ;
		CP wn = (CP){cos(2 * pi * ty / L) , sin(2 * pi * ty / L)} ;

		for (int i = 0 ; i < n ; i += L) {
			CP w = (CP){1 , 0} ;
			for (int j = 0 ; j < hf ; ++j , w = w * wn) {
				CP tmp = f[i + j + hf] * w ;
				f[i + j + hf] = f[i + j] - tmp ;
				f[i + j] = f[i + j] + tmp ;
			}
		}
	}
}

int main() {
	n = read() ; m = read() ;
	for (int i = 0 ; i <= n ; ++i) f[i].x = read() ;
	for (int i = 0 ; i <= m ; ++i) g[i].x = read() ;

	///

	int L = 0 ; m += n ; n = 1 ;
	for (; n <= m ; n <<= 1 , ++L) ;
	for (int i = 0 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	fft(f , 1) ; fft(g , 1) ;
	for (int i = 0 ; i < n ; ++i) f[i] = f[i] * g[i] ;
	fft(f , -1) ;

	for (int i = 0 ; i <= m ; ++i) {
		int tmp = (int)(f[i].x / n + 0.5) ;
		printf("%d " , tmp) ;
	}
	printf("\n") ;

	return 0 ;
}