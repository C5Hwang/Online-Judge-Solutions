#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_L = 100 + 10 , MAX_ALL = 20200 + 10 , lgN = 20 + 5 ;

char st[MAX_L] ;
int rank[MAX_ALL] , height[MAX_ALL] ;
int sa[MAX_ALL] , wx[MAX_ALL] , wy[MAX_ALL] , cnt[MAX_ALL] ;
int n , all , s[MAX_ALL] , bh[MAX_ALL] , ap[MAX_N] , f[MAX_ALL][lgN] ;

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

void RMQ() {
	for (int i = 1 ; i < n ; ++i) f[i][0] = height[i] ;
	
	for (int j = 1 ; (1 << j) < n ; ++j)
		for (int i = 1 ; i < n ; ++i) {
			int k = i + (1 << (j - 1)) ;
			if (k >= n) f[i][j] = f[i][j - 1] ;
			else f[i][j] = std::min(f[i][j - 1] , f[k][j - 1]) ;
		}
}

///

int query(int x , int y) {
	++x ;
	int len = y - x + 1 ;

	int k = 0 ;
	for (; (1 << (k + 1)) <= len ; ++k) ;

	return std::min(f[x][k] , f[y - (1 << k) + 1][k]) ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		int maxa = 2 * n , len ;
		all = 0 ; 
		scanf("%d" , &n) ;
		for (int i = 0 ; i < n ; ++i) {
			scanf("%s" , st) ;
			len = strlen(st) ;
			for (int j = 0 ; j < len ; ++j) bh[all] = i , s[all] = (int)st[j] + n , maxa = std::max(maxa , s[all++]) ;
			s[all++] = i * 2 + 1 ;
			for (int j = len - 1 ; j >= 0 ; --j) bh[all] = i , s[all++] = (int)st[j] + n ;
			if (i + 1 != n) s[all++] = i * 2 + 2 ;
		}
		s[all++] = 0 ;
		if (n == 1) {printf("%d\n" , len) ; continue ;}
		std::swap(n , all) ;

		///
		
		build(maxa + 1) ;
		getheight() ; RMQ() ;

		///
		
		int L = 2 * all , sum = 1 , res = 0 ;
		memset(ap , 0 , sizeof(ap)) ; ++ap[bh[sa[L]]] ;
		for (int i = 2 * all + 1 ; i < n ; ++i) {
			int num = bh[sa[i]] ;
			++ap[num] ;
			if (ap[num] == 1) ++sum ;

			while (sum == all) {
				int newn = bh[sa[L]] ;
				res = std::max(res , query(L++ , i)) ;
				--ap[newn] ;
				if (!ap[newn]) --sum ;
			}
		}

		printf("%d\n" , res) ;
	}

	return 0 ;
}
