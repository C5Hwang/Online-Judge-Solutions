#include <stdio.h>
#include <stdlib.h>

#define db double
#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-6 ;
const int MAX_N = 1e6 + 10 ;

struct data {ll x , y ;}que[MAX_N] ;

ll f[MAX_N] ;
int n , L , R , A , B , C , x[MAX_N] , S[MAX_N] ;

db getk(data a , data b) {
	return (a.y - b.y) * 1.0 / (a.x - b.x) ;
}

void push(data a) {
	for (; L < R && getk(que[R] , que[R - 1]) - getk(que[R] , a) < eps ; --R) ;
	que[++R] = a ;
}

void pop(int k) {
	for (; L < R && k - getk(que[L] , que[L + 1]) < eps ; ++L) ;
}

int main() {
	scanf("%d %d %d %d" , &n , &A , &B , &C) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d" , &x[i]) , S[i] = S[i - 1] + x[i] ;

	///

	L = 1 ; R = 0 ; push((data){0 , 0}) ;
	for (int i = 1 ; i <= n ; ++i) {
		pop((A << 1) * S[i]) ;
		f[i] = (ll)A * S[i] * S[i] + (ll)B * S[i] + C + que[L].y - ((ll)A << 1) * S[i] * que[L].x ;

		push((data){S[i] , f[i] + (ll)A * S[i] * S[i] - (ll)B * S[i]}) ;
	}

	printf("%lld\n" , f[n]) ;

	return 0 ;
}