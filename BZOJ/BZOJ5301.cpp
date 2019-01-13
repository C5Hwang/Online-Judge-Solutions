#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct data {
	int x , y , bk , idx ;
}qry[MAX_N] ;

ll res , ans[MAX_N] ;
int n , m , k , siz , a[MAX_N] , s[MAX_N] , cnt[MAX_N << 1] ;

bool cmp(data a , data b) {return a.bk < b.bk || (a.bk == b.bk && a.y < b.y) ;}

int main() {
	scanf("%d %d %d" , &n , &m , &k) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;
	s[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i) s[i] = s[i - 1] ^ a[i] ;

	siz = (int)sqrt(n) ;
	for (int i = 0 ; i < m ; ++i) {
		data *p = &qry[i] ;
		scanf("%d %d" , &p->x , &p->y) ;
		--p->x ; p->idx = i ; p->bk = p->x / siz ;
	}

	///

	std::sort(qry + 0 , qry + m , cmp) ;

	res = 0 ; int L = 0 , R = -1 ;
	for (int i = 0 ; i < m ; ++i) {
		data *p = &qry[i] ;

		for (; R < p->y ;) {++cnt[s[++R]] ; res += cnt[k ^ s[R]] ;}
		for (; p->x < L ;) {++cnt[s[--L]] ; res += cnt[k ^ s[L]] ;}
		for (; p->y < R ;) {res -= cnt[k ^ s[R]] ; --cnt[s[R--]] ;}
		for (; L < p->x ;) {res -= cnt[k ^ s[L]] ; --cnt[s[L++]] ;}

		if (!k) ans[p->idx] = res - (R - L + 1) ;
		else ans[p->idx] = res ;
	}

	for (int i = 0 ; i < m ; ++i) printf("%lld\n" , ans[i]) ;

	return 0 ;
}