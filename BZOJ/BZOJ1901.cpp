#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 10000 + 10 , MAX_M = 10000 + 10 , lgN = 20 ;

struct Node {
	int s ; bool empty ;
	Node *ch[2] ;
}tre[(MAX_N + MAX_M) * lgN * lgN] , NULLNODE ;
struct Question {
	int q , x , y , k ;
}que[MAX_M] ;

Node *root[MAX_N] , *A[lgN] , *B[lgN] ;
int n , m , cur , lcur , sA , sB , t[MAX_N] , list[MAX_N + MAX_M] ;

void maintain(Node *rt) {rt->s = 0 ; rt->empty = 0 ; rt->ch[0] = rt->ch[1] = &NULLNODE ;}

void ins(Node *&rt , int x , int y , int f , int a) {
	if (f < x || y < f) return ;
	if (rt->empty) rt = &tre[++cur] , maintain(rt) ;

	rt->s += a ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;

	ins(rt->ch[0] , x , mid , f , a) ;
	ins(rt->ch[1] , mid + 1 , y , f , a) ;
}

int query(int x , int y , int k) {
	if (x == y) return list[x] ;

	int sum = 0 , mid = (x + y) >> 1 ;
	for (int i = 0 ; i < sB ; ++i) sum += B[i]->ch[0]->s ;
	for (int i = 0 ; i < sA ; ++i) sum -= A[i]->ch[0]->s ;
	
	if (sum < k) {
		for (int i = 0 ; i < sB ; ++i) B[i] = B[i]->ch[1] ;
		for (int i = 0 ; i < sA ; ++i) A[i] = A[i]->ch[1] ;

		return query(mid + 1 , y , k - sum) ;
	}
	else {
		for (int i = 0 ; i < sB ; ++i) B[i] = B[i]->ch[0] ;
		for (int i = 0 ; i < sA ; ++i) A[i] = A[i]->ch[0] ;

		return query(x , mid , k) ;
	}
}

///

int lowbit(int t) {return t & (-t) ;}

void update(int t , int x , int y) {
	for (; t <= n ; t += lowbit(t))
		ins(root[t] , 1 , lcur , x , y) ;
}

int find(int x , int y , int k) {
	--x ;
	for (sA = 0 ; x > 0 ; x -= lowbit(x) , ++sA)
		A[sA] = root[x] ;
	for (sB = 0 ; y > 0 ; y -= lowbit(y) , ++sB)
		B[sB] = root[y] ;

	return query(1 , lcur , k) ;
}

void init() {
	lcur = cur = 0 ;
	for (int i = 0 ; i < MAX_N ; ++i) root[i] = &NULLNODE ;
}

int main() {
	maintain(&NULLNODE) ; NULLNODE.empty = 1 ;
	
	init() ;

	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d" , &t[i]) , list[++lcur] = t[i] ;
	for (int i = 0 ; i < m ; ++i) {
		char q = getchar() ;
		while (q < 'A' || q > 'Z') q = getchar() ;

		int x , y , k = -1 ;
		scanf("%d %d" , &x , &y) ;
		if (q == 'Q') scanf("%d" , &k) ;
		else list[++lcur] = y ;

		que[i].q = q == 'Q' ? 0 : 1 ;
		que[i].x = x ; que[i].y = y ; que[i].k = k ;
	}

	///
	
	std::sort(list + 1 , list + 1 + lcur) ;
	lcur = std::unique(list + 1 , list + 1 + lcur) - (list + 1) ;
	for (int i = 1 ; i <= n ; ++i) {
		int p = std::lower_bound(list + 1 , list + 1 + lcur , t[i]) - list ;
		update(i , p , 1) ;
	}

	///

	for (int i = 0 ; i < m ; ++i) {
		int q  = que[i].q , x = que[i].x , y = que[i].y , k = que[i].k , res ;

		if (!q) res = find(x , y , k) , printf("%d\n" , res) ;
		else {
			int px = std::lower_bound(list + 1 , list + 1 + lcur , t[x]) - list ,
			    py = std::lower_bound(list + 1 , list + 1 + lcur , y) - list ;

			update(x , px , -1) ; update(x , py , 1) ; t[x] = y ;
		}
	}

	return 0 ;
}
