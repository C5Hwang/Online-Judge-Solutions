#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 200000 + 10 ;

int n , d , cur , sum ;
long long res , a[MAX_N] , bh[MAX_N] ;

int find(int L , int R , int p) {
	while (L + 1 < R) {
		int mid = (L + R) / 2 ;

		if (sum - bh[mid] + 1 > p) L = mid ;
		else R = mid ;
	}

	if (sum - bh[L] + 1 <= p) return a[L] ;
	return a[R] ;
}

int main() {
	res = cur = sum = 0 ;

	scanf("%d %d" , &n , &d) ;
	for (int i = 0 ; i < n ; ++i) {
		getchar() ;
		char q ; int m ;
		scanf("%c %d" , &q , &m) ;

		if (q == 'A') {
			long long num = (m + res) % d ;
			a[++cur] = num ; bh[cur] = ++sum ;

			while(cur > 1 && a[cur] > a[cur - 1])
				a[cur - 1] = a[cur] , bh[cur - 1] = bh[cur--] ;
		}
		else {
			res = find(1 , cur , m) ;
			printf("%lld\n" , res) ;
		}
	}

	return 0 ;
}
