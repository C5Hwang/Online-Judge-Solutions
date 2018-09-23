#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 500 + 10 ;

struct data {long long num , s ;}queue[MAX_L] ;

int L , R ;
long long n , k ;

int find(int L , int R , data x) {
	for (int i = L ; i <= R ; ++i)
		if (queue[i].num == x.num) return i ;

	return 0 ;
}

int main() {
	freopen("input" , "r" , stdin) ;
	freopen("output" , "w" , stdout) ;

	int T , caseNUM = 1 ; scanf("%d" , &T) ;
	for (; T-- ; ++caseNUM) {
		scanf("%lld %lld" , &n , &k) ;

		L = 1 ; R = 1 ; queue[1].num = n ; queue[1].s = 1 ;

		bool ans = 0 ;
		while (!ans) {
			int nL = R + 1 , nR = R , i ;
			
			for (i = L ; i <= R ; ++i) {
				if (queue[i].s >= k || queue[i].num == 1) {ans = 1 ; break ;}

				data x = queue[i] ;
				long long left = (x.num - 1) >> 1 , mod = (x.num - 1) % 2 ;
				data lson = (data){left + mod, x.s} ,
					 rson = (data){left , x.s} ;

				int ln = find(nL , nR , lson) ;
				if (!ln) queue[++nR] = lson ; else queue[ln].s += lson.s ;

				int rn = find(nL , nR , rson) ;
				if (!rn) queue[++nR] = rson ; else queue[rn].s += rson.s ;

				k -= queue[i].s ;
			}
			L = nL ; R = nR ;

			if (ans) {
				data x = queue[i] ;

				long long mid = (1 + x.num) / 2 , s1 = mid - 1 , s2 = x.num - mid ;

				printf("Case #%d: %lld %lld\n" , caseNUM , std::max(s1 , s2) , std::min(s1 , s2)) ;
			}
		}
	}
	
	return 0 ;
}
