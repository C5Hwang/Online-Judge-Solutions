#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e6 + 10 ;

struct data {
	long long x , y ;
}queue[MAX_N] ;

int n , L , R , a[MAX_N] , b[MAX_N] ;
long long s[MAX_N] , A[MAX_N] , f[MAX_N] ;

double GetK(data a , data b) {
	return (a.y - b.y) * 1.0 / (a.x - b.x) ;
}

void push(data x) {
	while (L < R && GetK(queue[R] , queue[R - 1]) > GetK(queue[R] , x)) --R ;
	queue[++R] = x ;
}

void pop(long long k) {
	while (L < R && GetK(queue[L] , queue[L + 1]) <= k) ++L ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &b[i]) ;

	///
	
	s[0] = A[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) 
		s[i] = s[i - 1] + b[i] , A[i] = A[i - 1] + s[i] ;

	///
	
	R = -1 ; f[0] = 0 ;
	push((data){0 , 0}) ;
	for (int i = 1 ; i <= n ; ++i) {
		pop(i) ;
		f[i] = queue[L].y - queue[L].x * i + A[i - 1] + a[i] ;
		push((data){s[i] , f[i] - A[i] + (i + 1) * s[i]}) ;
	}
	printf("%lld\n" , f[n]) ;

	return 0 ;
}
