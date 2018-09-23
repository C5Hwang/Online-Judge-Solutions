#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 200 + 10 ;

int n , m , sum , ans ;

int main() {
	scanf("%d" , &n) ; sum = m = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		int a ; scanf("%d" , &a) ;
		if (a >= 90) sum += a , ++m ;
	}

	///

	ans = round(sum * 100.0 / m) ;
	printf("%d.%d%d\n" , ans / 100 , (ans % 100) / 10 , ans % 10) ;

	return 0 ;
}