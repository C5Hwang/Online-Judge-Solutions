#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , mod = 536870912 ;

inline int red(int a , int b) {return a - b < 0 ? a - b + mod : a - b ;}
inline int ti(int a , int b) {return (ll)a * b - (ll)a * b / mod * mod ;}
inline int add(int a , int b) {return a + b >= mod ? a + b - mod : a + b ;}

struct data {int x , y ;}pt[MAX_N] ;
struct Node {
	Node *ch[2] ;
	int num , sum , lzy1 , lzy2 ;
	int p[2] , mi[2] , ma[2] , siz ;

	void init() {ch[0] = ch[1] = NULL ; sum = num = lzy2 = 0 ; siz = lzy1 = 1 ;}
	void build_update() {
		mi[0] = ma[0] = p[0] ; mi[1] = ma[1] = p[1] ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) for (int j = 0 ; j < 2 ; ++j)
				mi[j] = std::min(mi[j] , ch[i]->mi[j]) , ma[j] = std::max(ma[j] , ch[i]->ma[j]) ;
	}
	void change(int a1 , int a2) {
		lzy1 = (ll)lzy1 * a1 % mod ; lzy2 = ((ll)lzy2 * a1 + a2) % mod ;
		num = ((ll)num * a1 + a2) % mod ; sum = ((ll)sum * a1 + (ll)a2 * siz) % mod ;
	}
	void update() {
		sum = num ; siz = 1 ;
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) sum = add(sum , ch[i]->sum) , siz += ch[i]->siz ;
	}
	void down() {
		for (int i = 0 ; i < 2 ; ++i)
			if (ch[i]) ch[i]->change(lzy1 , lzy2) ;
		lzy1 = 1 ; lzy2 = 0 ;
	}
}tre[MAX_N] ;

Node *root ;
int n , m , cur , A , B , E ;

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

bool cmp(data a , data b) {
	if (E) return a.y < b.y ;
	else return a.x < b.x ;
}

void build(Node *&rt , int x , int y , int ty) {
	if (x > y) return ;

	(rt = &tre[cur++])->init() ;
	int mid = (x + y) >> 1 ; E = ty ;
	std::nth_element(pt + x , pt + mid , pt + y + 1 , cmp) ;

	rt->mi[0] = rt->ma[0] = rt->p[0] = pt[mid].x ;
	rt->mi[1] = rt->ma[1] = rt->p[1] = pt[mid].y ;
	if (x == y) return ;

	build(rt->ch[0] , x , mid - 1 , ty^1) ; build(rt->ch[1] , mid + 1 , y , ty^1) ;
	rt->build_update() ; rt->update() ;
}

void modify(Node *rt , int a1 , int a2) {
	if (!rt || B < rt->mi[E] || rt->ma[E] < A) return ;
	if (A <= rt->mi[E] && rt->ma[E] <= B) {
		rt->change(a1 , a2) ;
		return ;
	}

	rt->down() ;
	if (A <= rt->p[E] && rt->p[E] <= B) {
		rt->sum = red(rt->sum , rt->num) ;
		rt->num = ((ll)rt->num * a1 + a2) % mod ;
		rt->sum = add(rt->sum , rt->num) ;
	}

	modify(rt->ch[0] , a1 , a2) ; modify(rt->ch[1] , a1 , a2) ;
	rt->update() ;
}

int find(Node *rt) {
	if (!rt || B < rt->mi[E] || rt->ma[E] < A) return 0 ;
	if (A <= rt->mi[E] && rt->ma[E] <= B) return rt->sum ;

	rt->down() ;
	int val = 0 , s1 = find(rt->ch[0]) , s2 = find(rt->ch[1]) ;
	if (A <= rt->p[E] && rt->p[E] <= B) val = rt->num ;

	return (s1 + s2 + val) % mod ;
}

int main() {
	freopen("4303.in" , "r" , stdin) ;
	freopen("4303.out" , "w" , stdout) ;

	n = read() ; m = read() ;
	for (int i = 1 ; i <= n ; ++i) {int a = read() ; pt[i].x = i ; pt[i].y = a ;}

	///

	build(root , 1 , n , 0) ;
	for (; m-- ;) {
		int op , a1 , a2 ;
		op = read() ; A = read() ; B = read() ; E = op & 1 ;
		if (op < 2) {a1 = read() ; a2 = read() ;}

		if (op < 2) modify(root , a1 , a2) ;
		else printf("%d\n" , find(root)) ;
	}

	return 0 ;
}