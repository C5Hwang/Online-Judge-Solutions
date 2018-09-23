#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 15 + 10 , INF = 0x3f3f3f3f ;

struct Query {
	int x , y ;
}que[MAX_N] ;

bool S[MAX_N] , T[MAX_N] ;
int n , cur , left[MAX_N] , lx[MAX_N] , ly[MAX_N] , slack[MAX_N] , w[MAX_N][MAX_N] ;

bool match(int x) {
	S[x] = 1 ;
	for (int nx = 1 ; nx <= n ; ++nx) {
		if (T[nx]) continue ;

		if (lx[x] + ly[nx] == w[x][nx]) {
			T[nx] = 1 ;
			if (!left[nx] || match(left[nx])) {left[nx] = x ; return 1 ;}
		}
		else slack[nx] = std::min(slack[nx] , lx[x] + ly[nx] - w[x][nx]) ;
	}

	return 0 ;
}

void update() {
	int a = INF ;
	for (int i = 1 ; i <= n ; ++i)
		if (!T[i]) a = std::min(a , slack[i]) ;

	for (int i = 1 ; i <= n ; ++i) {
		if (S[i]) lx[i] -= a ;
		if (T[i]) ly[i] += a ;
	}
}

int KM() {
	for (int i = 1 ; i <= n ; ++i) {
		lx[i] = -INF ; ly[i] = left[i] = 0 ;
		for (int j = 1 ; j <= n ; ++j)
			lx[i] = std::max(lx[i] , w[i][j]) ;
	}

	for (int i = 1 ; i <= n ; ++i) {
		for (int j = 1 ; j <= n ; ++j) slack[j] = INF ;

		for (;;) {
			for (int j = 1 ; j <= n ; ++j) S[j] = T[j] = 0 ;

			if (match(i)) break; else update() ;
		}
	}
	
	int sum = 0 ;
	for (int i = 1 ; i <= n ; ++i) sum += lx[i] , sum += ly[i] ;
	
	return sum ;
}

int main() {
	scanf("%d" , &n) ;
	for (int caseNUM = 1 ; n != 0 ; ++caseNUM) {
		for (int i = 1 ; i <= n ; ++i)
			scanf("%d %d" , &que[i].x , &que[i].y) ;

		///
		
		int ans = -INF ;
		for (int state = 0 ; state < 3 ; ++state) {
			int end = !state ? 2 : n ;
			for (int i = 1 ; i <= end ; ++i) {
				int dx , dy , x , y ;
				if (!state) dx = x = 1 , dy = (i == 1) ? 1 : -1 , y = (i == 1) ? 1 : n ;
				else if (state == 1) dx = 1 , dy = 0 , x = 1 , y = i ;
				else dx = 0 , dy = 1 , x = i , y = 1 ;

				///

				for (int ti = 1 ; ti <= n ; ++ti) {
					for (int j = 1 ; j <= n ; ++j) {
						int nx = que[j].x , ny = que[j].y ;

						w[j][ti] = -abs(x - nx) - abs(y - ny) ;
					}

					x += dx ; y += dy ;
				}

				int res = KM() ;
				ans = std::max(ans , res) ;
			}
		}

		printf("Board %d: %d moves required.\n\n" , caseNUM , -ans) ;

		scanf("%d" , &n) ;
	}

	return 0 ;
}
