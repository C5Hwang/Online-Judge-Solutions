#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 20000 + 10 , MAX_NUM = 1000000 + 10 ;

int n , k , a[MAX_N] ;
int L , R , queue[MAX_N] ;
int rank[MAX_N] , height[MAX_N] ;
int sa[MAX_N] , wx[MAX_N] , wy[MAX_N] , cnt[MAX_NUM] ;

bool cmp(int *x , int a , int b , int k) {
	return x[a] == x[b] && x[a + k] == x[b + k] ;
}

void build(int m) {
	int p = 0 , *x = wx , *y = wy ;
	for (int i = 0 ; i < m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) ++cnt[x[i] = a[i]] ;
	for (int i = 1 ; i < m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n - 1 ; i >= 0 ; --i) sa[--cnt[a[i]]] = i ;

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
		while (a[i + k] == a[j + k]) ++k ;
		height[rank[i]] = k ;
	}
}

///

void pop(int x) {if (queue[L] == x) ++L ;}

void push(int x) {
	queue[++R] = x ;

	while (R > L && height[queue[R]] < height[queue[R - 1]]) std::swap(queue[R] , queue[R - 1]) , --R ;
}

int main() {
	int maxa = 0 ;
	scanf("%d %d" , &n , &k) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d" , &a[i]) , maxa = std::max(maxa , a[i]) ;
	a[n++] = 0 ;

	///
	
	build(maxa + 1) ;
	getheight() ;

	///
	
	L = 1 , R = 0 ;
	int j = k , res ;
	for (int i = 2 ; i <= j ; ++i) push(i) ;
	res = height[queue[L]] ;

	for (++j ; j < n ; ++j)	{
		int i = j - k + 1 ; pop(i) ; push(j) ;

		res = std::max(res , height[queue[L]]) ;
	}

	printf("%d\n" , res) ;

	return 0 ;
}
