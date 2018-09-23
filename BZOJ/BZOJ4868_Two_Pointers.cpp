#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 , INF = 0x3f3f3f3f ;

long long n , m , A , B , C , a[MAX_N] , b[MAX_N] , sorta[MAX_N] , sortb[MAX_N] , sa[MAX_N] , sb[MAX_N] ;

long long read() {
	long long x = 0 , F = 1 ; char c = getchar() ;
	while (c < '0' || c > '9') {if (c == '-') F = -F ; c = getchar() ;}
	while (c >= '0' && c <= '9') x = x * 10 - '0' + c , c = getchar() ;
	return x * F ;
}

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
	long long maxa = 0 , maxb = 0 ;
	A = read() ; B = read() ; C = read() ; n = read() ; m = read() ;
	for (int i = 0 ; i < n ; ++i) {
		long long x ; x = read() ;
		maxa = std::max(maxa , x) ; ++sorta[x] ;
	}
	for (int i = 0 ; i < m ; ++i) {
		long long x ; x = read() ;
		maxb = std::max(maxb , x) ; ++sortb[x] ;
	}

	///

	n = 0 ; m = 0 ;
	for (int i = 0 ; i <= maxa ; ++i)
		for (int j = 0 ; j < sorta[i] ; ++j) a[n++] = i ;
	for (int i = 0 ; i <= maxb ; ++i)
		for (int j = 0 ; j < sortb[i] ; ++j) b[m++] = i ;

	sa[0] = a[0] ; sb[0] = b[0] ;
	for (int i = 1 ; i < n ; ++i) sa[i] = sa[i - 1] + a[i] ;
   	for (int i = 1 ; i < m ; ++i) sb[i] = sb[i - 1] + b[i] ;
	a[n] = INF ;

	///
	
	long long res = -1 , p1 = -1 , p2 = -1;
	for (long long i = 0 ; i <= maxb ; ++i)	{
		while (a[p1 + 1] < i) ++p1 ;
		while (b[p2 + 1] < i) ++p2 ;

		///

		if (C == 1e16 && p1 > -1) break ;

		long long c1 , c2 ;
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
