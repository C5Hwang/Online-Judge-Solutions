#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std ;

const int MAX_L = 110000 + 10 ;

char s[MAX_L] , st[2 * MAX_L] ;
int n , Next[2 * MAX_L] ;

int main() {
	while (scanf("%s" , s) != EOF) {
		n = strlen(s) ;
		
		int L = 0 ; st[0] = '*' ;
		for (int i = 0 ; i < n ; ++i)
			st[++L] = '#' , st[++L] = s[i] ;
		st[++L] = '#' ; st[++L] = '+' ;
		
		///
		
		int p = 1 , res = 0 ; Next[1] = 0 ;
		for (int i = 2 ; i < L ; ++i) {
			int u = p + Next[p] , r = max(0 , min(Next[2 * p - i] , u - i)) ;
			
			for (; st[i + r + 1] == st[i - r - 1] ; ++r) ;
			
			if (i + r > u) p = i ;
			Next[i] = r ;
			
			res = max(res , Next[i]) ;
		}
		
		printf("%d\n" , res) ;
	}
	
	return 0 ;
}
