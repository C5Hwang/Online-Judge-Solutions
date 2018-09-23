#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 50 , MAX_L = 1000 + 10 ;

int n , bl , ml ;
bool f[MAX_N][MAX_L] ;

int main() {
	scanf("%d %d %d" , &n , &bl , &ml) ;
	f[0][bl] = 1 ;
	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;

		bool ans = 0 ;
		for (int j = 0 ; j < ml ; ++j) {
			if (!f[i - 1][j]) continue ;

			int L = j - a , R = j + a ;

			if (0 <= L && L <= ml) f[i][L] = 1 , ans = 1 ;
			if (0 <= R && R <= ml) f[i][R] = 1 , ans = 1 ;
		}

		if (!ans) {
			printf("-1\n") ;

			return 0 ;
		}
	}

	int res ;
	for (res = ml ; res >= 0 ; --res)
		if (f[n][res]) break ;

	printf("%d\n" , res) ;

	return 0 ;
}
