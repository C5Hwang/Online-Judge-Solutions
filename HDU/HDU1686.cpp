#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std ;

const int MAX_L = 1000000 + 10 ;

char s1[MAX_L] , s2[MAX_L] ;
int n , m , next[MAX_L] ;

int main() {
	int Q ; scanf("%d" , &Q) ;
	while (Q--) {
		scanf("%s %s" , s1 , s2) ;
		n = strlen(s1) ; m = strlen(s2) ;
		
		///
		
		int k = - 1 ; next[0] = -1 ;
		for (int i = 1 ; i < n ; ++i) {
			while (s1[k + 1] != s1[i] && k >= 0) k = next[k] ;
			
			if (s1[i] == s1[k + 1]) ++k ;
			next[i] = k ;
		}
		
		k = -1 ; int res = 0 ;
		for (int i = 0 ; i < m ; ++i) {
			while (s1[k + 1] != s2[i] && k >= 0) k = next[k] ;
			
			if (s1[k + 1] == s2[i]) ++k ;
			if (k + 1 == n) ++res ;
		}
		
		printf("%d\n" , res) ;
	}
	
	
	return 0 ;
}
