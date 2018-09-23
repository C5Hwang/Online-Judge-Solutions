#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 1000 + 10 , MAX_N = 100 + 10 , MAX_ALL = 100100 + 10 , lgN = 20 + 5 ;

char st[MAX_L] ;
int n , s[MAX_ALL] , bh[MAX_ALL] ;
int rank[MAX_ALL] , height[MAX_ALL] ;
int cur , f[MAX_ALL][lgN] , ap[MAX_N] , point[MAX_ALL] ;
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

void RMQ() {
	for (int i = 1 ; i < n ; ++i) f[i][0] = height[i] ;

	for (int j = 1 ; (1 << j) < n ; ++j)
		for (int i = 1 ; i < n ; ++i) {
			int k = i + (1 << (j - 1)) ;

			if (k >= n) f[i][j] = f[i][j - 1] ;
			else f[i][j] = std::min(f[i][j - 1] , f[k][j - 1]) ;
		}
}

int query(int L , int R) {
	++L ;
	int len = R - L + 1 , t ;
	for (t = 0 ; (1 << (t + 1)) <= len ; ++t) ;

	return std::min(f[L][t] , f[R - (1 << t) + 1][t]) ;
}

void print(int x , int len , int k) {
	for (int i = x ; i < x + len ; ++i) printf("%c" , (char)s[i] - k) ;
	printf("\n") ;
}

int main() {
	scanf("%d" , &n) ;
	while (n > 0) {
		int all = 0 , maxa = n ;
		for (int i = 0 ; i < n ; ++i) {
			scanf("%s" , st) ;
			int len = strlen(st) ;

			for (int j = 0 ; j < len ; ++j) 
				bh[all] = i , s[all++] = (int)st[j] + n , maxa = std::max(maxa , (int)st[j] + n) ;
			if (i + 1 != n) s[all++] = i + 1 ;
		}
		s[all++] = 0 ;
		std::swap(all , n) ;

		///

		build(maxa + 1) ;
		getheight() ; RMQ() ;

		///
			
		int L = all , R , k = all / 2 + 1 , t = 0 , res = 0 ;
		memset(ap , 0 , sizeof(ap)) ;
		for (R = all ; R < n ; ++R) {
			int num = bh[sa[R]] ;
			if (!ap[num]) ++t ;
			++ap[num] ;

			while (t == k) {
				int num = bh[sa[L]] ;
				--ap[num] ;
				if (!ap[num]) --t ;

				res = std::max(res , query(L++ , R)) ;
			}
		}

		///

		if (res == 0) {printf("?\n\n") ; scanf("%d" , &n) ; continue ;}

		cur = 0 ; t = 0 ; L = all ;
		memset(ap , 0 , sizeof(ap)) ;
		for (R = all ; R < n ; ++R) {
			int num = bh[sa[R]] ;
			if (!ap[num]) ++t ;
			++ap[num] ;

			while (t == k) {
				int num = bh[sa[L]] ;
				--ap[num] ;
			   	if (!ap[num]) --t ;

				if (query(L , R) == res) point[cur++] = sa[L] ;

				++L ;
			}
		}

		int last = 0 ; print(point[0] , res , all) ;
		for (int i = 1 ; i < cur ; ++i)
			if (query(rank[point[last]] , rank[point[i]]) >= res) continue ;
			else last = i , print(point[i] , res , all) ;

		printf("\n") ;

		scanf("%d" , &n) ;
	}


	return 0 ;
}
