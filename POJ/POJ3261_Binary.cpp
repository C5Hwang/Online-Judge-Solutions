#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 20000 + 10 , MAX_NUM = 1000000 + 10 ;

int n , k , a[MAX_N] ;
int height[MAX_N] , rank[MAX_N] ;
int sa[MAX_N] , wx[MAX_N] , wy[MAX_N] , cnt[MAX_NUM] ;

bool cmp(int *x , int a , int b , int k) {
	return x[a] == x[b] && x[a + k] == x[b + k] ;
}

void build(int m) {
	int p = 0 , *x = wx , *y = wy ;
	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[x[i] = a[i]] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[a[i]]] = i ;

	for (int k = 1 ; p < n ; m = p , k <<= 1) {
		int r = 0 ;
		for (int i = n - k ; i < n ; ++i) y[r++] = i ;
		for (int i = 0 ; i < n ; ++i) if (sa[i] >= k) y[r++] = sa[i] - k ;

		for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
		for (int i = 0 ; i < n ; ++i) ++cnt[x[y[i]]] ;
		for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
		for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[x[y[i]]]] = y[i] ;

		std::swap(x , y) ;
		p = 1 ; x[sa[0]] = 0 ;
		for (int i = 1 ; i < n ; ++i)
			if (cmp(y , sa[i] , sa[i - 1] , k)) x[sa[i]] = p - 1 ;
			else x[sa[i]] = p++ ;
	}
}

void getheight() {
	for (int i = 0 ; i < n ; ++i) rank[sa[i]] = i ;

	int k = 0 ;
	for (int i = 0 ; i < n - 1 ; ++i) {
		if (k) --k ;

		int j = sa[rank[i] - 1] ;
		while (a[i + k] == a[j + k]) ++k ;
		height[rank[i]] = k ;
	}
}

bool check(int x) {
	int len = 0 , area = 0 ;
	for (int i = 1 ; i < n ; ++i) {
		if (height[i] < x) {area = std::max(area , len) ; len = 0 ; continue ;}

		if (len) ++len ;
		else len += 2 ;
	}

	return std::max(area , len) >= k ;
}

int main() {
	int maxa = 0 ;
	scanf("%d %d" , &n , &k) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d" , &a[i]) , maxa = std::max(maxa , a[i]) ;
	a[n++] = 0 ;

	///
	
	build(maxa + 1) ;
	getheight() ;

	///
	
	int L = 0 , R = n ;
	while (L + 1 < R) {
		int mid = (L + R) / 2;
		if (check(mid)) L = mid ;
		else R = mid ;
	}
	printf("%d\n" , L) ;

	return 0 ;
}
