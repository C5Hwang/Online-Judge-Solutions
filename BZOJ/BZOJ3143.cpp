#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 500 + 10 , MAX_M = 25e4 + 10 ;

struct Edge{int x , y ; db E ;}eg[MAX_M] ;

std::vector<int> e[MAX_N] ;

int n , m , d[MAX_N] ;
db mat[MAX_N][MAX_N] ;

bool cmp(Edge a , Edge b) {return a.E > b.E ;}

void gauss() {
	for (int i = 1 ; i <= n ; ++i) {
		int r = i ;
		for (int j = i + 1 ; j <= n ; ++j) if (fabs(mat[j][i]) > fabs(mat[r][i])) r = j ;
		if (r != i) for (int j = 1 ; j <= n + 1 ; ++j) std::swap(mat[i][j] , mat[r][j]) ;

		for (int j = i + 1 ; j <= n ; ++j) {
			db tmp = mat[j][i] / mat[i][i] ;
			for (int k = i ; k <= n + 1 ; ++k) mat[j][k] -= mat[i][k] * tmp ;
		}
	}

	for (int i = n ; i ; --i) {
		for (int j = n ; j > i ; --j) mat[i][n + 1] -= mat[i][j] * mat[j][n + 1] ;
		mat[i][n + 1] /= mat[i][i] ;
	}
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		eg[i] = (Edge){x , y} ; e[x].push_back(y) ; e[y].push_back(x) ;
	}

	///

	mat[1][n + 1] = -1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int s = e[i].size() ;
		mat[i][i] -= 1 ;

		for (int j = 0 ; j < s ; ++j) {
			int t = e[i][j] ;
			if (t != n) mat[i][t] += 1.0 / e[t].size() ;
		}
	}

	gauss() ;

	///

	for (int i = 0 ; i < m ; ++i) {
		int x = eg[i].x , y = eg[i].y ;
		if (x != n) eg[i].E += mat[x][n + 1] / e[x].size() ;
		if (y != n) eg[i].E += mat[y][n + 1] / e[y].size() ;
	}

	std::sort(eg + 0 , eg + m , cmp) ;

	db ans = 0 ;
	for (int i = 0 ; i < m ; ++i) ans += eg[i].E * (i + 1) ;

	printf("%0.3lf\n" , ans) ;

	return 0 ;
}