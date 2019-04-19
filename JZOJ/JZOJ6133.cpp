#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 , MAX_M = 400 + 10 ;

int tot , tmp[MAX_M] , pl[MAX_M] ;
int n , m , W , h[MAX_N] , x[MAX_M] , y[MAX_M] , cnt[MAX_M] , f[MAX_M][MAX_M] ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	freopen("friend.in" , "r" , stdin) ;
	freopen("friend.out" , "w" , stdout) ;

	n = read() ; m = read() ; W = read() ;
	for (int i = 1 ; i <= n ; ++i) h[i] = W - read() ;
	for (int i = 1 ; i <= m ; ++i) {
		int p , j ; p = read() ; j = read() ;

		for (x[i] = p ; x[i] > 1 && h[x[i]] < j ; --x[i]) ;
		for (y[i] = p ; y[i] < n && h[y[i]] < j ; ++y[i]) ;

		tmp[++tot] = x[i] ; tmp[++tot] = y[i] ;
	}

	///

	int o = 0 ;
	std::sort(tmp + 1 , tmp + 1 + tot) ;

	pl[++o] = tmp[1] ;
	for (int i = 2 ; i <= tot ; ++i)
		if (tmp[i] != tmp[i - 1]) pl[++o] = tmp[i] ;

	for (int i = 1 ; i <= m ; ++i) {
		for (int j = 1 ; j <= o ; ++j) if (x[i] == pl[j]) {x[i] = j ; break ;}
		for (int j = 1 ; j <= o ; ++j) if (y[i] == pl[j]) {y[i] = j ; break ;}
	}

	///

	for (int L = 1 ; L <= o ; ++L)
		for (int i = 1 ; i <= o ; ++i) {
			int j = i + L - 1 ;
			if (j > o) break ;

			for (int k = i ; k <= j ; ++k) cnt[k] = 0 ;
			for (int k = 1 ; k <= m ; ++k)
				if (i <= x[k] && y[k] <= j) {++cnt[x[k]] ; if (y[k] < j) --cnt[y[k] + 1] ;}

			for (int k = i + 1 ; k <= j ; ++k) cnt[k] += cnt[k - 1] ;
			for (int k = i ; k <= j ; ++k)
				f[i][j] = std::max(f[i][j] , f[i][k - 1] + f[k + 1][j] + ((cnt[k] * cnt[k] - cnt[k]) >> 1)) ;
		}

	printf("%d\n" , f[1][o]) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}