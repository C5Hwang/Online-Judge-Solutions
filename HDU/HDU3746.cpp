#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std ;

const int MAX_L = 100000 + 10 ;

char st[MAX_L] ;
int n , L , Next[MAX_L] ;

int find() {
	memset(Next , 0 , sizeof(Next)) ;
	
	int k = 0 ;
	Next[0] = Next[1] = 0 ;
	for (int i = 2 ; i <= L ; ++i) {
		while (k > 0 && st[k] != st[i - 1]) k = Next[k] ;
		
		if (st[k] == st[i - 1]) ++k ;
		Next[i] = k ;
	}
	
	return L - Next[L] ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , &st) ;
		
		L = strlen(st) ;
		int xh = find() ;
		
		if (xh * 2 >= L) printf("%d\n" , xh * 2 - L) ;
		else if (L % xh != 0) printf("%d\n" , xh - (L % xh)) ;
		else printf("0\n") ;
	}
}
