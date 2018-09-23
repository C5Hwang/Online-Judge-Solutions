#include <stdio.h>
#include <stdlib.h>

int n ;

int main() {
	scanf("%d" , &n) ;
	while (n != 0) {
		if (n % 2) printf("Bob\n") ;
		else printf("Alice\n") ;

		scanf("%d" , &n) ;
	}

	return 0 ;
}
