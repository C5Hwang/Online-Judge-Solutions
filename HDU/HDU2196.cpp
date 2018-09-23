#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 10000 + 10 ;

struct Link {
	int num , val ;
	Link *next ;
}list[2 * MAX_N] ;

Link *head[MAX_N] ;
int n , cur , f[MAX_N] ;
int fs[MAX_N] , ss[MAX_N] , fp[MAX_N] , sp[MAX_N] ;

void build(int x , int fa) {
	int fir , sec , firp , secp , d = 0 ;
	fir = sec = firp = secp = 0 ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		build(nx , x) ;
		int temp = fs[nx] + h->val ;
		if (temp > fir) {
			std::swap(fir , sec) ; std::swap(firp , secp) ;
			fir = temp ; firp = nx ;
		}
		else if (temp > sec) sec = temp , secp = nx ;
	}

	fs[x] = fir ; ss[x] = sec ;
	fp[x] = firp ; sp[x] = secp ;
}

void getans(int x , int fa , int olf) {
	f[x] = std::max(olf , fs[x]) ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;
		if (nx == fp[x]) {getans(fp[x] , x , std::max(olf , ss[x]) + h->val) ; continue ;}

		getans(nx , x , std::max(olf , fs[x]) + h->val) ;
	}
}

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;

	head[x] = &list[cur++] ;
}

void init() {
	cur = 0 ;
	memset(head , 0 , sizeof(head)) ;
}

int main() {
	while (scanf("%d" , &n) != EOF)	{
		init() ;

		for (int i = 2 ; i <= n ; ++i) {
			int j , v ;
			scanf("%d %d" , &j , &v) ;
			ins(i , j , v) ; ins(j , i , v) ;
		}

		///

		build(1 , -1) ;
		getans(1 , -1 , 0) ;

		///

		for (int i = 1 ; i <= n ; ++i)
			printf("%d\n" , f[i]) ;
	}

	return 0 ;
}
