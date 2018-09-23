#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_L = 100 + 5 , MAX_K = 2 + 5 , K = 2 , mod = 1e9 + 7 ;

int T , L , a[MAX_L] ;
ll n , f[MAX_L][2][2] , A[MAX_K][MAX_K] , B[MAX_K][MAX_K] , C[MAX_K][MAX_K] , P[MAX_K][MAX_K] ;

void times(ll (*A)[MAX_K] , ll (*B)[MAX_K] , int n , int m) {
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			P[i][j] = 0 ;
			for (int r = 0 ; r < K ; ++r) (P[i][j] += (A[i][r] * B[r][j]) % mod) %= mod ;
		}

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			B[i][j] = P[i][j] ;
}

void qpow(ll t) {
	if (t == 1) return ;

	qpow(t >> 1) ;
	times(C , C , 2 , 2) ;
	if (t & 1) times(B , C , 2 , 2) ;
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%lld" , &n) ;

		L = 0 ; ll tmp = n ;
		for (; tmp ; tmp >>= 1) a[++L] = tmp & 1 ;

		///

		f[L][1][1] = f[L][0][0] = 1 ;
		f[L][0][1] = f[L][1][0] = 0 ;

		for (int i = L - 1 ; i ; --i)
			for (int j = 0 ; j < 3 ; ++j) {
				if (!j && a[i]) {
					f[i][j][0] = f[i + 1][0][0] + f[i + 1][1][0] + f[i + 1][0][1] + f[i + 1][1][1] ;
					f[i][j][1] = 0 ;
				}
				else if (!j && !a[i]) {
					f[i][j][0] = f[i + 1][0][0] + f[i + 1][1][0] ;
					f[i][j][1] = f[i + 1][0][1] + f[i + 1][1][1] ;
				}
				else if (j && a[i]) {
					f[i][j][0] = f[i + 1][0][0] ;
					f[i][j][1] = f[i + 1][0][1] ;
				}
				else {
					f[i][j][0] = f[i + 1][0][0] ;
					f[i][j][1] = 0 ;
				}
			}

		///

		ll ans1 , ans2 ;
		A[0][0] = A[1][0] = 1 ;
		B[0][0] = B[0][1] = B[1][0] = 1 ; B[1][1] = 0 ;
		C[0][0] = C[0][1] = C[1][0] = 1 ; C[1][1] = 0 ;

		qpow(n) ; times(C , A , 2 , 1) ;

		ans1 = f[1][0][0] + f[1][0][1] + f[1][1][0] + f[1][1][1] - 1 ;
		ans2 = A[0][0] ;

		printf("%lld\n%lld\n" , ans1 , ans2) ;
	}

	return 0 ;
}