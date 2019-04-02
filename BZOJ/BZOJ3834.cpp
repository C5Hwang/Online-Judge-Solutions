#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

int T , s1 , s2 , w1 , w2 ;

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %d %d %d" , &s1 , &s2 , &w1 , &w2) ;
		--s1 ; --w1 ;

		int n = std::max(s2 , w2) , L = 1 , ans = 1 ;
		for (; L <= n ;) {
			int t1 = s1 / L , t2 = s2 / L , t3 = w1 / L , t4 = w2 / L , R = n ;
			if (t1) R = std::min(R , s1 / t1) ;
			if (t2) R = std::min(R , s2 / t2) ;
			if (t3) R = std::min(R , w1 / t3) ;
			if (t4) R = std::min(R , w2 / t4) ;

			if (t2 > t1 && t4 > t3) ans = R ;
			L = R + 1 ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}