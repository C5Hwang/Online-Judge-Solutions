#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 16 + 10 , MAX_STA = (1 << 16) + 10 , INF = 0x3f3f3f3f ;

struct data {
	int t , w ;
}a[MAX_N] , sta[MAX_STA] ;

int maxW , n , f[MAX_STA] ;

int main() {
	scanf("%d %d" , &maxW , &n) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%d %d" , &a[i].t , &a[i].w) ;

	///
	
	for (int i = 0 ; i <= (1 << n) ; ++i)
		for (int j = 0 ; j < n ; ++j)
			if ((1 << j) & i) {
				sta[i].w += a[j].w ;
				sta[i].t = std::max(sta[i].t , a[j].t) ;
			}

	///
	
	f[0] = 0 ;
	for (int i = 1 ; i < (1 << n) ; ++i) {
		f[i] = INF ;
		for (int S = i ; S > 0 ; S = (S - 1) & i) {
			if (sta[S].w > maxW) continue ;

			f[i] = std::min(f[i - S] + sta[S].t , f[i]) ;
		}
	}

	printf("%d\n" , f[(1 << n) - 1]) ;

	return 0 ;
}
