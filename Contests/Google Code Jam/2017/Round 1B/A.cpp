#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1000 + 10 ;

struct data {
	int v , s ;
}a[MAX_N] ;

double t[MAX_N] ;
int n , k ;

bool cmp(data x , data y) {return x.s < y.s ;}

int main() {
	freopen("input.in" , "r" , stdin) ;
	freopen("output" , "w" , stdout) ;

	int num = 1 ;
	int T ; scanf("%d" , &T) ;
	for (; T-- ; ++num) {
		double mt = 0 ;

		scanf("%d %d" , &k , &n) ;
		for (int i = 1 ; i <= n ; ++i) scanf("%d %d" , &a[i].s , &a[i].v) ;

		///
		
		std::sort(a + 1 , a + 1 + n , cmp) ;

		///

		mt = (k - a[n].s) * 1.0 / a[n].v ;
		for (int i = n - 1 ; i > 0 ; --i) {
			int nv = a[i].v ;
			double meet = (a[i + 1].s - a[i].s) * 1.0 / (a[i].v - a[i + 1].v) ,
				   arr = (k - a[i].s) * 1.0 / a[i].v ;

			if (meet > arr || meet < 0) mt = arr ;
			else {
				int rv = a[i + 1].v ;
				double nt = (k - a[i + 1].s - meet * rv) * 1.0 / rv ;

				mt = meet + nt ;
			}
		}

		printf("Case #%d: %0.6lf\n" , num , k / mt) ;
	}

	return 0 ;
}
