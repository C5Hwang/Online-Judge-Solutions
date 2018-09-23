#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const ll INF = 1e12 ;
const int MAX_N = 300 + 10 ;

int n , m , k ;
ll f[MAX_N][MAX_N][2][2][2][2] ;

ll squ(ll x) {return x * x ;}

ll getans(int n , int m , short u , short d , short l , short r) {
	if (n > m) {
		std::swap(n , m) ;
		std::swap(u , l) ; std::swap(d , r) ;
	}
	if (d > u) std::swap(u , d) ;
	if (r > l) std::swap(l , r) ;

	if (f[n][m][u][d][l][r] != -1) return f[n][m][u][d][l][r] ;

	ll ans = squ(n * m - k) ;
	if ((u + l + r) && (d + l + r))
		for (int i = 1 ; i < n ; ++i)
			ans = std::min(ans , getans(i , m , u , 0 , l , r) + getans(n - i , m , 0 , d , l , r)) ;

	if ((l + u + d) && (r + u + d))
		for (int i = 1 ; i < m ; ++i)
			ans = std::min(ans , getans(n , i , u , d , l , 0) + getans(n , m - i , u , d , 0 , r)) ;

	return (f[n][m][u][d][l][r] = ans) ;
}

int main() {
	memset(f , -1 , sizeof(f)) ;
	scanf("%d %d %d" , &n , &m , &k) ;
	
	///
	
	ll res = getans(n , m , 1 , 1 , 1 , 1) ;
	printf("%lld\n" , res) ;

	return 0 ;
}
