#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , INF = 0x7FFFFFFF ;

bool check[MAX_N][MAX_N] ;
int n , m , a[MAX_N][MAX_N] , s[MAX_N][MAX_N] ;

int work(int r , int c) {
	for (int i = 0 ; i <= n ; ++i)
		for (int j = 0 ; j <= m ; ++j)
			s[i][j] = 0 ;

	int ti = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] ;
			int num = a[i][j] - s[i][j] , x = i + r - 1 , y = j + c - 1 ;
			ti += num ;

			if (num < 0) return -1 ;
			if (num > 0 && x > n && y > m) return -1 ;
			s[i][j] += num ; s[i][y + 1] -= num ; s[x + 1][j] -= num ; s[x + 1][y + 1] += num ;
		}

	return ti ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j)
			scanf("%d" , &a[i][j]) ;

	///
	
	int ans = INF ;
	for (int i = 1 ; i <= n ; ++i)
		for (int j = 1 ; j <= m ; ++j) {
			if (check[i][j]) continue ;
			int res = work(i , j) ;

			if (res >= 0) ans = std::min(ans , res) ;
			else {
				for (int x = i << 1 , y = j << 1 ; x <= n && y <= m ; x += i , y += j)
					check[x][y] = 1 ;
			}
		}
	printf("%d\n" , ans) ;

	return 0 ;
}
