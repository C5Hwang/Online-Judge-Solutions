#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 ;

struct Node {
	int num , s , r ;
	Node *ch[2] ;
}tre[MAX_N] ;

Node *root = NULL ;
int n , cur , len , a[MAX_N] , list[MAX_N] , res[MAX_N] ;

void update(Node *rt) {
	int sum = 1 ;
	for (int i = 0 ; i < 2 ; ++i)
		sum += rt->ch[i] ? rt->ch[i]->s : 0 ;

	rt->s = sum ;
}

void rotate(Node *&rt , int d) {
	Node *son = rt->ch[d^1] ;

	rt->ch[d^1] = son->ch[d] ; son->ch[d] = rt ; rt = son ;
	update(rt->ch[d]) ; update(rt) ;
}

void ins(Node *&rt , int p , int a) {
	if (!rt) {
		rt = &tre[++cur] ;
		rt->num = a ; rt->s = 1 ; rt->r = rand() ;
		rt->ch[0] = rt->ch[1] = 0 ;
		
		return ;
	}

	int k = rt->ch[0] ? rt->ch[0]->s + 1 : 1 ,
	    d = p <= k ? 0 : 1 ;

	ins(rt->ch[d] , p - k * d , a) ; update(rt) ;
	if (rt->ch[d]->r < rt->r) rotate(rt , d^1) ;
}

int query(Node *rt , int p) {
	int k = rt->ch[0] ? rt->ch[0]->s + 1 : 1 ,
	    d = p <= k ? 0 : 1 ;

	if (p == k) return rt->num ;
	else return query(rt->ch[d] , p - k * d) ;
}

int find(int L , int R , int a) {
	while (L + 1 < R) {
		int mid = (L + R) / 2 ;
		if (list[mid] > a) R = mid ;
		else L = mid ;
	}
	
	return R ;
}

int main() {
	scanf("%d" , &n) ;
	for (int i = 1 ; i <= n ; ++i) {
		int p ;
		scanf("%d" , &p) ; ++p ;
		ins(root , p , i) ;
	}

	///
	
	a[0] = 0 ;
	for (int i = 1 ; i <= n ; ++i)
		a[i] = query(root , i) ;
	
	///
	
	res[a[1]] = 1 ; list[++len] = a[1] ;
	for (int i = 2 ; i <= n ; ++i) {
		int p = find(0 , len + 1 , a[i]) ;
		if (p > len) list[++len] = a[i] ;
		else if (list[p] > a[i]) list[p] = a[i] ;

		res[a[i]] = p ;
	}

	int ans = res[1] ;
	printf("%d\n" , ans) ;
	for (int i = 2 ; i <= n ; ++i)
		ans = std::max(ans , res[i]) , printf("%d\n" , ans) ;

	return 0 ;
}
