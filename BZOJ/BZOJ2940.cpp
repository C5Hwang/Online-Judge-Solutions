#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e3 + 10 ;

bool ap[3 * MAX_N] ;
int r , g , b , q , n , que[MAX_N] , sg[MAX_N] ;

void init() {
	for (int i = 0 ; i <= 3 * n ; ++i) ap[i] = 0 ;
}

void add(int k) {
	for (int x = 0 ; x <= k ; ++x) {
		int tmp = sg[x] ^ sg[k - x] ;
		ap[tmp] = 1 ;
	}
}

int main() {
	scanf("%d %d %d %d" , &r , &g , &b , &q) ;
	for (int i = 0 ; i < q ; ++i) {
		scanf("%d" , &que[i]) ;
		n = std::max(n , que[i]) ;
	}

	///

	sg[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		init() ;
		add(i - r) ; add(i - g) ; add(i - b) ;

		for (int j = 0 ; j <= 3 * n ; ++j)
			if (!ap[j]) {sg[i] = j ; break ;}
	}

	for (int i = 0 ; i < q ; ++i)
		if (sg[que[i]]) printf("1\n") ;
		else printf("2\n") ;

	return 0 ;
}