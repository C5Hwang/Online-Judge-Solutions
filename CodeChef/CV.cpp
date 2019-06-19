#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 100 + 10 ;

int T , n ;
char s[MAX_N] ;

bool check(int x) {
	char t = s[x] ;

	if (t == 'a' || t == 'e' || t == 'i' || t == 'o' || t == 'u') return 1 ;
	return 0 ;
}

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d %s" , &n , s) ;

		int ans = 0 ;
		for (int i = 1 ; i < n ; ++i) if (check(i) && !check(i - 1)) ++ans ;

		printf("%d\n" , ans) ;
	}

	return 0 ;
}