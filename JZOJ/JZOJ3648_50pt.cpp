#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e6 + 10 , MAX_T = 4e6 + 10 ;

struct data {int p , ml ;}st[MAX_N] ;

char s1[MAX_N] , s2[MAX_N] , s[MAX_T] ;
int tre[MAX_N << 2] , a[MAX_T] , b[MAX_T] ;
int n , tot , sa[MAX_T] , cnt[MAX_T] , sec[MAX_T] , r1[MAX_T] , rk[MAX_T] , h[MAX_T] ;

bool cmp(data x , data y) {return x.ml < y.ml ;}

bool ck(int x , int y , int l) {
	return rk[x] == rk[y] && rk[x + l] == rk[y + l] ;
}

void getsa(int m) {
	for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
	for (int i = 0 ; i < tot ; ++i) ++cnt[rk[i] = s[i]] ;
	for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = tot - 1 ; i >= 0 ; --i) sa[cnt[s[i]]--] = i ;

	int p = 0 ;
	for (int k = 1 ; p < tot ; k <<= 1 , m = p) {
		int o = 0 ;
		for (int i = tot - k ; i < tot ; ++i) sec[++o] = i ;
		for (int i = 1 ; i <= tot ; ++i) if (sa[i] >= k) sec[++o] = sa[i] - k ;

		for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
		for (int i = 1 ; i <= tot ; ++i) ++cnt[rk[sec[i]]] ;
		for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
		for (int i = tot ; i ; --i) sa[cnt[rk[sec[i]]]--] = sec[i] ;

		r1[sa[1]] = p = 1 ;
		for (int i = 2 ; i <= tot ; ++i)
			if (ck(sa[i] , sa[i - 1] , k)) r1[sa[i]] = p ;
			else r1[sa[i]] = ++p ;
		for (int i = 0 ; i < tot ; ++i) rk[i] = r1[i] ;
	}
}

void geth() {
	int k = 0 ;
	for (int i = 0 ; i < tot ; ++i) {
		if (rk[i] == 1) {k = 0 ; continue ;}
		if (k) --k ;

		int j = sa[rk[i] - 1] ;
		for (; j + k < tot && i + k < tot && s[i + k] == s[j + k] ; ++k) ;
		h[rk[i]] = k ;
	}
}

void getlcp(int *f , int p) {
	p = rk[p] ;

	int t = h[p] ;
	for (int i = p - 1 ; i ; --i) {f[sa[i]] = t ; t = std::min(t , h[i]) ;}

	t = h[p + 1] ;
	for (int i = p + 1 ; i <= tot ; ++i) {t = std::min(t , h[i]) ; f[sa[i]] = t ;}
}

void build(int t , int x , int y) {
	tre[t] = -1 ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	build(t << 1 , x , mid) ; build(t << 1 | 1 , mid + 1 , y) ;
}

void modify(int t , int x , int y , int p , int a) {
	tre[t] = a ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	if (p <= mid) modify(t << 1 , x , mid , p , a) ;
	else modify(t << 1 | 1 , mid + 1 , y , p , a) ;
}

int find(int t , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return -1 ;
	if (fx <= x && y <= fy) return tre[t] ;

	int mid = (x + y) >> 1 ,
		s1 = find(t << 1 , x , mid , fx , fy) ,
		s2 = find(t << 1 | 1 , mid + 1 , y , fx , fy) ;

	return std::max(s1 , s2) ;
}

int main() {
	scanf("%d %s %s" , &n , s1 , s2) ;
	for (int i = 0 ; i < n ; ++i) s[tot++] = s1[i] ;
	s[tot++] = '#' ;
	for (int i = 0 ; i < n ; ++i) s[tot++] = s2[i] ;

	///

	getsa('z') ;
	geth() ; getlcp(a , 0) ; getlcp(b , n + 1) ;

	///

	int ans = 0 , p = 0 ;
	for (int i = 0 ; i < n ; ++i) st[p++] = (data){i , a[n + 1 + i]} ;
	std::sort(st + 0 , st + n , cmp) ;

	build(1 , 0 , n) ; p = 0 ;
	for (int k = 0 ; k < n ; ++k) {
		int i = st[k].p , ml = st[k].ml , j ;

		for (; p < ml ;) ++p , modify(1 , 0 , n , b[p] , p) ;
		j = find(1 , 0 , n , i , n) ;

		if (j > -1) ans = std::max(ans , i + j) ;
	}

	printf("%d\n" , ans) ;

	return 0 ;
}