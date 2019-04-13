#include <stdio.h>
#include <stdlib.h>

#define db double
#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-6 ;
const int MAX_N = 5e4 + 10 ;

struct data {ll x , y ;}que[MAX_N] ;

int n , le , ri ;
ll L , a[MAX_N] , A[MAX_N] , f[MAX_N] ;

db getk(data a , data b) {
	return (a.y - b.y) * 1.0 / (a.x - b.x) ;
}

void push(data x) {
	for (; le < ri && getk(que[ri - 1] , que[ri]) - getk(que[ri] , x) > eps ; --ri) ;
	que[++ri] = x ;
}

void pop(ll k) {
	for (; le < ri && getk(que[le] , que[le + 1]) - k < eps ; ++le) ;
}

int main() {
	scanf("%d %lld" , &n , &L) ; ++L ;
	for (int i = 1 ; i <= n ; ++i) scanf("%lld" , &a[i]) ;
	A[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) A[i] = A[i - 1] + a[i] ;
	for (int i = 1 ; i <= n ; ++i) A[i] += i ;

	///

	le = 1 ; ri = 0 ; push((data){0 , 0}) ;
	for (int i = 1 ; i <= n ; ++i) {
		pop(A[i] << 1) ;
		f[i] = A[i] * A[i] + L * L - ((A[i] * L) << 1) + que[le].y - (A[i] << 1) * que[le].x ;

		push((data){A[i] , f[i] + A[i] * A[i] + ((A[i] * L) << 1)}) ;
	}

	printf("%lld\n" , f[n]) ;

	return 0 ;
}