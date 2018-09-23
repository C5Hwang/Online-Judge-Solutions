#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 20000 + 10 , INF = 0x3f3f3f3f ;

struct Read {
	int num , bh ;
}re[MAX_N] ;

int n ;
int height[MAX_N] , rank[MAX_N] ;
int wx[MAX_N] , wy[MAX_N] , sa[MAX_N] , cnt[MAX_N] ;

bool cmp1(Read x , Read y) {return x.num < y.num ;}
bool cmp2(Read x , Read y) {return x.bh < y.bh ;}

bool cmp(int *x , int a , int b , int k) {
	return x[a] == x[b] && x[a + k] == x[b + k] ;
}

///

void build(int m) {
	int p = 0 , *x = wx , *y = wy ;

	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[x[i] = re[i].num] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[re[i].num]] = i ;

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
		while (re[i + k].num == re[j + k].num) ++k ;
		height[rank[i]] = k ;
	}
}

///

bool check(int k) {
	int minp , maxp ; minp = maxp = -1 ;
	for (int i = 1 ; i < n ; ++i) {
		if (height[i] < k) {minp = maxp = -1 ; continue ;}

		if (minp == -1 && maxp == -1) minp = std::min(sa[i] , sa[i - 1]) , maxp = std::max(sa[i] , sa[i - 1] ) ;
		else minp = std::min(minp , sa[i]) , maxp = std::max(maxp , sa[i]) ;

		if (maxp - minp > k) return 1 ;
	}

	return 0 ;
}

int main() {
	scanf("%d" , &n) ;
	while (n != 0) {
		int last = -INF ;
		for (int i = 0 ; i < n ; ++i) {
			int a ; scanf("%d" , &a) ;
			if (last == -INF) {last = a ; continue ;}
			
			re[i - 1].num = a - last ; re[i - 1].bh = i - 1 ; 
			last = a ;
		}
		--n ;

		///

		std::sort(re + 0 , re + n , cmp1) ;
		last = re[0].num ; re[0].num = 1 ;

		int maxn = 1 ;
		for (int i = 1 ; i < n ; ++i)
			if (re[i].num == last) re[i].num = maxn ;
			else last = re[i].num , re[i].num = ++maxn ;

		std::sort(re + 0 , re + n , cmp2) ;
		re[n++].num = 0 ;

		///

		build(maxn + 1) ;
		getheight() ;

		///

		int L = 0 , R = n + 1 ;
		while (L + 1 < R) {
			int mid = (L + R) >> 1 ;

			if (check(mid)) L = mid ;
			else R = mid ;
		}

		if (L >= 4) printf("%d\n" , L + 1) ;
		else printf("0\n") ;

		scanf("%d" , &n) ;
	}

	return 0 ;
}
