#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 60 + 10 , MAX_C = 20 + 10 ;

bool ap[MAX_N] ;
int tot , len , bk[MAX_N] , eg[MAX_N] ;
int sr , sg , sb , m , p , n , ny , f[MAX_C][MAX_C][MAX_C] ;

int dp() {
	memset(f , 0 , sizeof(f)) ;

	int sum = 0 ; f[0][0][0] = 1 ;
	for (int i = 0 ; i < tot ; ++i) {
		int L = bk[i] ; sum += L ;
		for (int r = 0 ; r <= sr ; ++r)
			for (int g = 0 ; g <= sg ; ++g) {
				int b = sum - r - g ;
				if (b < 0 || b > sb) continue ;

				int tmp = 0 ;
				if (r >= L) (tmp += f[r - L][g][b]) %= p ;
				if (g >= L) (tmp += f[r][g - L][b]) %= p ;
				if (b >= L) (tmp += f[r][g][b - L]) %= p ;

				f[r][g][b] = tmp ;
			}
	}

	return f[sr][sg][sb] ;
}

int qpow(int a , int t) {
	if (t == 1) return a ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % p ;
	if (t & 1) s = (ll)s * a % p ;

	return s ;
}

void dfs(int x) {
	if (ap[x]) return ;
	++len ; ap[x] = 1 ;
	dfs(eg[x]) ;
}

int main() {
	scanf("%d %d %d %d %d" , &sr , &sb , &sg , &m , &p) ;

	///

	n = sr + sb + sg ; ny = qpow((m + 1) , p - 2) ;
	tot = n ;
	for (int i = 0 ; i < n ; ++i) bk[i] = 1 ;

	///

	int ans = dp() ;
	for (int i = 0 ; i < m ; ++i) {
		tot = 0 ; memset(ap , 0 , sizeof(ap)) ;

		///

		for (int i = 1 ; i <= n ; ++i) scanf("%d" , &eg[i]) ;
		for (int i = 0 ; i <= n ; ++i) {
			if (ap[i]) continue ;
			len = 0 ; dfs(i) ;
			bk[tot++] = len ;
		}

		///

		int tmp = dp() ;
		(ans += tmp) %= p ;
	}
	ans = (ll)ans * ny % p ;

	printf("%d\n" , ans) ;

	return 0 ;
}