#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const double eps = 1e-10 ;
const int MAX_N = 100 + 10 , INF = 0x3f3f3f3f ;

struct point {
	int x , y ;
}p[2 * MAX_N] ;

bool S[MAX_N] , T[MAX_N] ;
int n , left[MAX_N] , res[MAX_N] ;
double dis[MAX_N][MAX_N] , lx[MAX_N] , ly[MAX_N] , slack[MAX_N] ;

int square(int x) {return x * x ;}

bool match(int x) {
	S[x] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		if (T[i]) continue ;

		if (fabs(lx[x] + ly[i] - dis[x][i]) >= eps) slack[i] = min(slack[i] , lx[x] + ly[i] - dis[x][i]) ;
		else {
			T[i] = 1 ;
			if (!left[i] || match(left[i])) {left[i] = x ; return 1 ;}
		}
	}

	return 0 ;
}

void update() {
	double a = INF ;
	for (int i = 1 ; i <= n ; ++i)
		if (!T[i]) a = min(a , slack[i]) ;

	for (int i = 1 ; i <= n ; ++i) {
		if (S[i]) lx[i] -= a ;
		if (T[i]) ly[i] += a ;
	}
}

int main() {
	while (scanf("%d" , &n) != EOF) {
		for (int i = 1 ; i <= 2 * n ; ++i)
			scanf("%d %d" , &p[i].x , &p[i].y) ;

		///

		for (int i = 1 ; i <= n ; ++i) {
			lx[i] = -INF ; ly[i] = left[i] = 0 ;

			for (int j = 1 ; j <= n ; ++j) {
				dis[i][j] = -sqrt(square(p[i].x - p[j + n].x) + square(p[i].y - p[j + n].y)) ;
				lx[i] = max(lx[i] , dis[i][j]) ;
			}
		}

		///
		
		for (int i = 1 ; i <= n ; ++i) {
			for (int j = 1 ; j <= n ; ++j) slack[j] = INF ;
			for (;;) {
				for (int j = 1 ; j <= n ; ++j) S[j] = T[j] = 0 ;
				if (match(i)) break; else update() ;
			}
		}
		for (int i = 1 ; i <= n ; ++i)
			res[left[i]] = i ;
		for (int i = 1 ; i <= n ; ++i)
			printf("%d\n" , res[i]) ;
	}

	return 0 ;
}
