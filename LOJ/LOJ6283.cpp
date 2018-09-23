#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define ed(x) (x * siz)
#define st(x) ((x - 1) * siz + 1)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , mod = 1e4 + 7 ;

int n , siz , a[MAX_N] , ti[MAX_N] , ad[MAX_N] , bk[MAX_N] ;

void update(int x) {
	for (int i = st(x) ; i <= std::min(ed(x) , n) ; ++i)
		a[i] = ((ll)a[i] * ti[x] + ad[x]) % mod ;
	ti[x] = 1 ; ad[x] = 0 ;
}

void modify(int ty , int x , int y , int c) {
	update(bk[x]) ;
	for (int i = x ; i <= std::min(ed(bk[x]) , y) ; ++i)
		if (!ty) (a[i] += c) %= mod ;
		else a[i] = (ll)a[i] * c % mod ;

	if (bk[x] != bk[y]) {
		update(bk[y]) ;
		for (int i = st(bk[y]) ; i <= y ; ++i)
			if (!ty) (a[i] += c) %= mod ;
			else a[i] = (ll)a[i] * c % mod ;
	}

	for (int i = bk[x] + 1 ; i < bk[y] ; ++i)
		if (!ty) (ad[i] += c) %= mod ;
		else {ad[i] = (ll)ad[i] * c % mod ; ti[i] = (ll)ti[i] * c % mod ;}
}

inline int read() {
	char c = getchar() ;
	int f = 1 , num = 0 ;

	for (; c < '0' || c > '9' ; c = getchar()) ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 + c - '0' ;

	return num * f ;
}

int main() {
	n = read() ; siz = (int)sqrt(n) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) , a[i] %= mod ;
	for (int i = 1 ; i <= n ; ++i) bk[i] = (i - 1) / siz + 1 , ti[i] = 1 ;

	///

	for (int i = 0 ; i < n ; ++i) {
		int op , x , y , z ;
		op = read() ; x = read() ; y = read() ; z = read() ;
		z %= mod ;

		if (op == 2){
			int tmp = ((ll)a[y] * ti[bk[y]] + ad[bk[y]]) % mod ;
			printf("%d\n" , tmp) ;
		}
		else modify(op , x , y , z) ;
	}

	return 0 ;
}