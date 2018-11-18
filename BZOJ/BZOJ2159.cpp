#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , MAX_K = 150 + 10 , mod = 1e4 + 7 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , k , cur , pw[MAX_K] , tmp[MAX_K] , S[MAX_K][MAX_K] , f[MAX_N][MAX_K] , g[MAX_N][MAX_K] ;

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dp_f(int x , int fa) {
	f[x][0] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dp_f(nx , x) ;

		(f[x][0] += f[nx][0]) %= mod ;
		for (int i = 1 ; i <= k ; ++i) (f[x][i] += f[nx][i - 1] + f[nx][i]) %= mod ;
	}
}

void dp_g(int x , int fa) {
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		for (int i = 0 ; i <= k ; ++i) tmp[i] = (f[x][i] + g[x][i]) % mod ;

		(tmp[0] += mod - f[nx][0]) %= mod ;
		for (int i = 1 ; i <= k ; ++i) (tmp[i] += mod + mod - f[nx][i] - f[nx][i - 1]) %= mod ;

		g[nx][0] = tmp[0] ;
		for (int i = 1 ; i <= k ; ++i) g[nx][i] = (tmp[i] + tmp[i - 1]) % mod ;

		dp_g(nx , x) ;
	}
}

int main() {
	int L , i , now , A , B , Q ;
	scanf("%d %d" , &n , &k) ;
	scanf("%d %d %d %d %d" , &L , &now , &A , &B , &Q) ;

	for (int i = 1 ; i < n ; ++i) {
		now = (now * A + B) % Q ;
		int tmp = (i < L) ? i : L , x = i - now % tmp , y = i + 1 ;

		ins(x , y) ; ins(y , x) ;
	}

	///

	S[0][0] = 1 ; pw[0] = 1 ;
	for (int i = 1 ; i <= k ; ++i) pw[i] = (pw[i - 1] * i) % mod ;
	for (int i = 1 ; i <= k ; ++i)
		for (int j = 1 ; j <= k ; ++j)
			S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % mod ;

	dp_f(1 , 1) ;
	dp_g(1 , 1) ;

	///

	for (int i = 1 ; i <= n ; ++i) {
		for (int j = 0 ; j <= k ; ++j) (f[i][j] += g[i][j]) %= mod ;

		int ans = 0 ;
		for (int j = 0 ; j <= k ; ++j) {
			int tmp = S[k][j] * pw[j] % mod ;
			(ans += tmp * f[i][j]) %= mod ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ; 
}