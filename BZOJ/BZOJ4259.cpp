#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 12e5 + 10 ;
const db pi = acos(-1) , eps = 1 ;

struct CP {
	db x , y ;
	friend CP operator *(db d , CP a) {return (CP){a.x * d , a.y * d} ;}
	friend CP operator +(CP a , CP b) {return (CP){a.x + b.x , a.y + b.y} ;}
	friend CP operator -(CP a , CP b) {return (CP){a.x - b.x , a.y - b.y} ;}
	friend CP operator *(CP a , CP b) {return (CP){a.x * b.x - a.y * b.y , a.x * b.y + a.y * b.x} ;}
}A[MAX_N] , B[MAX_N] , A2[MAX_N] , B2[MAX_N] , A3[MAX_N] , B3[MAX_N] ;

bool val[MAX_N] ;
int n , m , rev[MAX_N] ;
char s1[MAX_N] , s2[MAX_N] ;

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

int main() {
	scanf("%d %d %s %s" , &n , &m , s1 , s2) ;
	for (int i = 0 ; i < n ; ++i) {
		int c = s1[i] == '*' ? 0 : s1[i] - 'a' + 1 , j = n - i - 1 ;

		A[j].x = c ; A2[j].x = c * c ; A3[j].x = c * c * c ;
	}
	for (int i = 0 ; i < m ; ++i) {
		int c = s2[i] == '*' ? 0 : s2[i] - 'a' + 1 ;

		B[i].x = c ; B2[i].x = c * c ; B3[i].x = c * c * c ;
	}

	///

	int mip = n - 1 , map = m , L = 0 ;
	m += n ; for (n = 1 ; n < m ; n <<= 1 , ++L) ;
	for (int i = 1 ; i < n ; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1)) ;

	///

	fft(A , 1) ; fft(B , 1) ; fft(A2 , 1) ; fft(B2 , 1) ; fft(A3 , 1) ; fft(B3 , 1) ;
	for (int i = 0 ; i < n ; ++i) A[i] = A3[i] * B[i] - 2.0 * A2[i] * B2[i] + A[i] * B3[i] ;
	fft(A , -1) ;

	///

	int ans = 0 ;
	for (int i = mip ; i < map ; ++i) {
		A[i].x /= n ;
		if (fabs(A[i].x) < eps) ++ans , val[i - mip + 1] = 1 ;
	}

	printf("%d\n" , ans) ;
	for (int i = 1 ; i <= map ; ++i) if (val[i]) printf("%d " , i) ;
	printf("\n") ;

	return 0 ;
}