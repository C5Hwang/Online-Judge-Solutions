#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 200 + 10 ;

char mp[MAX_N][MAX_N] ;
int n , m , sum[MAX_N][MAX_N] ;

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i)
		scanf("%s" , mp[i]) ;

	///
	
	for (int i = 0 ; i < n ; ++i) {
		sum[i][0] = mp[i][0] == 'X' ? 1 : 0 ; 
		for (int j = 1 ; j < m ; ++j)
			if (mp[i][j] == 'X') sum[i][j] = sum[i][j - 1] + 1 ;
			else sum[i][j] = sum[i][j - 1] ;
	}

	///
	
	int res = 0 ;
	for (int l1 = 0 ; l1 < m ; ++l1)
		for (int l2 = l1 ; l2 < m ; ++l2) {
			int minp = -1 , maxp = -1 ;

			for (int i = 0 ; i < n ; ++i) {
				if (mp[i][l1] == 'X' || mp[i][l2] == 'X') {minp = -1 ; maxp = -1 ; continue ;}

				int cle = sum[i][l2] - (l1 > 0 ? sum[i][l1 - 1] : 0) ;
				if (!cle) {
					if (minp == -1) minp = i ;
					else minp = std::min(minp , i) ;

					if (maxp == -1) maxp = i ;
					else maxp = std::max(maxp , i) ;

					res = std::max(res , (maxp - minp + 1) * (l2 - l1 + 1)) ;
				}
			}
		}

	printf("%d\n" , res) ;

	return 0 ;
}
