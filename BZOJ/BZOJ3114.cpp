#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 50 + 10 , MOD = 1e9 + 7 ;

int T , n , p , k , res ;

int times(int x , int y) {
	return (int)(((long long)x * (long long)y) % MOD) ;
}

int main() {
	scanf("%d" , &T) ;
	for (int CASE = 1 ; T ; --T , ++CASE) {
		scanf("%d" , &n) ;

		int N = 1 ;
		res = 1 ;

		for (int i = 0 ; i < n ; ++i) {
			scanf("%d %d" , &p , &k) ;

			int t = 1 , sum = 0 ;
			for (int j = 0 ; j <= k ; ++j) {
				sum = (sum + t) % MOD ;
				if (j < k) t = times(t , p) ;
			}
			sum = (sum + times(t , k)) % MOD ;
			N = times(N , t) ;

			res = times(res , sum) ;
		}

		printf("Case %d: %d\n" , CASE , (res + N) % MOD) ;
	}


	return 0 ;
}
