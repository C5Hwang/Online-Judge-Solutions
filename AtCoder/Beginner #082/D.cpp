#include <bitset>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 8e3 + 10 , offset = 8e3 ;

std::bitset<MAX_N << 1> f[MAX_N] ;

char op[MAX_N] ;
int len , init[2] , cnt[2] , to[2] , num[2][MAX_N] ;

bool work(int ty) {
	for (int i = 0 ; i <= cnt[ty] ; ++i) f[i].reset() ;

	f[0][init[ty] + offset] = 1 ;
	for (int i = 1 ; i <= cnt[ty] ; ++i)
		f[i] = (f[i - 1] >> num[ty][i]) | (f[i - 1] << num[ty][i]) ;

	return f[cnt[ty]][to[ty] + offset] == 1 ;
}

int main() {
	scanf("%s" , op) ;
	len = strlen(op) ;
	scanf("%d %d" , &to[0] , &to[1]) ;

	///

	cnt[0] = cnt[1] = 0 ;
	init[0] = init[1] = 0 ;
	int i = 0 ;
	for (; i < len && op[i] != 'T' ; ++i , ++init[0]) ;

	int ty = 1 ;
	for (++i ; i < len ; ty ^= 1) {
		int p = i ;
		for (; p < len && op[p] != 'T' ; ++p) ;

		if (p > i) num[ty][++cnt[ty]] = p - i ;
		i = p + 1 ;
	}

	bool ans = work(0) & work(1) ;
	if (ans) printf("Yes\n") ;
	else printf("No\n") ;

	return 0 ;
}