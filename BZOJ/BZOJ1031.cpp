#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 1e5 + 10 ;

int len , n ;
char st[MAX_L] , s[2 * MAX_L] ;
int cnt[2 * MAX_L] , wx[2 * MAX_L] , wy[2 * MAX_L] , sa[2 * MAX_L] ;

bool cmp(int a , int b , int k , int *y) {
	return y[a] == y[b] && y[a + k] == y[b + k] ;
}

void build(int m) {
	int *x = wx , *y = wy , p = 1 ;
	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[x[i] = s[i]] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[s[i]]] = i ;

	for (int k = 1 ; p < n ; m = p , k <<= 1) {
		int r = 0 ;
		for (int i = n - k ; i < n ; ++i) y[r++] = i ;
		for (int i = 0 ; i < n ; ++i) if (sa[i] >= k) y[r++] = sa[i] - k ;

		for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
		for (int i = 0 ; i < n ; ++i) ++cnt[x[y[i]]] ;
		for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
		for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[x[y[i]]]] = y[i] ;

		std::swap(x , y) ;
		x[sa[0]] = 0 ; p = 1 ;
		for (int i = 1 ; i < n ; ++i)
			if (cmp(sa[i] , sa[i - 1] , k , y)) x[sa[i]] = p - 1 ;
			else x[sa[i]] = p++ ;
	}
}

int main() {
	scanf("%s" , st) ;

	int maxa = 0 ;
	len = strlen(st) ; n = len * 2 ;
	for (int i = 0 ; i < n ; ++i)
		s[i] = st[i % len] , maxa = std::max(maxa , (int)s[i]) ;
	s[n++] = 0 ;

	///
	
	build(maxa + 1) ;

	///
	
	for (int i = 0 ; i < n ; ++i) {
		int p = sa[i] + len - 1 ;
		if (sa[i] >= len) continue ;

		printf("%c" , s[p]) ;
	}
	printf("\n") ;

	return 0 ;
}
