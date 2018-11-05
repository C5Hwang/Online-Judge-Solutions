#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 , lgN = 20 + 5 , mod = 998244353 ;

struct data {
	int x , y ;
}g[MAX_N] , h[MAX_N] ;

std::vector<data> link[MAX_N] , s1[MAX_N] , s2[MAX_N] ;

int n , q , cur , A[MAX_N] , D[MAX_N] , F[MAX_N] , ad[MAX_N] , f[MAX_N][lgN] , fp[MAX_N] ;

///

data add(data a , data b , int p) {
	data c ;
	c.x = ((ll)a.y * b.y * 2 % mod) * p % mod ;
	c.x = ((ll)c.x + a.x + ((ll)p * b.x % mod)) % mod ;
	c.y = (a.y + (ll)b.y * p) % mod ;

	return c ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int jump(int x , int d) {
	int y = x ;

	for (int i = 0 ; (1 << i) <= d ; ++i)
		if ((1 << i) & d) y = f[y][i] ;
	return y ;
}

void dfs(int x) {
	int len = link[x].size() ;

	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].x ;
		if (nx == f[x][0]) continue ;

		f[nx][0] = x ; fp[nx] = link[x][i].y ;
		dfs(nx) ;
	}
}

void count(int x) {
	int len = link[x].size() ;

	F[x] = ad[x] ;
	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].x ;
		if (nx == f[x][0]) continue ;

		count(nx) ;
		(F[x] += F[nx]) %= mod ;
	}
}

///

void dp_g(int x) {
	g[x] = (data){(ll)F[x] * F[x] % mod , F[x]} ;

	int len = link[x].size() ;
	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].x , p = link[x][i].y ;
		if (nx == f[x][0]) continue ;

		dp_g(nx) ;
		g[x] = add(g[x] , g[nx] , p) ;
	}
}

void dp_h(int x) {
	int len = link[x].size() ;
	s1[x].resize(len) ; s2[x].resize(len) ;

	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].x , p = link[x][i].y ;
		if (nx == f[x][0]) {
			if (!i) s1[x][i] = (data){0 , 0} ;
			else s1[x][i] = s1[x][i - 1] ;

			continue ;
		}

		data last = i ? s1[x][i - 1] : (data){0 , 0} ;
		s1[x][i] = add(last , g[nx] , p) ;
	}

	for (int i = len - 1 ; i >= 0 ; --i) {
		int nx = link[x][i].x , p = link[x][i].y ;
		if (nx == f[x][0]) {
			if (i == len - 1) s2[x][i] = (data){0 , 0} ;
			else s2[x][i] = s2[x][i + 1] ;

			continue ;
		}

		data last = i == len - 1 ? (data){0 , 0} : s2[x][i + 1] ;
		s2[x][i] = add(last , g[nx] , p) ;
	}

	///

	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].x , p = link[x][i].y ;
		if (nx == f[x][0]) continue ;

		h[nx] = (data){(ll)F[x] * F[x] % mod , F[x]} ;
		h[nx] = add(h[nx] , h[x] , fp[x]) ;
		if (i) h[nx] = add(h[nx] , s1[x][i - 1] , 1) ;
		if (i < len - 1) h[nx] = add(h[nx] , s2[x][i + 1] , 1) ;

		dp_h(nx) ;
	}
}

///

int main() {
	freopen("travel.in" , "r" , stdin) ;
	freopen("travel.out" , "w" , stdout) ;

	n = read() ;
	for (int i = 1 ; i <= n ; ++i) A[i] = read() , D[i] = read() ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ; x = read() ; y = read() ; v = read() ;

		link[x].push_back((data){y , v}) ;
		link[y].push_back((data){x , v}) ;
	}

	///

	f[1][0] = 1 ;
	dfs(1) ;
	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i)
			f[i][j] = f[f[i][j -1]][j - 1] ;

	for (int i = 1 ; i <= n ; ++i) {
		int j = jump(i , D[i]) ;

		(ad[i] += A[i]) %= mod ;
		if (j != 1) {
			j = f[j][0] ;
			ad[j] = (ad[j] + mod - A[i]) % mod ;
		}
	}
	count(1) ;

	///

	dp_g(1) ;
	h[1] = (data){0 , 0} ;
	dp_h(1) ;

	///

	q = read() ;
	for (int i = 0 ; i < q ; ++i) {
		int x = read() ;
		data ans = add(g[x] , h[x] , fp[x]) ;

		printf("%d\n" , ans.x) ;
	}

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}