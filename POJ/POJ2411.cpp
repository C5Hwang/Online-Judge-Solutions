#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 11 + 10 , MAX_POW = (1 << 15) + 10 ;

int n , m ;
bool ava[MAX_POW] ;
long long f[MAX_N][MAX_POW] ;

int main() {
	scanf("%d %d" , &n , &m) ;
	while (n > 0 || m > 0) {
		if (n * m % 2) {printf("0\n") ; scanf("%d %d" , &n , &m) ; continue ;}
		if (n < m) std::swap(n , m) ;

		///

		int pm = 1 << m ;
		for (int i = 0 ; i < pm ; ++i) f[0][i] = 0 ;
		f[0][0] = 1 ;

		for (int i = 0 ; i < pm ; ++i) {
			int num = 0 ; bool ok = 1 ;
			for (int j = 0 ; j < m && ok ; ++j) {
				int x = i & (1 << j) ;

				if (x) {if (num % 2) ok = 0 ; num = 0 ;}
				else ++num ;
			}
			if (num % 2) ok = 0 ;

			ava[i] = ok ;
		}

		///
		
		for (int i = 1 ; i < n ; ++i)
			for (int j = 0 ; j < pm ; ++j) {
				long long sum = 0 ;
				for (int k = 0 ; k < pm ; ++k) {
					bool ok = 1 ; int temp = k ;
					for (int q = 0 ; q < m && ok ; ++q) {
						int x = j & (1 << q) , y = k & (1 << q) ;

						if (x & y) ok = 0 ;
						else if (x) temp += x ;
					}
					ok &= ava[temp] ;
					if (ok) sum += f[i - 1][k] ;
				}

				f[i][j] = sum ;
			}

		///

		long long res = 0 ;
		for (int i = 0 ; i < pm ; ++i) if (ava[i]) res += f[n - 1][i] ;

		printf("%lld\n" , res) ;

		scanf("%d %d" , &n , &m) ;
	}

	return 0 ;
}

