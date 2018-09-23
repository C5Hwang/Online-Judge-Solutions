#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ull unsigned long long

const int MAX_N = 1e4 + 10 , MAX_L = 2e3 + 10 ;

std::map<ull , bool> ap ;

int n ;
ull base ;
char st[MAX_L] ;

ull gethash() {
	ull h = 0 ;
	int len = strlen(st) ;

	for (int i = 0 ; i < len ; ++i) h = h * base + st[i] ;

	return h ;
}

int main() {
	base = 1003 ;

	scanf("%d" , &n) ;

	int ans = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , st) ;

		ull h = gethash() ;
		if (!ap[h]) ++ans ;
		ap[h] = 1 ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}
