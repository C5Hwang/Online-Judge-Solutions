#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 1000 + 10 ;

char st[MAX_L] ;
int len , a[MAX_L] ;
int rank[MAX_L] , height[MAX_L] ;
int sa[MAX_L] , wx[MAX_L] , wy[MAX_L] , cnt[MAX_L] ;

bool cmp(int *x , int a , int b , int k) {
	return x[a] == x[b] && x[a + k] == x[b + k] ;
}

void build(int m) {
	int p = 0 , *x = wx , *y = wy ;
	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < len ; ++i) ++cnt[x[i] = a[i]] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = len - 1 ; i >= 0 ; --i) sa[--cnt[a[i]]] = i ;

	for (int k = 1 ; p < len ; k <<= 1 , m = p) {
		int r = 0 ;
		for (int i = len - k ; i < len ; ++i) y[r++] = i ;
		for (int i = 0 ; i < len ; ++i) if (sa[i] >= k) y[r++] = sa[i] - k ;

		for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
		for (int i = 0 ; i < len ; ++i) ++cnt[x[y[i]]] ;
		for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
		for (int i = len - 1 ; i >= 0 ; --i) sa[--cnt[x[y[i]]]] = y[i] ;

		std::swap(x , y) ;
		p = 1 ; x[sa[0]] = 0 ;
		for (int i = 1 ; i < len ; ++i)
			if (cmp(y , sa[i] , sa[i - 1] , k)) x[sa[i]] = p - 1 ;
			else x[sa[i]] = p++ ;
	}
}

void getheight() {
	for (int i = 0 ; i < len ; ++i) rank[sa[i]] = i ;

	int k = 0 ;
	for (int i = 0 ; i < len - 1 ; ++i) {
		if (k) --k ;

		int j = sa[rank[i] - 1] ;
		while (a[i + k] == a[j + k]) ++k ;
		height[rank[i]] = k ;
	}
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		int maxa = 0 ;
		scanf("%s" , st) ;
		len = strlen(st) ;
		for (int i = 0 ; i < len ; ++i) {
			a[i] = (int)st[i] ;
			maxa = std::max(a[i] , maxa) ;
		}
		a[len++] = 0 ;

		///

		build(maxa + 1) ;
		getheight() ;

		///

		int res = 0 ;
		for (int i = 1 ; i < len ; ++i) {
			int n = len - sa[i] - 1 ;
			res += n - height[i] ;
		}

		printf("%d\n" , res) ;
	}

	return 0 ;
}
