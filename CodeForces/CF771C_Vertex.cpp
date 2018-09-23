#include <stdio.h>
#include <stdlib.h>

const int MAX_N = 2e5 + 10 , MAX_K = 10 ;

struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;

Link *head[MAX_N] ;
long long sf[MAX_N] , sg[MAX_N] , temp[MAX_N] ;
int n , k , cur , f[MAX_N][MAX_K] , g[MAX_N][MAX_K] ;

void getF(int x , int fa) {
	long long tot = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		getF(nx , x) ;
		tot += sf[nx] ;
		f[x][1] += f[nx][0] ;
	}

	for (int i = 1 ; i <= k ; ++i) {
		long long sum = 0 ;
		int j = (i - 2 + k) % k + 1 ;
		for (Link *h = head[x] ; h ; h = h->next) {
			int nx = h->num ;
			if (nx == fa) continue ;

			sum += f[nx][j] ;
		}

		f[x][i] += sum ;
	}

	sf[x] = tot + f[x][1] ;
	++f[x][0] ;
}

void getG(int x , int fa) {
	long long tot = sg[x] + g[x][k] + 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		int i = (k - 1) % k + 1 , j = (k - 2) % k + 1 , ti = k > 1 ? 1 : 2 ;
		temp[nx] = sf[nx] + f[nx][i] + f[nx][j] + f[nx][0] * ti ;
		tot += temp[nx] ;
	}

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		sg[nx] = tot - temp[nx] ;
		for (int i = 1 ; i <= k ; ++i) {
			int p = (i - 2 + k) % k + 1 , q = (i - 3 + k) % k + 1 ;
			g[nx][i] = g[x][p] + f[x][p] - f[nx][q] ;
			if (p == 1) g[nx][i] -= f[nx][0] ;
		}
		g[nx][1] += f[x][0] ;

		getG(nx , x) ;
	}
}

///

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

///

int main() {
	scanf("%d %d" , &n , &k) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}

	///

	getF(1 , 1) ;
	getG(1 , 1) ;

	long long res = 0 ;
	for (int i = 1 ; i <= n ; ++i) res += sf[i] + sg[i] ;
	printf("%I64d\n" , res >> 1) ;

	return 0 ;
}
