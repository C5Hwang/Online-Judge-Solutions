#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db INF = 1e16 , eps = 1e-8 ;
const int MAX_N = 5e4 + 10 , MAX_K = 100 + 10 ;

db f[MAX_K][MAX_N] ;
int n , m , a[MAX_N] ;
ll s[MAX_N] , ss[MAX_N] ;

db cal(int x , int y) {
	ll len = y - x + 1 , S = s[y] - s[x - 1] , SS = ss[y] - ss[x - 1] ;
	db num = S * 1.0 / len ;

	return SS + num * num * len - 2 * num * S ;
}

void work(int k , int x , int y , int fx , int fy) {
	if (x > y) return ;

	db res = INF ;
	int mid = (x + y) >> 1 , pl = -1 ;
	for (int i = fx ; i <= fy ; ++i) {
		if (i > mid) break ;

		db tmp = f[k - 1][i - 1] + cal(i , mid) ;
		if (tmp - res < eps) res = tmp , pl = i ;
	}
	f[k][mid] = res ;

	work(k , x , mid - 1 , fx , pl) ;
	work(k , mid + 1 , y , pl , fy) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

	std::sort(a + 1 , a + 1 + n) ;
	for (int i = 1 ; i <= n ; ++i)
		s[i] = s[i - 1] + a[i] , ss[i] = ss[i - 1] + (ll)a[i] * a[i] ;

	///

	f[0][0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) f[0][i] = INF ;

	for (int k = 1 ; k <= m ; ++k) {
		for (int x = 0 ; x < k ; ++x) f[k][x] = INF ;

		work(k , k , n , 1 , n) ;
	}

	printf("%0.8lf\n" , f[m][n]) ;

	return 0 ;
}