#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const ll INF = 1e15 ;
const int lim = 2e6 , MAX_N = 2e6 + 10 ;

struct data {
	ll a , b ;

	friend data operator *(data x , ll y) {
		return (data){x.a * y , x.b * y} ;
	} ;
	friend data operator -(data x , data y) {
		return (data){x.a - y.a , x.b - y.b} ;
	}
} ;

data sum[MAX_N] , ans[MAX_N] ;
int T , n , tot , pri[MAX_N] , phi[MAX_N] , mu[MAX_N] ;

void init() {
	n = lim ;

	mu[1] = 1 ; phi[1] = 1 ;
	for (int i = 2 ; i <= n ; ++i) {
		if (!phi[i]) {mu[i] = -1 ; phi[i] = i - 1 ; pri[tot++] = i ;}

		for (int j = 0 ; j < tot ; ++j) {
			int tmp = i * pri[j] ;
			if (tmp > n) break ;

			if (i % pri[j]) {mu[tmp] = -mu[i] ; phi[tmp] = phi[i] * (pri[j] - 1) ;}
			else {mu[tmp] = 0 ; phi[tmp] = phi[i] * pri[j] ; break ;}
		}
	}

	for (int i = 1 ; i <= n ; ++i)
		sum[i].a = sum[i - 1].a + phi[i] , sum[i].b = sum[i - 1].b + mu[i] ;
}

data getans(int m) {
	if (m <= lim) return sum[m] ;
	if (ans[n / m].a != -INF) return ans[n / m] ;

	data res = (data){(m * ((ll)m + 1)) >> 1 , 1} ;
	for (ll L = 2 ; L <= m ;) {
		int t = m / L , R = m / t ;

		res = res - getans(t) * (R - L + 1) ; L = R + 1LL ;
	}

	return (ans[n / m] = res) ;
}

int main() {
	init() ;
	scanf("%d" , &T) ;
	for (; T-- ;) {
		scanf("%d" , &n) ;
		for (int i = 0 ; i <= n / lim ; ++i) ans[i].a = ans[i].b = -INF ;

		data res = getans(n) ;
		printf("%lld %lld\n" , res.a , res.b) ;
	}

	return 0 ;
}