#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_L = 30 + 5 , MAX_N = 2 + 3 ;

ll n ;
int k , mod , G , pri[MAX_L] , A[MAX_N][MAX_N] , S[MAX_N][MAX_N] , T[MAX_N][MAX_N] , C[MAX_N][MAX_N] ;

inline int qpow(int a , int t) {
	int s = 1 , tmp = a ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

inline void times(int (*A)[MAX_N] , int (*B)[MAX_N]) {
	for (int i = 0 ; i < 2 ; ++i)
		for (int j = 0 ; j < 2 ; ++j) {
			int s = 0 ;
			for (int r = 0 ; r < 2 ; ++r) (s += (ll)A[i][r] * B[r][j] % mod) %= mod ;
			C[i][j] = s ;
		}

	for (int i = 0 ; i < 2 ; ++i) A[i][0] = C[i][0] , A[i][1] = C[i][1] ;
}

inline void matpow(ll t) {
	S[0][0] = S[1][1] = 1 ; S[1][0] = S[0][1] = 0 ;
	for (int i = 0 ; i < 2 ; ++i) T[i][0] = A[i][0] , T[i][1] = A[i][1] ;

	for (; t ; t >>= 1 , times(T , T)) if (t & 1) times(S , T) ;
}

inline int getroot() {
	int phi = mod - 1 , tmp = phi , tot = 0 ;

	for (int i = 2 ; i * i <= phi ; ++i) {
		if (tmp % i) continue ;

		pri[tot++] = i ;
		for (; !(tmp % i) ; tmp /= i) ;
	}

	for (int i = 2 ; i < mod ; ++i) {
		bool ok = 1 ;
		for (int j = 0 ; j < tot && ok ; ++j)
			if (qpow(i , phi / pri[j]) == 1) ok = 0 ;

		if (ok) return i ;
	}
}

int main() {
	int T ; scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%lld %d %d" , &n , &k , &mod) ;
		G = getroot() ;

		int gn = qpow(G , (mod - 1) / k) , ny = qpow(k , mod - 2) , ans = 0 ;

		for (int i = 0 , g = 1 ; i < k ; ++i , g = (ll)g * gn % mod) {
			A[0][0] = (g + 1) % mod ; A[0][1] = A[1][0] = g ; A[1][1] = 1 ;

			matpow(n) ;
			(ans += S[0][0]) %= mod ;
		}
		ans = (ll)ans * ny % mod ;

		printf("%d\n" , ans) ;
	}

	return 0 ;
}