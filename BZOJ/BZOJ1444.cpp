#include <queue>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define idx(x) (x - root)
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-8 ;
const int MAX_N = 10 + 5 , MAX_L = 100 + 10 ;

struct Node{
	bool word ;
	Node *ch[MAX_N] , *fail ;

	void init() {
		word = 0 ; fail = NULL ;
		for (int i = 0 ; i < MAX_N ; ++i) ch[i] = NULL ;
	}
}list[MAX_L] ;

std::queue<Node*> que ;

char s[MAX_N] ;
bool ok[MAX_N] ;
int n , m , len , cur ;
Node *root , *pt[MAX_N] ;
db P[MAX_N] , A[MAX_L][MAX_L] ;

bool check() {
	for (int i = 0 ; i < len ; ++i) {
		int c = s[i] - 'A' ;
		if (c >= m) return 0 ;
		else if (P[c] < eps) return 0 ;
	}

	return 1 ;
}

Node *insert(Node *&rt , int p) {
	if (!rt) (rt = &list[cur++])->init() ;
	if (p == len) {rt->word = 1 ; return rt ;}

	int c = s[p] - 'A' ;
	return insert(rt->ch[c] , p + 1) ;
}

void build() {
	//Notice: Don't need to update fail.

	que.push(root) ;
	root->fail = NULL ;

	for (; !que.empty() ;) {
		Node *x = que.front() ; que.pop() ;

		for (int i = 0 ; i < m ; ++i) {
			Node *nx = x->ch[i] ;
			if (!nx) continue ;

			Node *p = x->fail ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) nx->fail = p->ch[i] ;
			else nx->fail = root ;

			que.push(nx) ;
		}
	}
}

void gauss() {
	for (int i = 0 ; i < cur ; ++i) {
		int r = i ;
		for (int j = i + 1 ; j < cur ; ++j) if (fabs(A[r][i]) - fabs(A[j][i]) < eps) r = j ;
		if (r != i) for (int j = 0 ; j <= cur ; ++j) std::swap(A[r][j] , A[i][j]) ;

		for (int j = i + 1 ; j < cur ; ++j) {
			db tmp = A[j][i] / A[i][i] ;
			for (int k = i ; k <= cur ; ++k) A[j][k] -= A[i][k] * tmp ;
		}
	}

	for (int i = cur - 1 ; i >= 0 ; --i) {
		for (int j = i + 1 ; j < cur ; ++j) A[i][cur] -= A[i][j] * A[j][cur] ;
		A[i][cur] /= A[i][i] ;
	}
}

int main() {
	scanf("%d %d %d" , &n , &len , &m) ;
	for (int i = 0 ; i < m ; ++i) {
		int p , q ; scanf("%d %d" , &p , &q) ;
		P[i] = p * 1.0 / q ;
	}

	(root = &list[cur++])->init() ;
	for (int i = 0 ; i < n ; ++i) {
		scanf("%s" , s) ; ok[i] = check() ;
		if (ok[i]) pt[i] = insert(root , 0) ;
	}

	///

	build() ;
	for (Node *x = root ; x != list + cur ; ++x) {
		A[idx(x)][idx(x)] = -1 ;
		if (x->word) continue ;

		for (int i = 0 ; i < m ; ++i) {
			Node *p = x ;
			for (; p && !p->ch[i] ; p = p->fail) ;
			if (p) p = p->ch[i] ;
			else p = root ;

			A[idx(p)][idx(x)] += P[i] ;
		}
	}
	A[idx(root)][cur] = -1 ;

	gauss() ;

	///

	for (int i = 0 ; i < n ; ++i)
		if (ok[i]) printf("%0.2lf\n" , A[idx(pt[i])][cur]) ;
		else printf("0.00\n") ;

	return 0 ;
}