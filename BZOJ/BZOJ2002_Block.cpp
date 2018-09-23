#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 2e5 + 10 ;

struct data {
	int bk , len , pl ;
}cw[MAX_N] ;

int n , m , block , cnt , a[MAX_N] ;

void update(int x) {
	data *pt = &cw[x] ;
	int L = (pt->bk - 1) * block + 1 , R = std::min(pt->bk * block , n) , p = x ;

	for (int i = R ; i >= L ; --i) {
		int np = i + a[i] ;
		if (np > R) cw[i].len = 1 , cw[i].pl = np ;
		else cw[i].len = cw[np].len + 1 , cw[i].pl = cw[np].pl ;
	}
}

int main() {
	scanf("%d" , &n) ;
	block = (int)sqrt(n) ;
	if (n % block) cnt = n / block + 1 ;
	else cnt = n / block ;

	///

	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	for (int i = 1 ; i <= cnt ; ++i) {
		int L = (i - 1) * block + 1 , R = std::min(i * block , n) ;
		for (int j = L ; j <= R ; ++j) cw[j].bk = i ;
	}

	for (int i = 1 ; i <= n ; ++i) update(i) ;

	///

	scanf("%d" , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int op , x , y ;
		scanf("%d %d" , &op , &x) ; ++x ;
		if (op == 2) scanf("%d" , &y) ;

		if (op == 1) {
			int p = x , ans = 0 ;
			for (; p <= n ; ans += cw[p].len , p = cw[p].pl) ;
			printf("%d\n" , ans) ;
		}
		else {
			a[x] = y ;
			update(x) ;
		}
	}

	return 0 ;
}
