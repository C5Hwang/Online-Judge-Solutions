#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_K = 50 + 10 ;

ll n ;
int k , p , r ;
int a[MAX_K][MAX_K] , b[MAX_K][MAX_K] , base[MAX_K][MAX_K] , tmp[MAX_K][MAX_K] ;

void times(int (*a)[MAX_K] , int (*b)[MAX_K] , int n , int r , int m) {
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			tmp[i][j] = 0 ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			for (int k = 1 ; k <= r ; ++k)
				tmp[i][j] = (tmp[i][j] + (ll)a[i][k] * b[k][j]) % p ;

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			a[i][j] = tmp[i][j] ;
}

void qpow(int (*a)[MAX_K] , ll n) {
	if (n == 1) return ;

	qpow(a , n >> 1) ;
	times(a , a , k , k , k) ;

	if (n % 2) times(a , base , k , k , k) ;
}

int main() {
	scanf("%lld %d %d %d" , &n , &p , &k , &r) ;
	n *= k ;

	///
	
	for (int i = 1 ; i <= k ; ++i) a[1][i] = 0 ;
	a[1][1] = 1 ;
	for (int j = 1 ; j <= k ; ++j) {
		int x = j , y = j - 1 ? j - 1 : k ;
		for (int i = 1 ; i <= k ; ++i)
			if (i == x && i == y) base[i][j] = 2 ;
			else if (i == x || i == y) base[i][j] = 1 ;
			else base[i][j] = 0 ;
	}
	for (int i = 1 ; i <= k ; ++i)
		for (int j = 1 ; j <= k ; ++j)
			b[i][j] = base[i][j] ;

	///

	qpow(b , n) ;
	times(a , b , 1 , k , k) ;

	printf("%d\n" , a[1][r + 1]) ;

	return 0 ;
}
