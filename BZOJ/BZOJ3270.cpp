#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 20 + 10 , MAX_M = 400 + 10 ;

std::vector<int> eg[MAX_N] ;

int n , m , pa , pb ;
db p[MAX_N] , mat[MAX_M][MAX_M] ;

int bh(int a , int b) {return (a - 1) * n + b ;}

void gauss() {
	for (int i = 1 ; i <= m ; ++i) {
		int r = i ;
		for (int j = i + 1 ; j <= m ; ++j) if (fabs(mat[j][i]) > fabs(mat[r][i])) r = j ;
		if (r != i) for (int j = 1 ; j <= m + 1 ; ++j) std::swap(mat[i][j] , mat[r][j]) ;

		for (int j = i + 1 ; j <= m ; ++j) {
			db tmp = mat[j][i] / mat[i][i] ;
			for (int k = i ; k <= m + 1 ; ++k) mat[j][k] -= mat[i][k] * tmp ;
		}
	}

	for (int i = m ; i ; --i) {
		for (int j = m ; j > i ; --j) mat[i][m + 1] -= mat[i][j] * mat[j][m + 1] ;
		mat[i][m + 1] /= mat[i][i] ;
	}
}

int main() {
	scanf("%d %d %d %d" , &n , &m , &pa , &pb) ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y ; scanf("%d %d" , &x , &y) ;
		eg[x].push_back(y) ; eg[y].push_back(x) ;
	}
	for (int i = 1 ; i <= n ; ++i) scanf("%lf" , &p[i]) ;

	///

	m = n * n ;
	for (int a = 1 ; a <= n ; ++a)
		for (int b = 1 ; b <= n ; ++b) {
			if (a == pa && b == pb) mat[bh(a , b)][m + 1] = -1 ;

			int sa = eg[a].size() , sb = eg[b].size() ;

			for (int i = 0 ; i < sa ; ++i) {
				int c = eg[a][i] ;
				if (c == b) continue ;

				mat[bh(a , b)][bh(c , b)] += (1 - p[c]) * p[b] / eg[c].size() ;
			}
			for (int i = 0 ; i < sb ; ++i) {
				int d = eg[b][i] ;
				if (a == d) continue ;

				mat[bh(a , b)][bh(a , d)] += p[a] * (1 - p[d]) / eg[d].size() ;
			}
			
			for (int i = 0 ; i < sa ; ++i)
				for (int j = 0 ; j < sb ; ++j) {
					int c = eg[a][i] , d = eg[b][j] ;
					if (c == d) continue ;

					mat[bh(a , b)][bh(c , d)] += (1 - p[c]) * (1 - p[d]) / (eg[c].size() * eg[d].size()) ;
				}

			if (a != b) mat[bh(a , b)][bh(a , b)] = p[a] * p[b] - 1 ;
			else mat[bh(a , b)][bh(a , b)] = -1 ;
		}

	gauss() ;

	for (int i = 1 ; i <= n ; ++i) printf("%0.6lf ", mat[bh(i , i)][m + 1]) ;
	printf("\n") ;

	return 0 ;
}