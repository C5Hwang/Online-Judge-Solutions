#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 10000 + 10 , MAX_N = 10 + 10 , MAX_ALL = 100010 + 10 ;

char st[MAX_L] ; bool ans[MAX_N] ;
int rank[MAX_ALL] , height[MAX_ALL] ;
int sa[MAX_ALL] , wx[MAX_ALL] , wy[MAX_ALL] , cnt[MAX_ALL] ;
int n , all , bh[MAX_ALL] , s[MAX_ALL] , minp[MAX_ALL] , maxp[MAX_ALL] ;

bool cmp(int *x , int a , int b , int k) {return x[a] == x[b] && x[a + k] == x[b + k] ;}

void build(int m) {
	int p = 1 , *x = wx , *y = wy ;
	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[x[i] = s[i]] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[s[i]]] = i ;

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
		while (s[i + k] == s[j + k]) ++k ;
		height[rank[i]] = k ;
	}
}

///

bool check(int m) {
	memset(ans , 0 , sizeof(ans)) ;
	memset(minp , -1 , sizeof(minp)) ;
	memset(maxp , -1 , sizeof(maxp)) ;

	int t = 0 , L = -1 ;
	for (int i = 1 ; i <= n ; ++i) {
		if (height[i] < m) {
			if (L == -1) {L = -1 ; t = 0 ; continue ;}
			else {
				if (t == all) return 1 ;
				for (int j = L ; j < i ; ++j) ans[bh[sa[j]]] = 0 , minp[bh[sa[j]]] = maxp[bh[sa[j]]] = -1 ;
				L = -1 ; t = 0 ; continue ;
			}
		}

		///

		int num ;
		if (L == -1) {
			L = i - 1 ;
			num = bh[sa[L]] ;
			if (minp[num] == -1) minp[num] = maxp[num] = sa[L] ;
			else if (!ans[num]) {
				minp[num] = std::min(minp[num] , sa[L]) ;
				maxp[num] = std::max(maxp[num] , sa[L]) ;
				if (maxp[num] - minp[num] >= m) ++t , ans[num] = 1 ;
			}
		}

		num = bh[sa[i]] ;
		if (minp[num] == -1) minp[num] = maxp[num] = sa[i] ;
		else if (!ans[num]) {
			minp[num] = std::min(minp[num] , sa[i]) ;
			maxp[num] = std::max(maxp[num] , sa[i]) ;
			if (maxp[num] - minp[num] >= m) ++t , ans[num] = 1 ;
		}
	}

	return 0 ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		all = 0 ;
		int maxa = n ;
		scanf("%d" , &n) ;
		for (int i = 0 ; i < n ; ++i) {
			scanf("%s" , st) ;
			int len = strlen(st) ;
			for (int j = 0 ; j < len ; ++j) bh[all] = i , s[all] = (int)st[j] + n , maxa = std::max(maxa , s[all++]) ;
			if (i + 1 != n) s[all++] = i + 1 ;
		}
		s[all++] = 0 ;
		std::swap(all , n) ;

		///

		build(maxa + 1) ;
		getheight() ;

		///

		height[n] = -1 ;
		int L = 0 , R = n ;
		while (L + 1 < R) {
			int mid = (L + R) / 2 ;
			if (check(mid)) L = mid ;
			else R = mid ;
		}

		printf("%d\n" , L) ;
	}

	return 0 ;
}
