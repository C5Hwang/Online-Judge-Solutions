#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define uint unsigned int
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct QUERY {int n , m , a , idx ;}qry[MAX_N] ;

bool vis[MAX_N] ;
uint mu[MAX_N] , ti[MAX_N] , BIT[MAX_N] , ans[MAX_N] ;
int n , Q , tot , idx[MAX_N] , pri[MAX_N] , sig[MAX_N] ;

///

bool cmp1(QUERY x , QUERY y) {return x.a < y.a ;}
bool cmp2(int x , int y) {return sig[x] < sig[y] ;}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

inline uint calc(int p , int t) {
	uint s = 0 , tmp = 1 ;
	for (int i = 0 ; i <= t ; ++i , tmp = tmp * p) s += tmp ;

	return s ;
}

void init() {
	mu[1] = 1 ; sig[1] = 1 ; ti[1] = 0 ;

	for (int i = 2 ; i <= n ; ++i) {
		if (!vis[i]) {
			pri[tot++] = i ;
			mu[i] = -1 ; sig[i] = i + 1 ; ti[i] = 1 ;
		}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;
			vis[tmp] = 1 ;

			if (i % pri[j]) {
				ti[tmp] = 1 ;
				mu[tmp] = -mu[i] ; sig[tmp] = sig[i] * sig[pri[j]] ;
			}
			else {
				ti[tmp] = ti[i] + 1 ; mu[tmp] = 0 ;
				sig[tmp] = sig[i] / calc(pri[j] , ti[i]) * calc(pri[j] , ti[i] + 1) ;

				break ;
			}
		}
	}
}

///

inline int lowbit(int x) {return x & (-x) ;}

void update(int x , uint a) {
	for (; x <= n ; x += lowbit(x)) BIT[x] += a ;
}

uint find(int x) {
	uint sum = 0 ;
	for (; x ; x -= lowbit(x)) sum += BIT[x] ;

	return sum ;
}

void add(int x) {
	for (int i = x ; i <= n ; i += x)
		if (mu[i / x]) update(i , mu[i / x] * sig[x]) ;
}

uint getans(int n , int m) {
	uint last = 0 , res = 0 ;
	for (int L = 1 ; L <= n ;) {
		int t1 = n / L , t2 = m / L , R = std::min(n / t1 , m / t2) ;

		uint tmp = find(R) ;
		res += (unsigned)t1 * (unsigned)t2 * (tmp - last) ;
		last = tmp ; L = R + 1 ;
	}

	return res ;
}

///

int main() {
	Q = read() ;
	for (int i = 0 ; i < Q ; ++i) {
		QUERY *p = &qry[i] ;
		p->n = read() ; p->m = read() ; p->a = read() ; p->idx = i ;
		if (p->n > p->m) std::swap(p->n , p->m) ;

		n = std::max(n , p->m) ;
	}

	///

	init() ;
	std::sort(qry + 0 , qry + Q , cmp1) ;

	for (int i = 1 ; i <= n ; ++i) idx[i] = i ;
	std::sort(idx + 1 , idx + 1 + n , cmp2) ;

	///

	int L = 1 ;
	for (int i = 0 ; i < Q ; ++i) {
		QUERY *p = &qry[i] ;
		for (; L <= n && sig[idx[L]] <= p->a ;) add(idx[L++]) ;

		ans[p->idx] = getans(p->n , p->m) ;
	}

	uint mod = ((unsigned)1 << 31) - 1 ;
	for (int i = 0 ; i < Q ; ++i) printf("%u\n" , ans[i] & mod) ;

	return 0 ;
}