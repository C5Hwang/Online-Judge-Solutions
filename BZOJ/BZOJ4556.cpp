#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , lgN = 20 + 5 ;

struct Node {
	int num ;
	Node *ch[2] ;
}tre[MAX_N * lgN] ;

char s[MAX_N] ;
Node *root[MAX_N] ;
int tot , mk[MAX_N] , f[MAX_N][lgN] ;
int n , m , sa[MAX_N] , rk[MAX_N] , r1[MAX_N] , cnt[MAX_N] , sec[MAX_N] , h[MAX_N] ;

///

bool cmp(int x , int y , int l) {
	return rk[x] == rk[y] && rk[x + l] == rk[y + l] ;
}

void getsa(int m) {
	for (int i = 0 ; i <= m ; ++i) cnt[i] = 0 ;
	for (int i = 1 ; i <= n ; ++i) ++cnt[rk[i] = s[i]] ;
	for (int i = 1 ; i <= m ; ++i) cnt[i] += cnt[i - 1] ;
	for (int i = n ; i ; --i) sa[cnt[s[i]]--] = i ;

	int p = 0 ;
	for (int k = 1 ; p < n ; m = p , k <<= 1) {
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
		if (rk[i] == 1) {k = h[1] = 0 ; continue ;}

		if (k) --k ;
		int j = sa[rk[i] - 1] ;
		for (; j + k <= n && i + k <= n && s[i + k] == s[j + k] ; ++k) ;

		h[rk[i]] = k ;
	}
}

///

void modify(Node *ort , Node *&rt , int x , int y , int f) {
	rt = &tre[tot++] ;
	*rt = *ort ; ++rt->num ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	if (f <= mid) modify(ort->ch[0] , rt->ch[0] , x , mid , f) ;
	else modify(ort->ch[1] , rt->ch[1] , mid + 1 , y , f) ;	
}

int find(Node *r1 , Node *r2 , int x , int y , int fx , int fy , int ty) {
	if (y < fx || fy < x) return 0 ;
	if (!(r1->num - r2->num)) return 0 ;
	if (x == y) return x ;

	int mid = (x + y) >> 1 , res ;
	if (ty) {
		res = find(r1->ch[1] , r2->ch[1] , mid + 1 , y , fx , fy , ty) ;
		if (!res) res = find(r1->ch[0] , r2->ch[0] , x , mid , fx , fy , ty) ;
	}
	else {
		res = find(r1->ch[0] , r2->ch[0] , x , mid , fx , fy , ty) ;
		if (!res) res = find(r1->ch[1] , r2->ch[1] , mid + 1 , y , fx , fy , ty) ;
	}

	return res ;
}

int count(int x , int y) {
	if (!x) return 0 ;
	if (x == y) return n ;
	else if (x > y) std::swap(x , y) ;

	++x ; int k = mk[y - x + 1] ;
	return std::min(f[x][k] , f[y - (1 << k) + 1][k]) ;
}

bool check(int a , int b , int c , int l) {
	b = b - l + 1 ;

	Node *L = root[a - 1] , *R = root[b] ;
	int p1 = find(R , L , 1 , n , 1 , c , 1) , p2 = find(R , L , 1 , n , c , n , 0) ,
		l1 = count(p1 , c) , l2 = count(p2 , c) ;

	return std::max(l1 , l2) >= l ;
}

///

int main() {
	scanf("%d %d %s" , &n , &m , s) ;
	for (int i = n ; i ; --i) s[i] = s[i - 1] ;

	///

	getsa('z') ; geth() ;

	for (int i = 1 ; i <= n ; ++i) f[i][0] = h[i] ;
	for (int j = 1 ; (1 << j) <= n ; ++j)
		for (int i = 1 ; i <= n ; ++i) {
			int p = i + (1 << (j - 1)) ;
			if (p > n) f[i][j] = f[i][j - 1] ;
			else f[i][j] = std::min(f[i][j - 1] , f[p][j - 1]) ;
		}

	mk[0] = mk[1] = 0 ;
	for (int i = 2 ; i <= n ; ++i) mk[i] = mk[i >> 1] + 1 ;

	root[0] = &tre[tot++] ;
	root[0]->ch[0] = root[0]->ch[1] = root[0] ;
	for (int i = 1 ; i <= n ; ++i) modify(root[i - 1] , root[i] , 1 , n , rk[i]) ;

	///

	for (; m-- ;) {
		int a , b , c , d , L , R ;
		scanf("%d %d %d %d" , &a , &b , &c , &d) ;

		L = 0 ; R = std::min(d - c + 1 , b - a + 1) + 1 ;
		for (; L + 1 < R ;) {
			int mid = (L + R) >> 1 ;
			if (check(a , b , rk[c] , mid)) L = mid ;
			else R = mid ;
		}

		printf("%d\n" , L) ;
	}

	return 0 ;
}