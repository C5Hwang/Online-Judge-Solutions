#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e4 + 10 ;

int n , m ;
ll w[MAX_N] , s[2] ;

bool cmp(int x , int y) {return x > y ;}

int main() {
	scanf("%d %d", &n , &m) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%lld" , &w[i]) , w[i] <<= 1 ;
	for (int i = 0 ; i < m ; ++i) {
		int x , y , v ; scanf("%d %d %d" , &x , &y , &v) ;
		w[x] += v ; w[y] += v ;
	}

	///

	std::sort(w + 1 , w + 1 + n , cmp) ;

	for (int i = 1 ; i <= n ; ++i)
		if (i & 1) s[0] += w[i] ;
		else s[1] += w[i] ;

	printf("%lld\n" , (s[0] - s[1]) >> 1) ;

	return 0 ;
}