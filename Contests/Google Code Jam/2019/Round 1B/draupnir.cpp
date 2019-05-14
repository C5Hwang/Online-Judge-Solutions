#include <stdio.h>
#include <stdlib.h>

#define ull unsigned long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

ull n1 , n2 ;
int T , W , R[10] ;

int main() {
	scanf("%d %d" , &T , &W) ;
	for (; T-- ;) {
		printf("56\n") ;
		fflush(stdout) ;

		scanf("%llu" , &n1) ;

		R[1] = n1 >> 56 ;
		R[2] = (n1 - ((ull)R[1] << 56)) >> 28 ;

		///

		printf("224\n") ;
		fflush(stdout) ;

		scanf("%llu" , &n2) ;
		R[4] = n2 >> 56 ;
		R[5] = (n2 - ((ull)R[4] << 56)) >> 44 ;
		R[6] = (n2 - ((ull)R[4] << 56) - ((ull)R[5] << 44)) >> 37 ;

		for (int i = 1 ; i <= 6 ; ++i)
			if (i != 3) {int j = 56 / i ; n1 -= (ull)R[i] << j ;}
		R[3] = n1 >> 18 ;

		///

		printf("%d %d %d %d %d %d\n" , R[1] , R[2] , R[3] , R[4] , R[5] , R[6]) ;
		fflush(stdout) ;
		
		int ans ;
		scanf("%d" , &ans) ;
		if (ans == -1) break ;
	}

	return 0 ;
}