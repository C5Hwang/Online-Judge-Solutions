#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e6 + 10 ;

int n , m , cnt[MAX_N] , pre[MAX_N] , fa[MAX_N] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int find(int x) {return fa[x] == -1 ? x : (fa[x] = find(fa[x])) ;}

int main() {
	freopen("shop.in" , "r" , stdin) ;
	freopen("shop.out" , "w" , stdout) ;

	n = read() ; m = read() ;
	for (int i = 1 ; i < n ; ++i) pre[i] = read() ;
	for (; m-- ;) {int x = read() ; ++cnt[x] ;}

	///

	ll ans = 0 ;
	for (int i = 0 ; i < n ; ++i) fa[i] = -1 ;
	for (int i = n - 1 ; i ; --i) {
		int f = find(i) ;
		for (; f && !cnt[f] ;) {
			int nf = pre[f] ;
			fa[f] = nf ; f = find(f) ;
		}

		if (cnt[f]) --cnt[f] , ans += i ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}