#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

int m ;

long long GetTime(int p , long long a) {
	if (p == 2) return a ;

	--p ;

	long long sum = 0 ; int sqp = (int)sqrt(p) ;
	for (int i = 2 ; i <= sqp ; ++i) {
		int at = 0 ;
		while (!(p % i)) p /= i , ++at ;

		if (at > 0) sum += GetTime(i , at * a) ;
	}
	if (p > 1) sum += GetTime(p , a) ;

	return sum ;
}

int main() {
	int T ; scanf("%d" , &T) ;
	while (T--) {
		scanf("%d" , &m) ;
		long long res = 0 , add = 1 ;
		for (int i = 0 ; i < m ; ++i) {
			int p ; long long a ;
			scanf("%d %lld" , &p , &a) ;

			if (p == 2) add = 0 ;

			///

		   	long long ti = GetTime(p , a) ;
			res += ti ;
		}

		printf("%lld\n" , res + add) ;
	}

	return 0 ;
}
