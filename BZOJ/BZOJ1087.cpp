#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 9 + 5 , MAX_S = (1 << 9) + 10 ;

int n , k , S ;
ll f[MAX_N][MAX_N * MAX_N][MAX_S] ;

int main() {
	scanf("%d %d" , &n , &k) ; S = (1 << n) ;

	for (int i = 0 ; i < S ; ++i) {
		int s = i & 1 ;
		bool ok = 1 ;

		for (int j = 1 ; j < n && ok ; ++j) {
			if (!(i & (1 << j))) continue ;

			++s ;
			if (i & (1 << (j - 1))) ok = 0 ;
		}

		if (ok) f[1][s][i] = 1 ;
	}

	///

	for (int i = 2 ; i <= n ; ++i)
		for (int j = 0 ; j <= k ; ++j)
			for (int S1 = 0 ; S1 < S ; ++S1)
				for (int S2 = 0 ; S2 < S ; ++S2) {
					int s = S2 & 1 ;
					bool ok = 1 ;

					for (int k = 1 ; k < n && ok ; ++k) {
						if (!(S2 & (1 << k))) continue ;

						++s ;
						if (S2 & (1 << (k - 1))) ok = 0 ;
					}

					if (S2 & 1)	if ((S1 & 1) || (S1 & 2)) ok = 0 ;
					for (int k = 1 ; k < n && ok ; ++k) {
						if (!(S2 & (1 << k))) continue ;

						for (int p = k - 1 ; p <= k + 1 && ok ; ++p)
							if (S1 & (1 << p)) ok = 0 ;
					}

					if (ok && j >= s) f[i][j][S2] += f[i - 1][j - s][S1] ;
				}

	ll ans = 0 ;
	for (int S1 = 0 ; S1 < S ; ++S1) ans += f[n][k][S1] ;

	printf("%lld\n" , ans) ;

	return 0 ;
}