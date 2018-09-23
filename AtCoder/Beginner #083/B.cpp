#include <stdio.h>
#include <stdlib.h>

int n , a , b , ans ;

bool check(int x) {
	int s = 0 ;
	for (; x ; x /= 10) {
		int tmp = x % 10 ;
		s += tmp ;
	}

	return a <= s && s <= b ;
}

int main() {
	scanf("%d %d %d" , &n , &a , &b) ;
	for (int i = 1 ; i <= n ; ++i)
		if (check(i)) ans += i ;

	printf("%d\n" , ans) ;

	return 0 ;
}