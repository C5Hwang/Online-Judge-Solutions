#include <bits/stdc++.h>

const int MAX_N = 200 + 10 ;

int n , tot , col[MAX_N] , cnt[MAX_N] , g[MAX_N][MAX_N] ;
bool ch[MAX_N] , fri[MAX_N][MAX_N] , lk[MAX_N][MAX_N] , f[MAX_N][MAX_N] ;

void jump(int x , int y) {
	if (!x) return ;

	int nw = g[x][y] ;
	ch[nw] = 1 ; jump(x - 2 , y - cnt[nw]) ;
}

bool dfs(int x , int t , int f) {
	col[x] = t ; ++cnt[t] ;
	for (int i = 1 ; i <= n ; ++i) {
		if (!lk[x][i] || i == f) continue ;

		if (col[i] != -1) {
			if (col[i] == t) return 0 ;
			continue ;
		}
		if (!dfs(i , t ^ 1 , x)) return 0 ;
	}

	return 1 ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int x ; scanf("%d" , &x) ;
		for (; x ; scanf("%d" , &x)) fri[i][x] = 1 ;
	}

	///

	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= n ; ++j) {
			if (i == j) continue ;
			if (!fri[i][j] || !fri[j][i]) lk[i][j] = 1 ;
		}

	memset(col , -1 , sizeof(col)) ;
	for (int i = 1 ; i <= n ; ++i) {
		if (col[i] != -1) continue ;

		tot += 2 ;
		if (!dfs(i , tot , i)) {printf("No solution\n") ; return 0 ;}
	}

	///

	f[0][0] = 1 ;
	for (int i = 2 ; i <= tot ; i += 2)
		for (int j = 0 ; j <= n ; ++j) {
			int x = i , y = i ^ 1 , cx = cnt[x] , cy = cnt[y] ;

			if (j >= cx && f[i - 2][j - cx]) {
				f[i][j] = 1 ; g[i][j] = x ;
			}
			else if (j >= cy && f[i - 2][j - cy]) {
				f[i][j] = 1 ; g[i][j] = y ;
			}
		}

	int ans = -1 ;
	for (int i = 0 ; i <= n ; ++i) {
		if (!f[tot][i]) continue ;

		int nw = abs(n - i - i) , nans = abs(n - ans - ans) ;
		if (nw < nans) ans = i ;
	}

	///

	jump(tot , ans) ;

	int res = 0 ;
	for (int i = 1 ; i <= n ; ++i) if (ch[col[i]]) ++res ;

	printf("%d " , res) ;
	for (int i = 1 ; i <= n ; ++i) if (ch[col[i]]) printf("%d " , i) ;
	printf("\n") ;

	printf("%d " , n - res) ;
	for (int i = 1 ; i <= n ; ++i) if (!ch[col[i]]) printf("%d " , i) ;
	printf("\n") ;

	return 0 ;
}