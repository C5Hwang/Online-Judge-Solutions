#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , MAX_M = 3e6 + 10 , lgN = 20 + 5 ;

struct data {int len , pl ; ll res ;} ;

std::stack<data> sta ;

char s[MAX_N] ;
int n , m , tot , qry[MAX_M] , a[MAX_M] , mk[MAX_N] ;
int sa[MAX_N] , h[MAX_N] , rk[MAX_N] , r1[MAX_N] , cnt[MAX_N] , sec[MAX_N] , f[MAX_N][lgN] ;

bool cmp(int x , int y , int l) {
	return rk[x] == rk[y] && rk[x + l] == rk[y + l] ;
}

void build(int m) {
	for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
	for (int i = 1 ; i <= n ; ++i) ++cnt[rk[i] = s[i]] ;
	for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n ; i ; --i) sa[cnt[rk[i]]--] = i ;

	int p = 0 ;
	for (int k = 1 ; p < n ; k <<= 1 , m = p) {
		int o = 0 ;
		for (int i = n + 1 - k ; i <= n ; ++i) sec[++o] = i ;
		for (int i = 1 ; i <= n ; ++i) if (sa[i] > k) sec[++o] = sa[i] - k ;

		for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
		for (int i = 1 ; i <= n ; ++i) ++cnt[rk[sec[i]]] ;
		for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
		for (int i = n ; i ; --i) sa[cnt[rk[sec[i]]]--] = sec[i] ;

		r1[sa[1]] = p = 1 ;
		for (int i = 2 ; i <= n ; ++i)
			if (cmp(sa[i] , sa[i - 1] , k)) r1[sa[i]] = p ;
			else r1[sa[i]] = ++p ;
		for (int i = 1 ; i <= n ; ++i) rk[i] = r1[i] ;
	}
}

void geth() {
	int k = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		if (rk[i] == 1) {k = 0 ; continue ;}

		if (k) --k ;
		int j = sa[rk[i] - 1] ;
		for (; i + k <= n && j + k <= n && s[i + k] == s[j + k] ; ++k) ;
		h[rk[i]] = k ;
	}
}

int count(int x , int y) {
	++x ;
	int k = mk[y - x + 1] ;

	return std::min(f[x][k] , f[y - (1 << k) + 1][k]) ;
}

ll getans() {
	ll ans = 0 , sum = 0 ;
	for (; !sta.empty() ; sta.pop()) ;
	sta.push((data){-1 , 0 , 0}) ;

	for (int i = 1 ; i < tot ; ++i) {
		int l = count(a[i - 1] , a[i]) ;

		for (; sta.top().len >= l ; sum -= sta.top().res , sta.pop()) ;
		ll tmp = (i - sta.top().pl) * (ll)l ;
		sum += tmp ; ans += sum ; sta.push((data){l , i , tmp}) ;
	}

	return ans ;
}

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

int main() {
	n = read() ; m = read() ; scanf("%s" , s) ;
	for (int i = n ; i ; --i) s[i] = s[i - 1] ;

	///

	build('z') ; geth() ;

	mk[0] = mk[1] = 0 ;
	for (int i = 2 ; i <= n ; ++i) mk[i] = mk[i >> 1] + 1 ;
	for (int i = 1 ; i <= n ; ++i) f[i][0] = h[i] ;
	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i) {
			int p = i + (1 << (j - 1)) ;
			if (p > n) f[i][j] = f[i][j - 1] ;
			else f[i][j] = std::min(f[i][j - 1] , f[p][j - 1]) ;
		}

	///

	for (; m-- ;) {
		int t = read() ;
		for (int i = 0 ; i < t ; ++i)
			qry[i] = read() , qry[i] = rk[qry[i]] ;

		std::sort(qry + 0 , qry + t) ;
		tot = 0 ; a[tot++] = qry[0] ;
		for (int i = 1 ; i < t ; ++i) if (qry[i] != qry[i - 1]) a[tot++] = qry[i] ;

		printf("%lld\n" , getans()) ;
	}

	return 0 ;
}