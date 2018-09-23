#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_N = 26 + 5 ;

bool ap[MAX_N] ;
int n , len , eg[MAX_N] , cnt[MAX_N] ;

void dfs(int x) {
	if (ap[x]) return ;
	++len ; ap[x] = 1 ;
	dfs(eg[x]) ;
}

int main() {
	int Q ; scanf("%d" , &Q) ;
	for (; Q-- ;) {
		n = 26 ; getchar() ;
		for (int i = 0 ; i < n ; ++i) {
			char ch ; scanf("%c" , &ch) ;
			eg[i] = ch - 'A' ;
		}

		///

		memset(ap , 0 , sizeof(ap)) ;
		memset(cnt , 0 , sizeof(cnt)) ;

		for (int i = 0 ; i < n ; ++i) {
			if (ap[i]) continue ;
			len = 0 ; dfs(i) ;
			++cnt[len] ;
		}

		bool ok = 1 ;
		for (int i = 0 ; i <= n && ok ; i += 2)
			if (cnt[i] & 1) ok = 0 ;

		if (ok) printf("Yes\n") ;
		else printf("No\n") ;
	}

	return 0 ;
}