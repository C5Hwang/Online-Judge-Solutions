#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

int n , nw , cnt ;

int main() {
	scanf("%d" , &n) ;

	nw = -1 ; cnt = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		int a ; scanf("%d" , &a) ;

		if (a != nw) --cnt ;
		else ++cnt ;

		if (cnt < 0) {nw = a ; cnt = 1 ;}
	}

	printf("%d\n" , nw) ;

	return 0 ;
}