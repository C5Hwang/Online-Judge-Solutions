#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_N = 500 + 10 , INF = 0x3f3f3f3f ;

bool S[MAX_N] , T[MAX_N] ;
int n , w[MAX_N][MAX_N] , lx[MAX_N] , ly[MAX_N] , left[MAX_N] , slack[MAX_N] ;

bool match(int x) {
	S[x] = 1 ;
	for (int nx = 1 ; nx <= n ; ++nx) {
		if (T[nx]) continue ;

		if (lx[x] + ly[nx] != w[x][nx]) slack[nx] = min(slack[nx] , lx[x] + ly[nx] - w[x][nx]) ;
		else {
			T[nx] = 1 ;
			if (!left[nx] || match(left[nx])) {
				left[nx] = x ;
				return 1 ;
			}
		}
	}

	return 0 ;
}

void update() {
	int a = INF ;
	for (int i = 1 ; i <= n ; ++i) if (!T[i]) a = min(a , slack[i]) ;

	for (int i = 1 ; i <= n ; ++i) {
		if (S[i]) lx[i] -= a ;
		if (T[i]) ly[i] += a ;
	}
}

int main() {
	while (scanf("%d" , &n) != EOF) {	
		for (int i = 1 ; i <= n ; ++i) {
			lx[i] = -INF ; ly[i] = left[i] = 0 ;
			for (int j = 1 ; j <= n ; ++j) {
				scanf("%d" , &w[i][j]) ;
				lx[i] = max(lx[i] , w[i][j]) ;
			}
		}
	
		///
		
		for (int i = 1 ; i <= n ; ++i) {
			for (int j = 1 ; j <= n ; ++j) slack[j] = INF ;
			for (;;) {
				for (int j = 1 ; j <= n ; ++j)
					S[j] = T[j] = 0 ;
				if (match(i)) break; else update() ;
			}
		}
	
		///
		
		int res = 0 ;
		for (int i = 1 ; i <= n ; ++i) printf("%d " , lx[i]) , res += lx[i] ;
		printf("\n") ;
		for (int i = 1 ; i <= n ; ++i) printf("%d " , ly[i]) , res += ly[i] ;
		printf("\n%d\n" , res) ;
	}

	return 0 ;
}
