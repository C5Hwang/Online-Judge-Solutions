#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

std::map<int , int> ti ;

const int MAX_B = (1 << 16) + 10 ;

int A , B , P , g , bk , inv[MAX_B] ;

int qpow(int a , int t) {
	if (!t) return 1 ;

	int s = qpow(a , t >> 1) ;
	s = (ll)s * s % P ; if (t & 1) s = (ll)s * a % P ;

	return s ;
}

int getans(int x) {
	for (int i = 0 ; i <= bk ; ++i) {
		int nx = (ll)x * inv[i] % P ;

		if (ti.count(nx)) return ti[nx] + i * bk ;
	}
}

int main() {
	scanf("%d %d" , &g , &P) ;
	bk = (int)sqrt(P) ; bk = std::max(bk , P / bk) ;

	int ny = qpow(g , P - 1 - bk) ; inv[0] = 1 ;
	for (int i = 1 ; i <= bk ; ++i) inv[i] = (ll)inv[i - 1] * ny % P ;
	for (int i = 0 , t = 1 ; i <= bk ; ++i , t = (ll)t * g % P) ti[t] = i ;

	///

	int Q ; scanf("%d" , &Q) ;
	for (; Q-- ;) {
		scanf("%d %d" , &A , &B) ;

		int t1 = getans(A) , t2 = getans(B) , ans = qpow(g , (ll)t1 * t2 % (P - 1)) ;

		printf("%d\n" , ans) ;
	}

	return 0 ;
}