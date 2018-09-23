#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-5 ;
const int MAX_N = 2500 + 10 , INF = 0x3f3f3f3f ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N] ;

Link *head[MAX_N] ;
int tot , siz[MAX_N] , dfx[MAX_N] ;
int n , k , cur , s[MAX_N] , p[MAX_N] ;
db L , R , w[MAX_N] , f[MAX_N][MAX_N] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		dfs(nx) ; siz[x] += siz[nx] ;
	}
	dfx[++tot] = x ;
}

bool dp(db d) {
	for (int i = 1 ; i <= n ; ++i) w[i] = p[i] - d * s[i] ;
	for (int i = 1 ; i <= n ; ++i) f[0][i] = -INF ;

	for (int i = 1 ; i < tot ; ++i) {
		int x = dfx[i] ;
		for (int j = 1 ; j <= n ; ++j)
			f[i][j] = std::max(f[i - 1][j - 1] + w[x] , f[i - siz[x]][j]) ;
	}

	return f[tot - 1][k] >= 0 ;
}

int main() {
	scanf("%d %d" , &k , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int x ;
		scanf("%d %d %d" , &s[i] , &p[i] , &x) ;
		ins(x , i) ; R = std::max(R , (db)p[i]) ;
	}

	///

	dfs(0) ;
	for (; fabs(L - R) > eps ;) {
		db mid = (L + R) * 0.5 ;
		if (dp(mid)) L = mid ;
		else R = mid ;
	}

	printf("%0.3lf\n" , L) ;

	return 0 ;
}