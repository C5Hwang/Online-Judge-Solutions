#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_L = 1000 + 10 , MAX_ALL = 100100 + 10 ;

char st[MAX_L] ;
int ap[MAX_N] , point[MAX_ALL] ;
int rank[MAX_ALL] , height[MAX_ALL] ;
int n , k , cur , bh[MAX_ALL] , s[MAX_ALL] ;
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

bool check(int m) {
	cur = 0 ;
	bool ok = 0 ;
	int L = -1 , t = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		if (height[i] < m) {
			if (L > -1) {
				for (int j = L ; j < i ; ++j) --ap[bh[sa[j]]] ;
				if (t >= k) point[cur++] = L , ok = 1 ;
			}

			L = -1 ; t = 0 ;
			continue ;
		}

		int num ;
		if (L == -1) {
			L = i - 1 ;
			num = bh[sa[L]] ;
			if (!ap[num]) ++t ;
			++ap[num] ;
		}

		num = bh[sa[i]] ;
		if (!ap[num]) ++t ;
		++ap[num] ;
	}

	return ok ;
}

void print(int x , int len , int n) {
	for (int i = x ; i < x + len ; ++i) printf("%c" , s[i] - n) ;
	printf("\n") ;
}

int main() {
	scanf("%d" , &n) ;
	while (n > 0) {
		int all = 0 , maxa = n ; k = n / 2 + 1 ;
		for (int i = 0 ; i < n ; ++i) {
			scanf("%s" , st) ;
			int len = strlen(st) ;

			for (int j = 0 ; j < len ; ++j) bh[all] = i , s[all] = (int)st[j] + n , maxa = std::max(maxa , s[all++]) ;

			if (i + 1 != n) s[all++] = i + 1 ;
		}
		s[all++] = 0 ;
		std::swap(n , all) ;

		///

		build(maxa + 1) ;
		getheight() ;

		///

		height[n] = -1 ;
		int L = 0 , R = n , ncur = 0 ;
		while (L + 1 < R) {
			int mid = (L + R) / 2 ;

			if (check(mid)) L = mid , ncur = cur ;
			else R = mid ;
		}

		///

		if (L == 0) {printf("?\n\n") ; scanf("%d" , &n) ; continue ;}

		int last = 0 , res = L , mt ;
	   	L = point[0] + 1 ; R = L ; mt = height[L] ; cur = ncur ;
		print(sa[point[0]] , res , all) ;

		for (int i = 1 ; i < cur ; ++i) {
			for (; R <= point[i] ; ++R) mt = std::min(mt , height[R]) ;

			if (mt >= res) continue ;
			L = point[i] + 1 ; R = L ; mt = height[L] ;
			print(sa[point[i]] , res , all) ;
		}
		printf("\n") ;

		scanf("%d" , &n) ;
	}

	return 0 ;
}
