#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

char s[20] ;
int n , m , L , st1 , st2 , ans , atk ;

int main() {
	scanf("%d %d" , &n , &m) ;
	L = 30 ; st1 = (1 << L) - 1 ;

	for (int i = 0 ; i < n ; ++i) {
		int a ; scanf("%s %d" , s , &a) ;

		if (s[0] == 'A') st1 &= a , st2 &= a ;
		else if (s[0] == 'O') st1 |= a , st2 |= a ;
		else st1 ^= a , st2 ^= a ;
	}

	///

	for (int i = L ; i >= 0 ; --i) {
		if (((1 << i) | atk) > m) {ans |= (st2 & (1 << i)) ; continue ;}

		if ((st1 & (1 << i)) > (st2 & (1 << i))) atk |= (1 << i) , ans |= (1 << i) ;
		else ans |= (st2 & (1 << i)) ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}