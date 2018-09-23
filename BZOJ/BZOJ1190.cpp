#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define READ scanf("%d %d" , &n , &W)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e15 ;
const int MAX_N = 100 + 10 , MAX_L = 1e3 + 10 , MAX_B = 30 + 5 ;

struct data {
	int a , b , val ;
}t[MAX_N] ;

ll f[MAX_B][MAX_L] ;
int n , W , le[MAX_B] , ri[MAX_B] ;

bool cmp(data x , data y) {return x.b < y.b ;}

void div(int x , int wi , int vi) {
	t[x].val = vi ;
	for (int i = 0 ; i <= 30 ; ++i)
		if ((wi >> i) <= 10) {
			t[x].a = wi >> i ; t[x].b = i ;
			break ;
		}
}

int main() {
	for (READ ; n != -1 && W != -1 ; READ) {
		int L = 0 , B = 0 ;

		for (int i = 0 ; i < n ; ++i) {
			int wi , vi ;
			scanf("%d %d" , &wi , &vi) ;

			div(i , wi , vi) ;
			L += t[i].a ; B = std::max(B , t[i].b) ;
		}

		///

		std::sort(t + 0 , t + n , cmp) ;
		for (int i = 0 ; i <= B ; ++i) le[i] = n , ri[i] = -1 ;
		for (int i = 0 ; i < n ; ++i) {
			int b = t[i].b ;
			le[b] = std::min(le[b] , i) ;
			ri[b] = std::max(ri[b] , i) ;
		}

		///

		for (int i = 0 ; i <= B ; ++i) {
			for (int j = 0 ; j <= L ; ++j) f[i][j] = 0 ;

			for (int idx = le[i] ; idx <= ri[i] ; ++idx) {
				data *p = &t[idx] ;
				for (int j = L ; j >= p->a ; --j) f[i][j] = std::max(f[i][j] , f[i][j - p->a] + p->val) ;
			}

			if (!i) continue ;

			int e = W & (1 << (i - 1)) ? 1 : 0 ;
			for (int j = L ; j >= 0 ; --j)
				for (int k = 0 ; k <= j ; ++k)
					f[i][j] = std::max(f[i][j] , f[i][j - k] + f[i - 1][std::min((k << 1) + e , L)]) ;
		}

		W = std::min(W >> B , L) ;
		printf("%lld\n" , f[B][W]) ;
	}

	return 0 ;
}