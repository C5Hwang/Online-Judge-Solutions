#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_B = 30 + 5 , mod = 10086 ;

int n , BASE , q , usd , a[MAX_N] , b[MAX_B] , num[MAX_B] ;

int qpow(int x , int t) {
	int tmp = x , s = 1 ;
	for (; t ; t >>= 1 , tmp = (ll)tmp * tmp % mod)
		if (t & 1) s = (ll)s * tmp % mod ;

	return s ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &a[i]) ;
	scanf("%d" , &q) ;

	BASE = 30 ; usd = 0 ;
	for (int i = 0 ; i < n ; ++i)
		for (int j = BASE ; j >= 0 ; --j)
			if (a[i] & (1 << j)) {
				if (b[j]) a[i] ^= b[j] ;
				else {
					b[j] = a[i] ; ++usd ;
					for (int k = j - 1 ; k >= 0 ; --k) if (b[j] & (1 << k)) b[j] ^= b[k] ;
					for (int k = BASE ; k > j ; --k) if (b[k] & (1 << j)) b[k] ^= b[j] ;
					break ;
				}
			}

	usd = qpow(2 , n - usd) ;

	///

	int tot = 0 ;
	for (int j = 0 ; j <= BASE ; ++j) if (b[j]) num[j] = tot++ ;

	int kth = 0 ;
	for (int j = BASE ; j >= 0 ; --j)
		if (q & (1 << j)) q ^= b[j] , kth += (1 << num[j]) ;

	kth = (ll)usd * kth % mod ;
	printf("%d\n" , (kth + 1) % mod) ;

	return 0 ;
}