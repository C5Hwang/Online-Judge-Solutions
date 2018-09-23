#include <set>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 ;

struct data {
	int t , num ;

	friend bool operator <(data a , data b) {return a.t < b.t ;}
} ;

std::set<int> s1 ;
std::set<data> s2[MAX_N] ;

bool ap[MAX_N] ;
int n , s , q , p , m , d ;
int tot , c[MAX_N] , cir[MAX_N] , stp[MAX_N] , pos[MAX_N] , left[MAX_N] ;

int finds1(int x) {
	std::set<int> :: iterator p = s1.lower_bound(x) ;
	if (p == s1.end()) p = s1.begin() ;

	return *p ;
}

int finds2(int sp , int x) {
	std::set<data> :: iterator p = s2[sp].lower_bound((data){stp[x] , 0}) ;
	if (p == s2[sp].end()) p = s2[sp].begin() ;

	return p->num ;
}

void init() {
	c[0] = 0 ; tot = 0 ;
	for (int i = 1 ; i < n ; ++i) c[i] = ((ll)c[i - 1] * q + p) % m ;

	for (int i = 0 ; i < n ; ++i) cir[i] = 0 ;
	for (int i = 0 ; i < n ; ++i) {
		if (cir[i]) continue ;

		++tot ;
		for (int p = i , x = 0 ; !cir[p] ; (p += d) %= n , ++x) {
			cir[p] = tot ; stp[p] = x ; ++left[tot] ;
		}
	}

	for (int i = 1 ; i <= tot ; ++i) s1.insert(i) ;
	for (int i = 0 ; i < n ; ++i) if (i != s) s2[cir[i]].insert((data){stp[i] , i}) ;
	--left[cir[s]] ; if (!left[cir[s]]) s1.erase(cir[s]) ;

	pos[0] = s ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , ay , tmp = c[i] % n ;
		y = finds1(cir[tmp]) ; ay = (y - cir[tmp] + tot) % tot ;
		tmp = (tmp + ay) % n ; x = finds2(y , tmp) ;

		pos[i] = x ; s2[y].erase((data){stp[x] , x}) ;

		--left[y] ;
		if (!left[y]) s1.erase(y) ;
	}
}

int main() {
	int Q ; scanf("%d" , &Q) ;
	for (; Q-- ;) {
		scanf("%d %d %d %d %d %d" , &n , &s , &q , &p , &m , &d) ;
		if (!d) d = 1 ;

		///

		init() ;

		///
		
		int ans = 0 ;
		for (int i = 0 ; i < n ; ++i) ap[i] = 0 ;
		for (int i = 0 ; i < n ; ++i) {
			if (ap[i]) continue ;

			int len = 0 ;
			for (int p = i ; !ap[p] ; p = pos[p]) ++len , ap[p] = 1 ;

			if (len == 1) continue ;

			if (!i) ans += (len - 1) ;
			else ans += (len + 1) ;
		}

		printf("%d\n" , ans) ;
	}

	return 0 ;
}