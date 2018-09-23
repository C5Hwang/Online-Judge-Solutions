#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 ;

struct data {
	ll num ; int pl ;
}a[MAX_N] ;

ll ad[MAX_N] ;
int n , siz , bk[MAX_N] ;

bool cmp(data x , data y) {return x.num < y.num ;}

void update(int x) {
	int L = st(x) , R = std::min(ed(x) , n) ;
	std::sort(a + L , a + R + 1 , cmp) ;
}

int getans(int x , ll c) {
	int L = st(x) , R = std::min(ed(x) , n) ;

	for (; L + 1 < R ;) {
		int mid = (L + R) >> 1 ;
		if (a[mid].num >= c) R = mid ;
		else L = mid ;
	}

	int tmp = L - st(x) ;
	if (a[L].num < c) ++tmp ;
	if (a[R].num < c) ++tmp ;

	return tmp ;
}

void modify(int x , int y , int c) {
	for (int i = st(bk[x]) ; i <= std::min(ed(bk[x]) , n) ; ++i)
		if (a[i].pl >= x && a[i].pl <= y) a[i].num += c ;
	update(bk[x]) ;

	if (bk[x] != bk[y]) {
		for (int i = st(bk[y]) ; i <= std::min(ed(bk[y]) , n) ; ++i) if (a[i].pl <= y) a[i].num += c ;
		update(bk[y]) ;
	}

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) ad[i] += c ;
}

int find(int x , int y , ll c) {
	int res = 0 ;

	for (int i = st(bk[x]) ; i <= std::min(ed(bk[x]) , n) ; ++i)
		if (a[i].pl >= x && a[i].pl <= y && a[i].num + ad[bk[x]] < c) ++res ;
	if (bk[x] != bk[y])
		for (int i = st(bk[y]) ; i <= std::min(ed(bk[y]) , n) ; ++i)
			if (a[i].pl <= y && a[i].num + ad[bk[y]] < c) ++res ;

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i) res += getans(i , c - ad[i]) ;

	return res ;
}

int main() {
	scanf("%d" , &n) ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) {
		scanf("%lld" , &a[i].num) ;
		a[i].pl = i ;
	}

	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 ;
	for (int i = 1 ; ed(i) <= n ; ++i) update(i) ;

	///

	for (int i = 0 ; i < n ; ++i) {
		int op , x , y , c ;
		scanf("%d %d %d %d" , &op , &x , &y , &c) ;

		if (!op) modify(x , y , c) ;
		else printf("%d\n" , find(x , y , (ll)c * c)) ;
	}

	return 0 ;
}