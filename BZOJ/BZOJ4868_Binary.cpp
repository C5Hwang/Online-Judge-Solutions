#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 ;

int n , m ;
long long A , B , C , a[MAX_N] , b[MAX_N] , sa[MAX_N] , sb[MAX_N] ;

long long find(long long *a , int n , long long x) {
	long long L = -1 , R = n ;
	while (L + 1 < R) {
		int mid = (L + R) >> 1 ;

		if (x > a[mid]) L = mid ;
		else R = mid ;
	}

	return L ;
}

int main() {
	scanf("%lld %lld %lld %d %d" , &A , &B , &C , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) scanf("%lld" , &a[i]) ;
	for (int i = 0 ; i < m ; ++i) scanf("%lld" , &b[i]) ;

	///
	
	std::sort(a + 0 , a + n) ;
	std::sort(b + 0 , b + m) ;
	sa[0] = a[0] ; sb[0] = b[0] ;
	for (int i = 1 ; i < n ; ++i) sa[i] = sa[i - 1] + a[i] ;
   	for (int i = 1 ; i < m ; ++i) sb[i] = sb[i - 1] + b[i] ;

	///
	
	long long res = -1 , maxb = b[m - 1] ;
	for (long long i = 0 ; i <= maxb ; ++i) {
		long long p1 = find(a , n , i) , p2 = find(b , m , i) ;

		///

		long long c1 , c2 ;
		if (C == 1e16 && p1 > -1) break ;

		if (p1 > -1) c1 = ((p1 + 1) * i - sa[p1]) * C ;
		else c1 = 0 ;

		if (res != -1 && c1 > res) continue ;

		///

		long long s1 , s2 ;
		if (p2 > -1) s1 = (sb[m - 1] - sb[p2]) - (m - p2 - 1) * i , s2 = (p2 + 1) * i - sb[p2] ;
		else s1 = sb[m - 1] - m * i , s2 = 0 ;

		if (B <= A) c2 = s1 * B ;
		else {
			if (s1 > s2) c2 = s2 * A + (s1 - s2) * B ;
			else c2 = s1 * A ;
		}

		if (res != -1 && c2 > res) continue ;

		///

		long long cost = c1 + c2 ;
		if (res == -1) res = cost ;
		else res = std::min(res , cost) ;
	}

	printf("%lld\n" , res) ;

	return 0 ;
}
