#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_L = 100 + 10 , MAX_ALL = 20200 + 10 ;

char st[MAX_N] ;
int rank[MAX_ALL] , height[MAX_ALL] ;
int n , all , bh[MAX_ALL] , s[MAX_ALL] , ap[MAX_N] ;
int sa[MAX_ALL] , wx[MAX_ALL] , wy[MAX_ALL] , cnt[MAX_ALL] ;

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

void add(int x , int &sum) {
	int num = bh[sa[x]] ;
	if (!ap[num]) ++sum ;
	++ap[num] ;
}

bool check(int m) {
	memset(ap , 0 , sizeof(ap)) ;
	int L = -1 , sum = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		if (height[i] < m) {
			if (L == -1) L = -1 , sum = 0 ;
			else {
				if (sum == all) return 1 ;
				for (int j = L ; j < i ; ++j) --ap[bh[sa[j]]] ;
				sum = 0 ; L = -1 ;
			}

			continue ;
		}

		if (L == -1) add(L = i - 1 , sum) ;
		add(i , sum) ;
	}
	
	return 0 ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		int maxa = 2 * n ;
		scanf("%d" , &n) ; all = 0 ;
		for (int i = 0 ; i < n ; ++i) {
			scanf("%s" , st) ;
			int len = strlen(st) ;
			for (int j = 0 ; j < len ; ++j) bh[all] = i , s[all] = (int)st[j] + n , maxa = std::max(s[all++] , maxa) ;
			s[all++] = i * 2 + 1 ;
			for (int j = len - 1 ; j >= 0 ; --j) bh[all] = i , s[all++] = (int)st[j] + n ;
			if (i + 1 != n) s[all++] = i * 2 + 2 ;
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
