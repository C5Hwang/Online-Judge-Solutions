#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 3e3 + 10 , INF = 0x3f3f3f3f ;

char s[MAX_N] ;
int d[10][10] , f[MAX_N][MAX_N][3] ;
int A , B , len1 , len2 , s1[MAX_N] , s2[MAX_N] ;

int trans(char c) {
	if (c == 'A') return 0 ;
	else if (c == 'T') return 1 ;
	else if (c == 'G') return 2 ;
	else return 3 ;
}

int main() {
	scanf("%s" , s) ; len1 = strlen(s) ;
	for (int i = 0 ; i < len1 ; ++i) s1[i + 1] = trans(s[i]) ;
	scanf("%s" , s) ; len2 = strlen(s) ;
	for (int i = 0 ; i < len2 ; ++i) s2[i + 1] = trans(s[i]) ;

	for (int i = 0 ; i < 4 ; ++i)
		for (int j = 0 ; j < 4 ; ++j)
			scanf("%d" , &d[i][j]) ;

	scanf("%d %d" , &A , &B) ;

	///

	for (int i = 0 ; i <= len1 ; ++i)
		for (int j = 0 ; j <= len2 ; ++j) {
			if (!i && !j) {f[i][j][0] = 0 ; f[i][j][1] = f[i][j][2] = -INF ; continue ;}

			if (!i || !j) f[i][j][0] = -INF ;
			else {
				int tmp = std::max(f[i - 1][j - 1][0] , std::max(f[i - 1][j - 1][1] , f[i - 1][j - 1][2])) ;
				f[i][j][0] = tmp + d[s1[i]][s2[j]] ;
			}

			if (!j) f[i][j][1] = -INF ;
			else {
				int t1 = std::max(f[i][j - 1][0] , f[i][j - 1][2]) - A ,
					t2 = f[i][j - 1][1] - B ;

				f[i][j][1] = std::max(t1 , t2) ;
			}

			if (!i) f[i][j][2] = -INF ;
			else {
				int t1 = std::max(f[i - 1][j][0] , f[i - 1][j][1]) - A ,
					t2 = f[i - 1][j][2] - B ;

				f[i][j][2] = std::max(t1 , t2) ;
			}
		}

	int ans = std::max(f[len1][len2][0] , std::max(f[len1][len2][1] , f[len1][len2][2])) ;

	printf("%d\n" , ans) ;

	return 0 ;
}