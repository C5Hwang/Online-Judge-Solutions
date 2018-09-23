#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2000 + 10 , lgN = 20 + 5 ;

int len , n ;
char st[MAX_N] ;
int height[MAX_N] , rank[MAX_N] , f[MAX_N][lgN] ;
int sa[MAX_N] , wx[MAX_N] , wy[MAX_N] , cnt[MAX_N] ;

bool cmp(int *x , int a , int b , int k) {return x[a] == x[b] && x[a + k] == x[b + k] ;}

void build(int m) {
	int p = 0 , *x = wx , *y = wy ;
	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[x[i] = st[i]] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[st[i]]] = i ;

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
		while (st[i + k] == st[j + k]) ++k ;
		height[rank[i]] = k ;
	}
}

///

void RMQ() {
	for (int i = 1 ; i < n ; ++i) f[i][0] = height[i] ;

	for (int i = 1 ; (1 << i) <= n ; ++i)
		for (int j = 1 ; j < n ; ++j) {
			int k = j + (1 << (i - 1)) ;
			if (k >= n) f[j][i] = f[j][i - 1] ;
			else f[j][i] = std::min(f[j][i - 1] , f[k][i - 1]) ;
		}
}

int query(int x , int y) {
	if (x > y) std::swap(x , y) ;
	++x ; int l = y - x + 1 , t = 0 ;

	for (; x + (1 << (t + 1)) <= y ; ++t) ;

	return std::min(f[x][t] , f[y - (1 << t) + 1][t]) ;
}

int main() {
	scanf("%s" , st) ; n = len = strlen(st) ;
	int maxa = '#' ; st[n++] = '#' ;
	for (int i = len - 1 ; i >= 0 ; --i) st[n++] = st[i] , maxa = std::max(maxa , (int)st[i]) ;
	st[n++] = 0 ;

	///
	
	build(maxa + 1) ;
	getheight() ; RMQ() ;

	///

	int maxl = 0 , maxp = 0 ;
	for (int i = 0 ; i < len ; ++i) {
		int j = n - i - 2 , len1 = query(rank[i] , rank[j]) , len2 = query(rank[i] , rank[j + 1]) ,
			ans1 = len1 * 2 - 1 , ans2 = len2 * 2 ;

		if (ans1 > maxl) maxl = ans1 , maxp = i ;
		else if (ans2 > maxl) maxl = ans2 , maxp = i ;
	}

	int r = maxl / 2 , L = maxp - r , R = maxl % 2 ? maxp + r : maxp + r - 1 ;
	for (int i = L ; i <= R ; ++i) printf("%c" , st[i]) ;
	printf("\n") ;
}
