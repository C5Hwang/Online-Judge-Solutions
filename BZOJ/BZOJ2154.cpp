#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e7 + 10 , mod = 20101009 ;

bool vis[MAX_N] ;
long long res , s[MAX_N] ;
int n , m , cur , miu[MAX_N] , prime[MAX_N] ;

long long SumK(long long x , long long y) {
	--x ;
	long long s1 = (x * (x + 1)) >> 1 , s2 = (y * (y + 1)) >> 1 ;
	s1 %= mod ; s2 %= mod ;

	return (s2 - s1 + mod) % mod ;
}

long long SumS(long long x , long long y) {
	long long s1 = (x * (x + 1)) >> 1 , s2 = (y * (y + 1)) >> 1 ;
	s1 %= mod ; s2 %= mod ;

	return s1 * s2 % mod ;
}

long long SumMiu(int x , int y) {
	--x ;
	return (s[y] - s[x] + mod) % mod ;
}

long long GetF(long long x , long long y) {
	int last = 0 ;
	long long ans = 0 ;
	for (int i = 1 ; i <= x ; i = last + 1) {
		int j1 = x / (x / i) , j2 = y / (y / i) ;
		last = std::min(j1 , j2) ;

		ans = (ans + (SumS(x / i , y / i) * SumMiu(i , last)) % mod) % mod ;
	}

	return ans ;
}

///

void init() {
	int n = 1e7 ;

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
			else {
				miu[temp] = 0 ;
				break ;
			}
		}	
	}

	s[1] = miu[1] ;
	for (long long i = 2 ; i <= n ; ++i) {
		long long temp = (miu[i] * i * i) % mod ;

		s[i] = (s[i - 1] + temp + mod) % mod ;
	}
}

int main() {
	init() ;
	scanf("%d %d" , &n , &m) ;

	///
	
	if (n > m) std::swap(n , m) ;

	int last = 0 ; res = 0 ;
	for (int i = 1 ; i <= n ; i = last + 1) {
		int j1 = n / (n / i) , j2 = m / (m / i) ;
		last = std::min(j1 , j2) ;

		res = (res + (SumK(i , last) * GetF(n / i , m / i)) % mod) % mod ;
	}

	printf("%lld\n" , res) ;

	return 0 ;
}
