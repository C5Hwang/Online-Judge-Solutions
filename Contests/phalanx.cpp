#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 3e5 + 10 , MAX_NODE = 6e6 + 10 ;

struct Node {
	ll num ; int sum ;
	Node *left , *right ;
}tree[(MAX_NODE << 1) + (MAX_N << 3)] ;

Node *root[MAX_N] , *empty ;
int n , m , q , cur , siz[MAX_N] ;

void init(Node *rt) {
	rt->num = -1 ; rt->sum = 0 ;
	rt->left = rt->right = empty ;
}

void del(Node *&rt , int x , int y , int k) {
	if (rt == empty) {rt = &tree[cur++] ; init(rt) ;}
	--rt->sum ;

	if (x == y) return ;

	int mid = (x + y) >> 1 , r = mid - x + 1 + rt->left->sum ;

	if (k <= r) del(rt->left , x , mid , k) ;
	else del(rt->right , mid + 1 , y , k - r) ;
}

void add(Node *&rt , int x , int y , int f , ll a) {
	if (y < f || f < x) return ;

	if (rt == empty) {rt = &tree[cur++] ; init(rt) ;}

	if (x == y) {
		rt->num = a ;
		return ;
	}

	int mid = (x + y) >> 1 ;
	add(rt->left , x , mid , f , a) ;
	add(rt->right , mid + 1 , y , f , a) ;
}

ll getkth(Node *rt , int x , int y , int k , int line) {
	if (x == y) {
		if (rt->num < 0) {
			if (line >= 0) return (ll)(line - 1) * m + y ;
			else return (ll)x * m ;
		}
		else return rt->num ;
	}

	int mid = (x + y) >> 1 , r = mid - x + 1 + rt->left->sum ;

	if (k <= r) return getkth(rt->left , x , mid , k , line) ;
	else return getkth(rt->right , mid + 1 , y , k - r , line) ;
}

int read() {
	char c = getchar() ;
	int f = 1 , num = 0 ;

	while (c < '0' || c > '9') {if (c == '-') f = -f ; c = getchar() ;}
	while (c >= '0' && c <= '9') {num = num * 10 + c - '0' ; c = getchar() ;}

	return num * f ;
}

int main() {
	freopen("phalanx.in" , "r" , stdin) ;
	freopen("phalanx.out" , "w" , stdout) ;

	n = read() ; m = read() ; q = read() ;

	empty = &tree[cur++] ; init(empty) ;
	for (int i = 0 ; i <= n ; ++i) {
		if (i) siz[i] = m - 1 ;
		else siz[i] = n ;
		root[i] = empty ;
	}

	///

	for (int i = 0 ; i < q ; ++i) {
		int x , y ; x = read() ; y = read() ;

		ll num = getkth(root[0] , 1 , n + q , x , -1) , ans ;
		if (y < m) {
			ans = getkth(root[x] , 1 , m + q , y , x) ;
			del(root[x] , 1 , m + q , y) ;
			add(root[x] , 1 , m + q , ++siz[x] , num) ;
		}
		else ans = num ;

		del(root[0] , 1 , n + q , x) ;
		add(root[0] , 1 , n + q , ++siz[0] , ans) ;

		printf("%lld\n" , ans) ;
	}

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}