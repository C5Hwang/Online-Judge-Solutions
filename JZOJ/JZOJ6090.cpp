#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 500 + 5 ;

int n , P , f[2][MAX_N][MAX_N] , s1[2][MAX_N][MAX_N] , s2[2][MAX_N][MAX_N] ;

inline int mod(int x) {return x >= P ? x - P : x ;}

int main() {
	freopen("yuan.in" , "r" , stdin) ;
	freopen("yuan.out" , "w" , stdout) ;

	scanf("%d %d" , &n , &P) ;

	///

	int np = 1 ;
	for (int i = 1 ; i <= n + 1 ; ++i)
		for (int j = 1 ; j <= n + 1 ; ++j)
			f[0][i][j] = i <= j ? 1 : 0 ,
			s1[0][i][j] = mod(s1[0][i][j - 1] + f[0][i][j]) ,
			s2[0][i][j] = mod(s2[0][i - 1][j] + f[0][i][j]) ;

	for (int x = n - 1 ; x ; --x , np ^= 1) {
		for (int y = 1 ; y <= x + 1 ; ++y)
			for (int z = 1 ; z <= x + 1 ; ++z) {
				if (z < y) {f[np][y][z] = 0 ; continue ;}

				int t1 = mod(P + s2[np^1][y][z + 1] - s2[np^1][1][z + 1]) ,
					t2 = mod(P + s1[np^1][y][z] - s1[np^1][y][y]) ;

				f[np][y][z] = mod(f[np^1][y + 1][z + 1] + mod(t1 + t2)) ;
			}

		for (int y = 1 ; y <= x + 1 ; ++y)
			for (int z = 1 ; z <= x + 1 ; ++z)
				s1[np][y][z] = mod(s1[np][y][z - 1] + f[np][y][z]) ,
				s2[np][y][z] = mod(s2[np][y - 1][z] + f[np][y][z]) ;
	}

	printf("%d\n" , f[np^1][2][2]) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}