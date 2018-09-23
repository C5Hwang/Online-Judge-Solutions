#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200000 + 10 ;

int n , len , bh[MAX_N] ;
char s1[MAX_N] , s2[MAX_N] ;
int rank[MAX_N] , height[MAX_N] ;
int sa[MAX_N] , wx[MAX_N] , wy[MAX_N] , cnt[MAX_N] ;

bool cmp(int *x , int a , int b , int k) {return x[a] == x[b] && x[a + k] == x[b + k] ;}

void build(int m) {
	int p = 1 , *x = wx , *y = wy ;
	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[x[i] = s1[i]] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[x[i]]] = i ;

	for (int k = 1 ; p < n ; k <<= 1 , m = p) {
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
		while (s1[i + k] == s1[j + k]) ++k ;
		height[rank[i]] = k ;
	}
}

int main() {
	int maxa = '#' ;
	scanf("%s %s" , s1 , s2) ;
	n = strlen(s1) ; len = strlen(s2) ;
	for (int i = 0 ; i < n ; ++i) maxa = std::max(maxa , (int)s1[i]) , bh[i] = 0 ;
	bh[n] = -1 ; s1[n++] = '#' ;
	for (int i = 0 ; i < len ; ++i) bh[n] = 1 , s1[n++] = s2[i] , maxa = std::max(maxa , (int)s2[i]) ;
	bh[n] = -1 ; s1[n++] = 0 ;

	///
	
	build(maxa + 1) ;
	getheight() ;

	///

	int res = 0 ;
	for (int i = 1 ; i < n ; ++i) {
		int x = bh[sa[i]] , y = bh[sa[i - 1]] ;
		if (x^1 != y) continue ;

		res = std::max(res , height[i]) ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
