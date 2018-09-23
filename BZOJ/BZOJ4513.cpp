#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int L = 60 , MAX_L = 60 + 5 ;

ll n , m , k ;
int T , P , f[MAX_L][2][2][2] , g[MAX_L][2][2][2] ;

void dp() {
	memset(f , 0 , sizeof(f)) ;
	memset(g , 0 , sizeof(g)) ;

	f[L][1][1][1] = 0 ; g[L][1][1][1] = 1 % P ;

	for (int p = L ; p ; --p)
		for (int x = 0 ; x < 2 ; ++x)
			for (int y = 0 ; y < 2 ; ++y)
				for (int z = 0 ; z < 2 ; ++z)
					for (int a = 0 ; a < 2 ; ++a)
						for (int b = 0 ; b < 2 ; ++b) {
							int c = a ^ b , np = p - 1 ;
							ll num = (ll)1 << np ;

							if (x & ((ll)a << np) > (n & num)) continue ;
							if (y & ((ll)b << np) > (m & num)) continue ;
							if (z & ((ll)c << np) < (k & num)) continue ;

							int st1 , st2 , st3 ;
							st1 = x & (((ll)a << np) == (n & num)) ;
							st2 = y & (((ll)b << np) == (m & num)) ;
							st3 = z & (((ll)c << np) == (k & num)) ;

							num %= P ;
							(g[np][st1][st2][st3] += g[p][x][y][z]) %= P ;
							(f[np][st1][st2][st3] += f[p][x][y][z]) %= P ;
							if (c) f[np][st1][st2][st3] = ((ll)f[np][st1][st2][st3] + (ll)g[p][x][y][z] * num) % P ;
						}
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%lld %lld %lld %d" , &n , &m , &k , &P) ;
		--n ; --m ;

		///

		dp() ;

		///

		int ans = 0 ;
		for (int x = 0 ; x < 2 ; ++x)
			for (int y = 0 ; y < 2 ; ++y)
				for (int z = 0 ; z < 2 ; ++z) {
					int t1 = f[0][x][y][z] , t2 = g[0][x][y][z] ;
					t2 = ((ll)t2 * (k % P)) % P ; t2 = P - t2 ;

					(ans += (t1 + t2) % P) %= P ;
				}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}