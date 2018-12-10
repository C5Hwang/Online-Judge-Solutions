#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e4 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;

Link *head[MAX_N] ;
int n , cur , ans , f[MAX_N][3] , tmp[3] ;

int gcd(int x , int y) {return y ? gcd(y , x % y) : x ;}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dp(int x , int fa) {
	f[x][0] = 1 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dp(nx , x) ;

		for (int i = 0 ; i < 3 ; ++i) {
			tmp[i] = f[nx][(i + 3 - h->val) % 3] ;
			ans += tmp[i] * f[x][(3 - i) % 3] ;
		}
		for (int i = 0 ; i < 3 ; ++i) f[x][i] += tmp[i] ;
	}
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i < n ; ++i) {
		int a , b , v ;
		scanf("%d %d %d" , &a , &b , &v) ; v %= 3 ;
		ins(a , b , v) ; ins(b , a , v) ;
	}

	///

	dp(1 , 1) ;

	(ans <<= 1) += n ;
	int tot = n * n , d = gcd(ans , tot) ;
	printf("%d/%d\n" , ans / d , tot / d) ;

	return 0 ;
}