#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 , MAX_L = 20 + 5 , mod = 1e5 ;

struct data {
	int len , a[MAX_L] ;

	friend data operator +(data x , data y) {
		int ml = std::max(x.len , y.len) ;

		for (int i = 0 ; i < ml ; ++i) x.a[i] += y.a[i] ;
		for (int i = 0 ; i < ml ; ++i) x.a[i + 1] += x.a[i] / mod , x.a[i] %= mod ;

		if (x.a[ml]) x.len = ml + 1 ;
		else x.len = ml ;

		return x ;
	}
	friend data operator *(data x , int y) {
		int l = x.len ;

		for (int i = 0 ; i < l ; ++i) x.a[i] *= y ;
		for (int i = 0 ; i < l ; ++i) x.a[i + 1] += x.a[i] / mod , x.a[i] %= mod ;

		if (x.a[l]) x.len = l + 1 ;
		else x.len = l ;

		return x ;
	}
	void print() {
		printf("%d" , a[len - 1]) ;

		for (int i = len - 2 ; i >= 0 ; --i) {
			int tmp = a[i] , l = 5 ;
			for (; tmp ; tmp /= 10 , --l) ;

			for (int j = 0 ; j < l ; ++j) printf("0") ;
			printf("%d" , a[i]) ;
		}
		printf("\n") ;
	}
}ans , f[MAX_N] ;

int n ;

int main() {
	scanf("%d" , &n) ;

	f[0].len = 1 ;
	f[0].a[0] = 1 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= i ; ++j) f[i] = f[i] + f[i - j] * j ;

	ans = f[n] ;
	for (int i = 2 ; i <= n ; ++i) ans = ans + f[n - i] * (i * i - i) ;

	ans.print() ;

	return 0 ;
}