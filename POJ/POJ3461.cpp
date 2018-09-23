#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std ;

const int MAX_N = 1000000 + 10 ;

char s1[MAX_N] , s2[MAX_N] ;
int Q , n , m , next[MAX_N] ;

int main() {
	scanf("%d" , &Q) ;
	while (Q--) {
		scanf("%s %s" , &s1 , &s2) ;
		n = strlen(s1) ; m = strlen(s2) ;
		
		///
		
		int k = -1 ;
		next[0] = -1 ;
		for (int i = 1 ; i < n ; ++i) {
			while (k > -1 && s1[i] != s1[k + 1]) k = next[k] ;
			if (s1[i] == s1[k + 1]) ++k ;
			
			next[i] = k ;
		}
		
		///
		
		int res = 0 ;
		k = -1 ;
		for (int i = 0 ; i < m ; ++i) {
			while (k > -1 && s2[i] != s1[k + 1]) k = next[k] ;
			if (s2[i] == s1[k + 1]) ++k ;
			
			if (k == n - 1) ++res ;
		}
		
		printf("%d\n" , res) ;
	}
	return 0 ;
}
