#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 ;

struct data {int num , val ;} ;

std::vector<data> link[MAX_N] ;
std::vector<db> s1[MAX_N] , s2[MAX_N] ;

db f[MAX_N] , g[MAX_N] ;
int n , p[MAX_N] , fp[MAX_N] ;

void merge(db &x , db y , int p) {
	x += (1 - x) * y * (p / 100.0) ;
}

void dp_f(int x , int fa) {
	int len = link[x].size() ;

	f[x] = p[x] / 100.0 ;
	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].num , p = link[x][i].val ;
		if (nx == fa) continue ;

		fp[nx] = p ;
		dp_f(nx , x) ;
		merge(f[x] , f[nx] , p) ;
	}
}

void dp_g(int x , int fa) {
	int len = link[x].size() ;
	s1[x].resize(len) ; s2[x].resize(len) ;

	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].num , p = link[x][i].val ;
		if (nx == fa) {
			if (!i) s1[x][i] = 0 ;
			else s1[x][i] = s1[x][i - 1] ;

			continue ;
		}

		s1[x][i] = i ? s1[x][i - 1] : 0 ;
		merge(s1[x][i] , f[nx] , p) ;
	}
	for (int i = len - 1 ; i >= 0 ; --i) {
		int nx = link[x][i].num , p = link[x][i].val ;
		if (nx == fa) {
			if (i == len - 1) s2[x][i] = 0 ;
			else s2[x][i] = s2[x][i + 1] ;

			continue ;
		}

		s2[x][i] = i == len - 1 ? 0 : s2[x][i + 1] ;
		merge(s2[x][i] , f[nx] , p) ;
	}

	///

	for (int i = 0 ; i < len ; ++i) {
		int nx = link[x][i].num ;
		if (nx == fa) continue ;

		g[nx] = p[x] / 100.0 ;
		merge(g[nx] , g[x] , fp[x]) ;
		if (i) merge(g[nx] , s1[x][i - 1] , 100) ;
		if (i != len - 1) merge(g[nx] , s2[x][i + 1] , 100) ;

		dp_g(nx , x) ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int a , b , c ;
		scanf("%d %d %d" , &a , &b , &c) ;

		link[a].push_back((data){b , c}) ;
		link[b].push_back((data){a , c}) ;
	}
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &p[i]) ;

	///

	dp_f(1 , 1) ;
	dp_g(1 , 1) ;

	db ans = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		db tmp = f[i] ;
		merge(tmp , g[i] , fp[i]) ;
		ans += tmp ;
	}

	printf("%0.6lf\n" , ans) ;

	return 0 ;
}