#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_L = 30 + 5 , L = 30 ;

int n , cnt[2][MAX_L] ;

void add(int x) {
	for (int i = 0 ; i <= L ; ++i)
		if (x & (1 << i)) ++cnt[1][i] ;
		else ++cnt[0][i] ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 0 ; i < n ; ++i) {
		int a ; scanf("%d" , &a) ;

		add(a) ;
	}

	int ans = 0 ;
	for (int i = 0 ; i <= L ; ++i)
		if (cnt[1][i] > cnt[0][i]) ans |= (1 << i) ;

	printf("%d\n" , ans) ;

	return 0 ;
}