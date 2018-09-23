#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 10 + 10 , MAX_M = 50 + 10 , INF = 0x3f3f3f3f ;

bool S[MAX_M] , T[MAX_N][MAX_M] ;

int st[MAX_M] , rt[MAX_M] , point[MAX_M] ;
int n , m , mem[MAX_N] , am[MAX_N] , ct[MAX_N] ;
int lx[MAX_M] , ly[MAX_N][MAX_M] , left[MAX_N][MAX_M] , slack[MAX_N][MAX_M] , w[MAX_M][MAX_N][MAX_M] ;

bool match(int x) {
	S[x] = 1 ;
	for (int n1 = 1 ; n1 <= n ; ++n1)
		for (int n2 = 1 ; n2 <= m ; ++n2) {
			if (T[n1][n2] || w[x][n1][n2] == -INF) continue ;

			if (lx[x] + ly[n1][n2] == w[x][n1][n2]) {
				T[n1][n2] = 1 ;
				if (!left[n1][n2] || match(left[n1][n2])) {left[n1][n2] = x ; return 1 ;}
			}
			else slack[n1][n2] = std::min(slack[n1][n2] , lx[x] + ly[n1][n2] - w[x][n1][n2]) ;
		}

	return 0 ;
}

void update() {
	int a = INF ;
	for (int n1 = 1 ; n1 <= n ; ++n1)
		for (int n2 = 1 ; n2 <= m ; ++n2)
			if (!T[n1][n2]) a = std::min(a , slack[n1][n2]) ;

	for (int i = 1 ; i <= m ; ++i) if (S[i]) lx[i] -= a ;
	for (int n1 = 1 ; n1 <= n ; ++n1)
		for (int n2 = 1 ; n2 <= m ; ++n2) if (T[n1][n2]) ly[n1][n2] += a ;
}

void init() {
	for (int i = 1 ; i <= m ; ++i)
		for (int n1 = 1 ; n1 <= n ; ++n1)
			for (int n2 = 1 ; n2 <= m ; ++n2)
				w[i][n1][n2] = -INF ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int ca = 1 ; n != 0 && m != 0 ; ++ca) {
		init() ;

		for (int i = 1 ; i <= n ; ++i)
			scanf("%d" , &mem[i]) ;

		for (int i = 1 ; i <= m ; ++i) {
			int p , last = -INF ; scanf("%d" , &p) ;
			for (int j = 0 ; j < p ; ++j) scanf("%d %d" , &am[j] , &ct[j]) ;
			
			///
			
			am[p] = INF ;
			for (int j = 0 ; j < p ; ++j)
				for (int n1 = 1 ; n1 <= n ; ++n1) {
					if (mem[n1] < am[j] || am[j + 1] < mem[n1]) continue ;
	
					for (int n2 = 1 ; n2 <= m ; ++n2)
						w[i][n1][n2] = std::max(w[i][n1][n2] , -ct[j] * n2) ;
				}

			///

			lx[i] = -INF ;
			for (int n1 = 1 ; n1 <= n ; ++n1)
				for (int n2 = 1 ; n2 <= m ; ++n2) {
					ly[n1][n2] = left[n1][n2] = 0 ;
					if (w[i][n1][n2] != INF) lx[i] = std::max(lx[i] , w[i][n1][n2]) ;
				}
		}

		///

		for (int i = 1 ; i <= m ; ++i) {
			for (int n1 = 1 ; n1 <= n ; ++n1)
				for (int n2 = 1 ; n2 <= m ; ++n2)
					slack[n1][n2] = INF ;
			for(;;) {
				for (int j = 1 ; j <= m ; ++j) S[j] = 0 ;
				for (int n1 = 1 ; n1 <= n ; ++n1)
					for (int n2 = 1 ; n2 <= m ; ++n2) T[n1][n2] = 0 ;

				if (match(i)) break; else update() ;
			}
		}

		///

		int res = 0 ;
		for (int i = 1 ; i <= m ; ++i) res += -lx[i] ;
		for (int n1 = 1 ; n1 <= n ; ++n1) {
			int sum = 0 ;
			for (int n2 = m ; n2 > 0 ; --n2) {
				res += -ly[n1][n2] ;
				if (left[n1][n2]) {
					int x = left[n1][n2] ;
					st[x] = sum ; point[x] = n1 ; rt[x] = (-lx[x] - ly[n1][n2]) / n2 ;

					sum += rt[x] ;
				}
			}
		}

		printf("Case %d\n" , ca) ;
		printf("Average turnaround time = %0.2lf\n" , (double)res / m) ;
		for (int i = 1 ; i <= m ; ++i)
			printf("Program %d runs in region %d from %d to %d\n" , i , point[i] , st[i] , st[i] + rt[i]) ;
			
		scanf("%d %d" , &n , &m) ;
	}

	return 0 ;
}
