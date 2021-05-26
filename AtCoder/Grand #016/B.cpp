#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

int n , cnt[MAX_N] ;

int main() {
	scanf("%d" , &n) ;
	int mi = n , ma = -1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		mi = std::min(mi , a) ; ma = std::max(ma , a) ;

		++cnt[a] ;
	}

	///

	bool ok = 0 ;
	if (mi == ma) {
		if (mi == n - 1) ok = 1 ;
		else {
			int k = n >> 1 ;
			if (mi <= k) ok = 1 ;
		}
	}
	else if (mi + 1 == ma) {
		int k = cnt[mi] + (cnt[ma] >> 1) ;
		if (cnt[ma] > 1 && ma <= k && cnt[mi] <= mi) ok = 1 ;
	}

	if (ok) printf("Yes\n") ;
	else printf("No\n") ;

	return 0 ;
}