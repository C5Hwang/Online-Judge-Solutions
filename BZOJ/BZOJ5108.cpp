#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long

const int MAX_N = 1e5 + 10 , lgN = 30 + 5 , len = 30 ;

struct data {
	int idx , num ;
}t[MAX_N] ;
struct number {int z , o ;} cnt[lgN] ;

ll ans ;
int n , m , a[MAX_N] ;

bool cmp(data x , data y) {return x.idx < y.idx ;}

void init() {
	for (int i = 0 ; i <= len ; ++i)
		cnt[i].z = cnt[i].o = 0 ;
}

void add(int x) {
	for (int i = 0 ; i <= len ; ++i)
		if (x & (1 << i)) ++cnt[i].o ;
		else ++cnt[i].z ;
}

int main() {
	scanf("%d %d" , &m , &n) ;
	for (int i = 0 ; i < n ; ++i) scanf("%d %d" , &t[i].idx , &t[i].num) ;
	std::sort(t + 0 , t + n , cmp) ;

	///

	int p = 0 , lt = 1 , s = 0 ;
	for (; p < n && t[p].idx == lt ; ++lt , ++p) {s ^= t[p].num ; ans += s ;}

	int last = s ;
	for (; p < n ;) {
		init() ;

		if (!p || t[p].idx - t[p - 1].idx > 2) last = 0 ;

		int ed = p , ax = 0 ;
		for (; ed < n - 1 && t[ed + 1].idx == t[ed].idx + 1 ; ++ed) ;

		int s = last ; add(last) ;
		for (int i = p ; i <= ed ; ++i) {s ^= t[i].num ; add(s) ;}
		for (int i = 0 ; i <= len ; ++i) if (cnt[i].z + 1 <= cnt[i].o) ax += (1 << i) ;

		s = ax^last ; ans += s ;
		for (int i = p ; i <= ed ; ++i) {s ^= t[i].num ; ans += s ;}

		last = s ; p = ed + 1 ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}