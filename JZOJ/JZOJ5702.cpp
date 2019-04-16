#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_K = 10 + 5 , mod = (119 << 23) + 1 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , m , k , cur , C[MAX_K][MAX_K] , f[2][MAX_N][MAX_K] , tmp[3][MAX_K] ;

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

void dp(int x , int fa) {
	f[0][x][0] = f[1][x][0] = 1 ;
	for (int t = 1 ; t <= k ; ++t) f[0][x][t] = f[1][x][t] = 0 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dp(nx , x) ;

		for (int t = 0 ; t <= k ; ++t) tmp[0][t] = tmp[1][t] = tmp[2][t] = 0 ;
		for (int t = 0 ; t <= k ; ++t)
			for (int nt = 0 ; nt <= t ; ++nt)
				tmp[2][t] = (tmp[2][t] + (ll)C[t][nt] * f[1][x][t - nt] % mod * f[1][nx][nt]) % mod ,
				tmp[1][t] = (tmp[1][t] + (ll)C[t][nt] * f[1][x][t - nt] % mod * f[0][nx][nt]) % mod ,
				tmp[0][t] = (tmp[0][t] + (ll)C[t][nt] * f[0][x][t - nt] % mod * f[0][nx][nt]) % mod ,
				tmp[0][t] = (tmp[0][t] + (ll)C[t][nt] * f[0][x][t - nt] % mod * f[1][nx][nt]) % mod ;

		for (int t = 0 ; t <= k ; ++t) {
			f[0][x][t] = tmp[0][t] ; f[1][x][t] = tmp[1][t] ;
			for (int nt = 0 ; nt <= k ; ++nt)
				f[1][x][t] = (f[1][x][t] + (ll)C[t][nt] * tmp[2][nt]) % mod ;
		}
	}
}

int main() {
	freopen("subgraph.in" , "r" , stdin) ;
	freopen("subgraph.out" , "w" , stdout) ;

	n = read() ; m = read() ; k = read() ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		x = read() ; y = read() ;

		ins(x , y) ; ins(y , x) ;
	}

	///

	C[0][0] = 1 ;
	for (int i = 1 ; i <= k ; ++i) {
		C[i][0] = 1 ;
		for (int j = 1 ; j <= k ; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod ;
	}

	dp(1 , 1) ;

	printf("%d\n" , (f[0][1][k] + f[1][1][k]) % mod) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}