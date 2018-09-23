#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 200 + 10 ;

int T , A ;
bool ap[MAX_N] ;

int main() {
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d" , &A) ;
		A = A / 9 + 1 ;

		bool ok = 0 ;

		for (int i = 0 ; !ok && i < A ; ++i) {
			int x = 3 * i + 2 , y = 2 , cnt = 9 ;
			for (int j = 0 ; j < 9 ; ++j) ap[j] = 0 ;

			for (; cnt ;) {
				int nx , ny , idx ;
				
				printf("%d %d\n" , x , y) ;
				fflush(stdout) ;
				scanf("%d %d" , &nx , &ny) ;
				
				if (nx < 1 && ny < 1) {ok = 1 ; break ;}

				nx += 1 - x ; ny += 1 - y ; idx = nx * 3 + ny ;
				if (!ap[idx]) --cnt ; ap[idx] = 1 ;
			}
		}
	}

	return 0 ;
}