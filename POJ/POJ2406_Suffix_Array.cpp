#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 1000000 + 10 ;

int n ;
char st[MAX_L] ;
int rank[MAX_L] , height[MAX_L] , f[MAX_L] ;
int sa[MAX_L] , wx[MAX_L] , wy[MAX_L] , cnt[MAX_L] ;

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

void RMQ() {
	int t = rank[0] ; f[t] = height[t] ;
	for (int i = t - 1 ; i >= 1 ; --i) f[i] = std::min(f[i + 1] , height[i]) ;

	f[t + 1] = height[t + 1] ;
	for (int i = t + 2 ; i < n ; ++i) f[i] = std::min(f[i - 1] , height[i]) ;
}

int query(int x) {
	int y = rank[0] ;

	if (x < y) return f[x + 1] ;
	else return f[x] ;
}

int main() {
	scanf("%s" , st) ;
	while (st[0] != '.') {
		int maxa = 0 ; n = strlen(st) ;
		for (int i = 0 ; i < n ; ++i) maxa = std::max(maxa , (int)st[i]) ;
		st[n++] = 0 ;
		
		///

		build(maxa + 1) ;
		getheight() ; RMQ() ;

		///

		int i ;
		for (i = 1 ; i < n - 1 ; ++i) {
			if ((n - 1) % i != 0) continue ;

			int len = query(rank[i]) ;

			if (len == n - i - 1) break ;
		}

		printf("%d\n" , (n - 1) / i) ;

		scanf("%s" , st) ;
	}

	return 0 ;
}
