#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 30 + 5 ;

char s[MAX_N] ;
int T , D , len , dmg[MAX_N] ;

bool check() {
	int sum = 0 ;
	for (int i = 0 ; i < len ; ++i) if (s[i] == 'S') ++sum ;

	return sum <= D ;
}

int getans() {
	int ans = 0 , shoot = 0 , d = 1 ;

	for (int i = 0 ; i < len ; ++i) {
		if (s[i] == 'C') d <<= 1 ;
		else dmg[i] = d , shoot += d ;
	}

	for (; shoot > D ;) {
		int p ;
		for (p = len - 1 ; p ; --p)
			if (s[p] == 'S' && s[p - 1] == 'C') break ;

		dmg[p - 1] = dmg[p] >> 1 ;
		shoot += dmg[p - 1] - dmg[p] ;
		std::swap(s[p] , s[p - 1]) ; ++ans ;
	}

	return ans ;
}

int main() {
	scanf("%d" , &T) ;
	for (int CASE = 1 ; T-- ; ++CASE) {
		scanf("%d %s" , &D , s) ;
		len = strlen(s) ;

		if (check()) printf("Case #%d: %d\n" , CASE , getans()) ;
		else printf("Case #%d: IMPOSSIBLE\n" , CASE) ;
	}

	return 0 ;
}