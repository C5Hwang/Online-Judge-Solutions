#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2 + 3 , mod = 1e9 + 7 , K = 2 ;

int n , m , c , ny ;
int A[MAX_N][MAX_N] , B[MAX_N][MAX_N] , C[MAX_N][MAX_N] , T[MAX_N][MAX_N] ;

void time_mtx(int (*A)[MAX_N] , int (*B)[MAX_N] , int n , int m) {
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j) {
			T[i][j] = 0 ;
			for (int r = 0 ; r < K ; ++r) {
				int tmp = (ll)A[i][r] * B[r][j] % mod ;
				(T[i][j] += tmp) %= mod ;
			}
		}

	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < m ; ++j)
			A[i][j] = T[i][j] ;
}

int qpow_num(int a , int t) {
	if (t == 1) return a ;

	int s = qpow_num(a , t >> 1) ;
	s = (ll)s * s % mod ;
	if (t & 1) s = (ll)s * a % mod ;

	return s ;
}

void qpow_mtx(int t) {
	if (t == 1) return ;

	qpow_mtx(t >> 1) ;
	time_mtx(C , C , 2 , 2) ;
	if (t & 1) time_mtx(C , B , 2 , 2) ;
}

int getf(int x) {
	if (x == 1) return 0 ;

	A[0][0] = 1 ; A[0][1] = 0 ;
	B[0][0] = C[0][0] = 0 ; B[1][0] = C[1][0] = 1 ;
	B[0][1] = C[0][1] = c - 1 ; B[1][1] = C[1][1] = c - 2 ;

	qpow_mtx(x - 1) ;
	time_mtx(A , C , 1 , 2) ;

	return (ll)A[0][1] * c % mod ;
}

int getphi(int x) {
	int res = x ;
	for (int i = 2 ; i * i <= x ; ++i) {
		if (x % i) continue ;
		for (; !(x % i) ; x /= i) ;
		res = res / i * (i - 1) ;
	}
	if (x > 1) res = res / x * (x - 1) ;

	return res ;
}

int getans(int x) {
	int t1 = getf(x) , t2 = getphi(n / x) ;
	t1 = (ll)t1 * t2 % mod ;
	t1 = (ll)t1 * ny % mod ;

	return t1 ;
}

int main() {
	for (; scanf("%d %d" , &n , &m) != EOF ;) {
		int ans = 0 ;
		c = m - 1 ; ny = qpow_num(n , mod - 2) ;

		for (int i = 1 ; i * i <= n ; ++i) {
			if (n % i) continue ;
			int ta = i , tb = n / i ;

			(ans += getans(ta)) %= mod ;
			if (ta != tb) (ans += getans(tb)) %= mod ;
		}

		ans = (ll)ans * m % mod ;
		printf("%d\n" , ans) ;
	}

	return 0 ;
}