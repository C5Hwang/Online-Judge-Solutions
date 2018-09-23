#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 1e3 + 10 , MAX_M = 100 + 10 , MAX_L = 1e3 + 10 ;

int n , m , len[MAX_M] , point[MAX_M] ;
char st[MAX_N][MAX_L] , er[MAX_M][MAX_M] ;

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) scanf("%s" , st[i]) ;
	for (int i = 0 ; i < m ; ++i) scanf("%s" , er[i]) , len[i] = strlen(er[i]) ;

	///
	
	for (int i = 0 ; i < n ; ++i) {
		memset(point , 0 , sizeof(point)) ;

		int L = strlen(st[i]) , res = 0 ;
		for (int j = 0 ; j < L ; ++j) {
			for (int k = 0 ; k < m ; ++k) {
				if (point[k] == len[k]) continue ;
				char c1 = st[i][j] , c2 = er[k][point[k]] ;
				if (c1 <= 'Z') c1 += ('a' - 'A') ;
				if (c2 <= 'Z') c2 += ('a' - 'A') ;
				if (c1 == c2) ++point[k] ;

				if (point[k] == len[k]) ++res ;
			}
		}

		printf("%d\n" , res) ;
	}

	return 0 ;
}
