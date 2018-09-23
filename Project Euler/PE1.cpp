#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 1e3 + 10 ;

int n , ans ;

int main() {
	ans = 0 ; n = 1e3 ;
	for (int i = 1 ; i < n ; ++i)
		if (!(i % 3) || !(i % 5)) ans += i ;
	printf("%d\n" , ans) ;

	return 0 ;
}
