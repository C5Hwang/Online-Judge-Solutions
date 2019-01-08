#include <map>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e6 + 10 , MAX_T = 10 + 5 , MAX_NUM = 1e7 + 10 ;

std::map<int , int> p1 , p2 ;

bool vis[MAX_NUM] ;
int n , pre[MAX_N] , last[MAX_N] , fa[MAX_N] ;
int tot , pri[MAX_N] , fir[MAX_NUM] , cnt[MAX_N] , P[MAX_N][MAX_T] ;

bool check(int p , int x , int y) {
	return pre[p] < x && y < last[p] ;
}

bool solve(int f , int x , int y) {
	if (x > y) return 1 ;

	int p = -1 ;
	for (int i = x ; i <= y ; ++i) {
		int j = y - i + x ;
		if (i > j) break ;

		if (check(i , x , y)) {p = i ; break ;}
		else if (check(j , x , y)) {p = j ; break ;}
	}

	if (p == -1) return 0 ;

	fa[p] = f ;
	return solve(p , x , p - 1) && solve(p , p + 1 , y) ;
}

void initpri() {
	int N = 1e7 ;
	for (int i = 2 ; i <= N ; ++i) {
		if (!vis[i]) pri[tot++] = i , fir[i] = i ;

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = pri[j] * i ;
			if (tmp > N) break ;

			vis[tmp] = 1 ; fir[tmp] = pri[j] ;
			if (!(i % pri[j])) break ;
		}
	}
}

int main() {
	scanf("%d" , &n) ; initpri() ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;

		for (; a > 1 ;) {
			int t = fir[a] ;
			for (; !(a % t) ; a /= t) ;
			P[i][cnt[i]++] = t ;
		}
	}

	///

	for (int i = 1 ; i <= n ; ++i) {
		int p = 0 , len = cnt[i] ;
		for (int j = 0 ; j < len ; ++j)	{
			if (p1.count(P[i][j])) p = std::max(p , p1[P[i][j]]) ;
			p1[P[i][j]] = i ;
		}
		pre[i] = p ;
	}
	for (int i = n ; i ; --i) {
		int p = n + 1 , len = cnt[i] ;
		for (int j = 0 ; j < len ; ++j) {
			if (p2.count(P[i][j])) p = std::min(p , p2[P[i][j]]) ;
			p2[P[i][j]] = i ;
		}
		last[i] = p ;
	}

	bool ans = solve(0 , 1 , n) ;
	if (ans) for (int i = 1 ; i <= n ; ++i) printf("%d " , fa[i]) ;
	else printf("impossible") ;
	printf("\n") ;

	return 0 ;
}