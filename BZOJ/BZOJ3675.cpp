#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e5 + 10 , INF = 0x3f3f3f3f ;

struct data {
	long long x , y ;
}queue[MAX_N] ;

int n , k , L , R , a[MAX_N] ;
long long f[MAX_N][2] , s[MAX_N] ;

double GetK(data a , data b) {
	if (a.x - b.x != 0) return (a.y - b.y) * 1.0 / (a.x - b.x) ;
	else return INF ;
}

void push(data a) {
	while (L < R && GetK(queue[R] , a) > GetK(queue[R - 1] , queue[R])) --R ;
	queue[++R] = a ;
}

void pop(long long a) {
	while (L < R && GetK(queue[L] , queue[L + 1]) >= a) ++L ;
}

int main() {
	scanf("%d %d" , &n , &k) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &a[i]) ;
	s[0] = a[0] ;
	for (int i = 1 ; i < n ; ++i) s[i] = s[i - 1] + a[i] ;

	///
	
	int nw = 0 ;
	for (int i = 0 ; i < n ; ++i) f[i][0] = 0 ;
	for (int j = 1 ; j <= k ; ++j) {
		L = 0 ; R = -1 ; nw ^= 1 ;

		for (int i = 0 ; i < n ; ++i) {
			push((data){s[i] , f[i][nw^1] - s[i] * s[i]}) ;
			pop(-s[i]) ;

			f[i][nw] = queue[L].y + queue[L].x * s[i] ;
		}
	}

	printf("%lld\n" , f[n - 1][nw]) ;

	return 0 ;
}
