#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 2500 + 10 ;

int n , inf , f[MAX_N] ;

int main() {
	scanf("%d" , &n) ; inf = n / 2 + n % 2 ;

	for (int i = 1 ; i < inf ; ++i) f[i] = 1 ;
	for (int t = 0 ; t < 3 ; ++t)
		for (int i = n ; i > 0 ; --i) {
			int sum = 0 ;
			for (int j = 1 ; j < inf ; ++j)
				if (i - j > 0) sum += f[i - j] ;
			f[i] = sum ;
		}

	printf("%d\n" , f[n]) ;

	return 0 ;
}
