#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 3e6 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;

Link *head[MAX_N] , *nw[MAX_N] ;
int N , n , m , ti , cur , sel[MAX_N] ;
int tot , sta[MAX_N] , dfn[MAX_N] , dfl[MAX_N] , st[MAX_N] , tre[MAX_N << 2] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	sta[++tot] = x ;
	st[x] = 1 ; nw[x] = head[x] ;

	for (; tot ;) {
		int x = sta[tot] ;

		if (nw[x]) {
			int nx = nw[x]->num ;
			sta[++tot] = nx ; st[nx] = ti + 1 ;
			nw[nx] = head[nx] ; nw[x] = nw[x]->next ;
		}
		else {dfn[x] = ++ti ; dfl[ti] = x ; --tot ;}
	}
}

void build() {
	for (N = 1 ; N <= n + 1 ; N <<= 1) ;
	for (int i = 1 ; i <= n ; ++i) tre[N + i] = dfl[i] ;
	for (int i = N - 1 ; i ; --i) tre[i] = std::max(tre[i << 1] , tre[i << 1 | 1]) ;
}

int find(int x , int y) {
	int res = 0 ;
	for (x += N - 1 , y += N + 1 ; x ^ y ^ 1 ; x >>= 1 , y >>= 1) {
		if (!(x & 1)) res = std::max(res , tre[x ^ 1]) ;
		if (y & 1) res = std::max(res , tre[y ^ 1]) ;
	}

	return res ;
}

void modify(int t) {
	tre[t += N] = 0 ;
	for (t >>= 1 ; t ; t >>= 1) tre[t] = std::max(tre[t << 1] , tre[t << 1 | 1]) ;
}

int main() {
	freopen("shop.in" , "r" , stdin) ;
	freopen("shop.out" , "w" , stdout) ;

	n = read() ; m = read() ;
	for (int i = 1 ; i < n ; ++i) {
		int x = read() ;
		ins(x , i) ;
	}
	for (int i = 0 ; i < m ; ++i) {int x = read() ; ++sel[x] ;}

	///

	dfs(0) ;
	build() ;

	ll ans = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		int x = dfl[i] ;
		for (; sel[x]-- ;) {
			int a = find(st[x] , dfn[x]) ;

			if (!a) break ;
			else {ans += a ; modify(dfn[a]) ;}
		}
	}

	printf("%lld\n" , ans) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}