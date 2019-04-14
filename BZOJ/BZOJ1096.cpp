#include <stdio.h>
#include <stdlib.h>

#define db double
#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-6 ;
const int MAX_N = 1e6 + 10 ;

struct data {ll x , y ;}que[MAX_N] ;

ll SP[MAX_N] , S[MAX_N] , f[MAX_N] ;
int n , L , R , X[MAX_N] , P[MAX_N] , C[MAX_N] ;

db getk(data a , data b) {
	return (a.y - b.y) * 1.0 / (a.x - b.x) ;
}

void push(data a) {
	for (; L < R && getk(que[R] , a) - getk(que[R] , que[R - 1]) < eps ; --R) ;
	que[++R] = a ;
}

void pop(int k) {
	for (; L < R && getk(que[L] , que[L + 1]) - k < eps ; ++L) ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d %d %d" , &X[i] , &P[i] , &C[i]) ;

	///

	SP[0] = S[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		S[i] = S[i - 1] + (ll)X[i] * P[i] , SP[i] = SP[i - 1] + P[i] ;

	L = 1 ; R = 0 ; push((data){0 , 0}) ;
	for (int i = 1 ; i <= n ; ++i) {
		pop(X[i]) ;
		f[i] = C[i] + SP[i] * X[i] - S[i] + que[L].y - X[i] * que[L].x ;

		push((data){SP[i] , f[i] + S[i]}) ;
	}

	printf("%lld\n" , f[n]) ;

	return 0 ;
}