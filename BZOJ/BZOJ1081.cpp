#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 65535 + 10 , MAX_L = 16 + 5 ;

char s[MAX_N][MAX_L] ;
int n , b , tot , area ;

char trans(int a) {
	if (a < 10) return a + '0' ;
	else return 'A' + a - 10 ;
}

void strcopy(int a , int b) {
	for (int i = 0 ; i < n ; ++i) s[a][i] = s[b][i] ;
}

int main() {
	scanf("%d %d" , &n , &b) ;
	if (!n) return 0 ;

	for (int i = 0 ; i < b ; ++i) {
		for (int j = 0 ; j < n ; ++j) s[tot][j] = '0' ;
		s[tot++][0] = trans(i) ;
	}

	///

	area = tot ;
	for (int i = 1 ; i < n ; ++i) {
		short sta = 1 ;

		for (int j = 1 ; j < b ; ++j , sta ^= 1) {
			int L , R , a ;
			if (sta) L = area - 1 , R = -1 , a = -1 ;
			else L = 0 , R = area , a = 1 ;

			for (int k = L ; k != R ; k += a) {
				strcopy(tot , k) ;
				s[tot++][i] = trans(j) ;
			}
		}

		area = tot ;
	}

	for (int i = 0 ; i < tot ; ++i) {
		for (int j = 0 ; j < n ; ++j) putchar(s[i][j]) ;
		putchar('\n') ;
	}

	return 0 ;
}