#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

int n , siz , bk[MAX_N] ;
ll a[MAX_N] , sum[MAX_N] , ad[MAX_N] ;

void add(int x , int y , int c) {
	for (int i = x ; i <= std::min(y , ed(bk[x])) ; ++i) a[i] += c , sum[bk[i]] += c ;
	if (bk[x] != bk[y]) for (int i = st(bk[y]) ; i <= y ; ++i) a[i] += c , sum[bk[i]] += c ;

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) {
		ad[i] += c ;
		if (ed(i) > n) sum[i] += (n - st(i) + 1) * (ll)c ;
		else sum[i] += siz * (ll)c ;
	}
}

ll find(int x , int y , int c) {
	ll res = 0 ;

	for (int i = x ; i <= std::min(y , ed(bk[x])) ; ++i) (res += a[i] + ad[bk[i]]) %= c ;
	if (bk[x] != bk[y]) for (int i = st(bk[y]) ; i <= y ; ++i) (res += a[i] + ad[bk[i]]) %= c ;

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) (res += sum[i]) %= c ;

	return res ;
}

int main() {
	scanf("%d" , &n) ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%lld" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) {
		bk[i] = (i - 1) / siz + 1 ;
		sum[bk[i]] += a[i] ;
	}

	///

	for (int i = 0 ; i < n ; ++i) {
		int op , x , y , c ;
		scanf("%d %d %d %d" , &op , &x , &y , &c) ;

		if (!op) add(x , y , c) ;
		else printf("%lld\n" , find(x , y , c + 1)) ;
	}

	return 0 ; 
}