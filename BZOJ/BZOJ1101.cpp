#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 5e4 + 10 ;

bool vis[MAX_N] ;
int T , n , m , k , cur , miu[MAX_N] , s[MAX_N] , prime[MAX_N] ;

void init() {
	n = 5e4 ;
	miu[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {
			miu[i] = -1 ;
			prime[cur++] = i ;
		}

		for (int j = 0 ; j < cur ; ++j) {
			int temp = i * prime[j] ;
			if (temp > n) break ;

			vis[temp] = 1 ;
			if (i % prime[j]) miu[temp] = -miu[i] ;
			else {miu[temp] = 0 ; break ;}
		}
	}

	s[1] = miu[1] ;
	for (int i = 2 ; i <= n ; ++i) s[i] = s[i - 1] + miu[i] ;
}

int GetAns(int n , int m) {
	if (n > m) std::swap(n , m) ;
	n /= k ; m /= k ;

	int last = 0 , res = 0 ;
	for (int i = 1 ; i <= n ; i = last + 1) {
		int j1 = n / (n / i) , j2 = m / (m / i) ;
		last = std::min(j1 , j2) ;

		res += (s[last] - s[i - 1]) * (n / i) * (m / i) ;
	}

	return res ;
}

int main() {
	init() ;

	scanf("%d" , &T) ;
	while (T--) {
		scanf("%d %d %d" , &n , &m , &k) ;

		printf("%d\n" , GetAns(n , m)) ;
	}

	return 0 ;
}
