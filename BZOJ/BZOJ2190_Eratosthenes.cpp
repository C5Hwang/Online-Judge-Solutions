#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 40000 + 10 ;

int n , fin[MAX_N] ;

int main() {
	scanf("%d" , &n) ;

	///

	long long sum = 1 ;
	for (int i = 2 ; i < n ; ++i) fin[i] = i ;
	for (int i = 2 ; i < n ; ++i) {
		if (fin[i] == i)
			for (int j = i ; j < n ; j += i) fin[j] = fin[j] / i * (i - 1) ;

		sum += fin[i] ;
	}

	if (n == 1) printf("0\n") ;
	else printf("%lld\n" , sum * 2 + 1) ;

	return 0 ;
}
