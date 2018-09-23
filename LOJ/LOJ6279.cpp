#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , INF = 0x7FFFFFFF ;

struct data {
	int num , pl ;
}a[MAX_N] ;

int n , siz , bk[MAX_N] , ad[MAX_N] ;

bool cmp(data x , data y) {return x.num < y.num ;}

void update(int x) {
	int L = st(x) , R = std::min(ed(x) , n) ;
	std::sort(a + L , a + R + 1 , cmp) ;
}

int getans(int x , int c) {
	c -= ad[x] ;
	int L = st(x) , R = ed(x) + 1 ;

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (a[mid].num >= c) R = mid ;
		else L = mid ;
	}

	if (a[L].num >= c) return -INF ;
	return a[L].num + ad[x] ;
}

void modify(int x , int y , int c) {
	for (int i = st(bk[x]) ; i <= std::min(ed(bk[x]) , n) ; ++i)
		if (a[i].pl >= x && a[i].pl <= y) a[i].num += c ;
	update(bk[x]) ;

	if (bk[x] != bk[y]) {
		for (int i = st(bk[y]) ; i <= std::min(ed(bk[y]) , n) ; ++i)
			if (a[i].pl <= y) a[i].num += c ;
		update(bk[y]) ;
	}

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) ad[i] += c ;
}

int find(int x , int y , int c) {
	int ans = -INF ;

	for (int i = st(bk[x]) ; i <= std::min(ed(bk[x]) , n) ; ++i)
		if (a[i].pl >= x && a[i].pl <= y && a[i].num + ad[bk[x]] < c) ans = std::max(ans , a[i].num + ad[bk[x]]) ;
	if (bk[x] != bk[y])
		for (int i = st(bk[y]) ; i <= std::min(ed(bk[y]) , n) ; ++i)
			if (a[i].pl <= y && a[i].num + ad[bk[y]] < c) ans = std::max(ans , a[i].num + ad[bk[y]]) ;

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) ans = std::max(ans , getans(i , c)) ;

	if (ans == -INF) return -1 ;
	return ans ;
}

int main() {
	scanf("%d" , &n) ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i].num) , a[i].pl = i ;
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;

	for (int i = 1 ; ed(i) <= n ; ++i) update(i) ;

	///

	for (int i = 0 ; i < n ; ++i) {
		int op , x , y , c ;
		scanf("%d %d %d %d" , &op , &x , &y , &c) ;

		if (!op) modify(x , y , c) ;
		else printf("%d\n" , find(x , y , c)) ;
	}

	return 0 ;
}