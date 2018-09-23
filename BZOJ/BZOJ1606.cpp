#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 5000 + 10 , MAX_C = 5e4 + 10 ;

int n , C ;
bool f[MAX_C] ;

int main() {
	scanf("%d %d" , &C , &n) ; f[0] = 1 ;

	for (int i = 0 ; i < n ; ++i) {
	   	int a ; scanf("%d" , &a) ;

		for (int j = a ; j <= C ; ++j) f[j] = f[j] | f[j - a] ;
	}

	for (int i = C ; i >= 0 ; --i)
		if (f[i]) {printf("%d\n" , i) ; break ;}

	return 0 ;
}
