#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long 
#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

ll sum[MAX_N] ;
bool flag[MAX_N] ;
int n , siz , a[MAX_N] , bk[MAX_N] ;

void update(int x) {
	int t = a[st(x)] ; sum[x] = 0 ;

	for (int i = st(x) ; i <= ed(x) ; ++i) {
		sum[x] += a[i] ;
		t = std::max(t , a[i]) ;
	}

	if (t <= 1) flag[x] = 1 ;
}

void modify(int x , int y) {
	for (int i = x ; i <= std::min(y , ed(bk[x])) ; ++i) a[i] = (int)sqrt(a[i]) ;
	update(bk[x]) ;
	if (bk[x] != bk[y]) {
		for (int i = st(bk[y]) ; i <= y ; ++i) a[i] = (int)sqrt(a[i]) ;
		update(bk[y]) ;
	}

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) {
		if (flag[i]) continue ;
		for (int j = st(i) ; j <= ed(i) ; ++j) a[j] = (int)sqrt(a[j]) ;
		update(i) ;
	}
}

ll find(int x , int y) {
	ll res = 0 ;
	for (int i = x ; i <= std::min(ed(bk[x]) , y) ; ++i) res += a[i] ;
	if (bk[x] != bk[y]) for (int i = st(bk[y]) ; i <= y ; ++i) res += a[i] ;

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) res += sum[i] ;

	return res ;
}

int main() {
	scanf("%d" , &n) ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= n ; ++i) {
		bk[i] = (i - 1) / siz + 1 ;
		sum[bk[i]] += a[i] ;
	}

	///

	for (int i = 0 ; i < n ; ++i) {
		int op , x , y , c ;
		scanf("%d %d %d %d" , &op , &x , &y , &c) ;

		if (!op) modify(x , y) ;
		else printf("%lld\n" , find(x , y)) ;
	}

	return 0 ;
}