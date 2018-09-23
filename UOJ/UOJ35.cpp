#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 ;

char s[MAX_N] ;
int n , wx[MAX_N] , wy[MAX_N] , sa[MAX_N] ;
int rank[MAX_N] , height[MAX_N] , cur[MAX_N] ;

bool cmp(int a , int b , int k , int *x)
{return x[a] == x[b] && x[a + k] == x[b + k] ;}

void build(int m) {
	int *x = wx , *y = wy , p = 0 ;
	for (int i = 0 ; i < m ; ++i) cur[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cur[x[i] = s[i]] ;
	for (int i = 1 ; i < m ; ++i) cur[i] += cur[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cur[s[i]]] = i ;

	for (int k = 1 ; p < n ; m = p , k <<= 1) {
		int r = 0 ;
		for (int i = n - k ; i < n ; ++i) y[r++] = i ;
		for (int i = 0 ; i < n ; ++i) if (sa[i] >= k) y[r++] = sa[i] - k ;

		for (int i = 0 ; i < m ; ++i) cur[i] = 0 ;
		for (int i = 0 ; i < n ; ++i) ++cur[x[y[i]]] ;
		for (int i = 1 ; i < m ; ++i) cur[i] += cur[i - 1] ;
		for (int i = n - 1 ; i >= 0 ; --i) sa[--cur[x[y[i]]]] = y[i] ;

		std::swap(x , y) ;
		x[sa[0]] = 0 ; p = 1 ;
		for (int i = 1 ; i < n ; ++i)
			if (cmp(sa[i] , sa[i - 1] , k , y)) x[sa[i]] = p - 1 ;
			else x[sa[i]] = p++ ;
	}
}

void GetHeight() {
	for (int i = 0 ; i < n ; ++i) rank[sa[i]] = i ;

	int k = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		if (k) --k ;

		int j = sa[rank[i] - 1] ;
		while (s[i + k] == s[j + k]) ++k ;
		height[rank[i]] = k ;
	}
}

int main() {
	scanf("%s" , s) ; n = strlen(s) ;
	int maxa = s[0] ; s[n++] = 0 ;
	for (int i = 1 ; i < n ; ++i)
		maxa = std::max(maxa , (int)s[i]) ;
	///

	build(maxa + 1) ;
	GetHeight() ;

	for (int i = 1 ; i < n ; ++i) printf("%d " , sa[i] + 1) ;
	printf("\n") ;
	for (int i = 2 ; i < n ; ++i) printf("%d " , height[i]) ;
	printf("\n") ;

	return 0 ;
}
