#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e3 + 10 , MAX_V = 300 + 10 , INF = 0x3f3f3f3f ;

struct data {
	int x , y ;
	double p ;
}cls[MAX_N] ;

double f[MAX_N][MAX_N][2] ;
int n , m , v , e , dis[MAX_V][MAX_V] ;

int main() {
	scanf("%d %d %d %d" , &n , &m , &v , &e) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &cls[i].x) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d" , &cls[i].y) ;
	for (int i = 0 ; i < n ; ++i) scanf("%lf" , &cls[i].p) ;

	for (int i = 1 ; i <= v ; ++i)
		for (int j = 1 ; j <= v ; ++j)
			if (i != j) dis[i][j] = INF ;
	for (int i = 0 ; i < e ; ++i) {
		int x , y , a ; scanf("%d %d %d" , &x , &y , &a) ;
		dis[x][y] = dis[y][x] = std::min(dis[x][y] , a) ;
	}

	///
	
	for (int k = 1 ; k <= v ; ++k)
		for (int i = 1 ; i <= v ; ++i)
			for (int j = 1 ; j <= v ; ++j)
				dis[i][j] = std::min(dis[i][j] , dis[i][k] + dis[k][j]) ;

	///
	
	for (int j = 0 ; j <= m ; ++j) f[0][j][0] = f[0][j][1] = INF ;
	f[0][0][0] = 0 ; if (m > 0) f[0][1][1] = 0 ;

	for (int i = 1 ; i < n ; ++i) {
		data *c1 = &cls[i - 1] , *c2 = &cls[i] ;

		f[i][0][1] = INF ;
		f[i][0][0] = f[i - 1][0][0] + dis[c1->x][c2->x] ;
		for (int j = 1 ; j <= m ; ++j) {
			double s1 , s2 ;

			//no query
			s1 = f[i - 1][j][0] + dis[c1->x][c2->x] ;
			s2 = f[i - 1][j][1] + (dis[c1->x][c2->x]) * (1 - c1->p) + (dis[c1->y][c2->x]) * c1->p ;
			f[i][j][0] = std::min(s1 , s2) ;

			//query
			s1 = f[i - 1][j - 1][0] + (dis[c1->x][c2->x]) * (1 - c2->p) + (dis[c1->x][c2->y]) * c2->p ;
			s2 = f[i - 1][j - 1][1] + (dis[c1->x][c2->x]) * (1 - c1->p) * (1 - c2->p) +
				 (dis[c1->x][c2->y]) * (1 - c1->p) * c2->p + (dis[c1->y][c2->x]) * c1->p * (1 - c2->p) +
				 (dis[c1->y][c2->y]) * c1->p * c2->p ;
			f[i][j][1] = std::min(s1 , s2) ;
		}
	}

	double res = INF ;
	for (int i = 0 ; i <= m ; ++i) res = std::min(res , std::min(f[n - 1][i][0] , f[n - 1][i][1])) ;
	printf("%0.2lf\n" , res) ;

	return 0 ;
}
