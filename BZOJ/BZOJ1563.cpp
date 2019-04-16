#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define ldb long double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ldb INF = 1e18 , eps = 1e-8 ;
const int MAX_N = 1e5 + 10 , MAX_L = 30 + 5 ;

struct data {int x , y , pt ;}sta[MAX_N] ;

ldb f[MAX_N] ;
char s[MAX_N][MAX_L] ;
int T , n , L , P , tot , le , a[MAX_N] , S[MAX_N] ;

inline ldb qpow(ldb x , int t) {
	ldb sum = 1 , tmp = x ;
	for (; t ; t >>= 1 , tmp *= tmp)
		if (t & 1) sum *= tmp ;

	return sum ;
}

inline ldb getf(int x , int p) {
	int d = (S[x] - S[p - 1] + x - p) ;
	d = abs(d - L) ;

	return f[p - 1] + qpow(d , P) ;
}

bool check(int x , int op , int p) {
	if (x < p) return 0 ;

	ldb t1 = getf(x , op) , t2 = getf(x , p) ;
	return t2 - t1 < eps ;
}

int find(int x , int y , int op , int p) {
	++y ;
	for (; x + 1 < y ;) {
		int mid = (x + y) >> 1 ;
		if (check(mid , op , p)) y = mid ;
		else x = mid ;
	}

	return y ;
}

void update(int p) {
	int pre ;
	for (; tot ;) {
		int tx = sta[tot].x , ty = sta[tot].y , op = sta[tot].pt ;

		if (check(tx , op , p)) {pre = tx ; --tot ; --le ; continue ;}
		else {pre = find(tx , ty , op , p) ; sta[tot].y = pre - 1 ; break ;}
	}

	if (pre <= n) sta[++tot] = ((data){pre , n , p}) ;
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d %d" , &n , &L , &P) ;
		for (int i = 1 ; i <= n ; ++i) {
			scanf("%s" , s[i]) ;
			a[i] = strlen(s[i]) ; S[i] = S[i - 1] + a[i] ;
		}

		///

		f[0] = 0 ; tot = 0 ; le = 1 ;
		sta[++tot] = ((data){1 , n , 1}) ; f[1] = getf(1 , 1) ;

		for (int i = 2 ; i <= n ; ++i) {
			update(i) ;
			for (le = std::max(le , 1) ; sta[le].y < i ; ++le) ;
			f[i] = getf(i , sta[le].pt) ;
		}

		///

		if (f[n] - INF < eps) printf("%0.0Lf\n" , f[n]) ;
		else printf("Too hard to arrange\n") ;
		printf("--------------------\n") ;
	}

	return 0 ;
}