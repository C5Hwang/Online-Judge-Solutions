#include <stdio.h>
#include <stdlib.h>

int a , b , c , d , s1 , s2 ;

int main() {
	scanf("%d %d %d %d" , &a , &b , &c , &d) ;
	s1 = a + b ; s2 = c + d ;

	if (s1 > s2) printf("Left\n") ;
	else if (s1 < s2) printf("Right\n") ;
	else printf("Balanced\n") ;

	return 0 ;
}