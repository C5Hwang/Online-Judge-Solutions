#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100000 + 10 , lgN = 20 ;
 
struct Node {
	int s ;
	Node *ch[2] ;
}tree[MAX_N * lgN] ;
struct Link {
	int num ;
	Link *next ;
}list[2 * MAX_N] ;
struct Value {
	int a , bh ;
}val[MAX_N] ;
 
Link *head[MAX_N] ;
Node *root[MAX_N] ;
int n , m , cur1 , cur2 , dep[MAX_N] , f[MAX_N][lgN] , anum[MAX_N] ;
 
void build(Node *&rt , int x , int y) {
	rt = &tree[cur1++] ;
	rt->s = 0 ; rt->ch[0] = rt->ch[1] = NULL ;

	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	build(rt->ch[0] , x , mid) ;
	build(rt->ch[1] , mid + 1 , y) ;
}
 
void update(Node *r1 , Node *&r2 , int x , int y , int f) {
	if (f < x || y < f) return ;

	r2 = &tree[++cur1] ;
	*r2 = *r1 ; ++r2->s ;

	if (x == y) return ;

	int mid = (x + y) >> 1 ;

	update(r1->ch[0] , r2->ch[0] , x , mid , f) ;
	update(r1->ch[1] , r2->ch[1] , mid + 1 , y , f) ;
}
 
int query(Node *r1 , Node *r2 , Node *r3 , Node *r4 , int x , int y , int k) {
	if (x == y) return anum[x] ;

	int sum = r1->ch[0]->s + r2->ch[0]->s - r3->ch[0]->s - r4->ch[0]->s ,
	    mid = (x + y) >> 1 ;

	if (sum >= k) return query(r1->ch[0] , r2->ch[0] , r3->ch[0] , r4->ch[0] , x , mid , k) ;
	else return query(r1->ch[1] , r2->ch[1] , r3->ch[1] , r4->ch[1] , mid + 1 , y , k - sum) ;
}
 
///
 
void dfs(int x , int fa) {
	update(root[fa] , root[x] , 1 , n , val[x].a) ;
	f[x][0] = fa ; dep[x] = dep[fa] + 1 ;

	Link *h = head[x] ;
	for (; h ; h = h->next)	{
		int nx = val[h->num].bh ;

		if (nx == fa) continue ;

		dfs(nx , x) ;
	}
}
 
int LCA(int x , int y) {
	if (dep[x] > dep[y]) std::swap(x , y) ;

	for (int i = lgN - 1 ; i >= 0 ; --i) {
		int fa = f[y][i] ;
		if (dep[fa] >= dep[x]) y = fa ;
	}

	if (x == y) return x ;

	for (int i = lgN - 1 ; i >= 0 ; --i) {
		int f1 = f[x][i] , f2 = f[y][i] ;
		if (f1 != f2) x = f1 , y = f2 ;
	}

	return f[x][0] ;
}
 
void ins(int x , int y) {
	list[cur2].num = y ;
	list[cur2].next = head[x] ;
	head[x] = &list[cur2++] ;
}
 
///
 
bool cmp1(Value x , Value y) {
	return x.a < y.a ;
}
bool cmp2(Value x , Value y) {
	return x.bh < y.bh ;
}
 
int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i <= n ; ++i)
		scanf("%d" , &val[i].a) , val[i].bh = i ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ;
		ins(x , y) ; ins(y , x) ;
	}

	///
	
	std::sort(val + 1 , val + n + 1 , cmp1) ;

	int last = val[1].a , s = 1 ;
	val[1].a = 1 ; anum[s] = last ;

	for (int i = 2 ; i <= n ; ++i)
		if (val[i].a == last) val[i].a = s ;
		else last = val[i].a , val[i].a = ++s , anum[s] = last ;

	std::sort(val + 1 , val + n + 1 , cmp2) ;

	///
	
	build(root[0] , 1 , n) ;
	dfs(1 , 0) ;
	
	///
	
	for (int j = 1 ; j < lgN ; ++j)
		for (int i = 1 ; i <= n ; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1] ;

	///
	
	int res = 0 ;
	for (int i = 0 ; i < m ; ++i) {
		int u , v , k , fa ;
		scanf("%d %d %d" , &u , &v , &k) ; u ^= res ;
		fa = LCA(u , v) ;

		res = query(root[u] , root[v] , root[fa] , root[f[fa][0]] , 1 , n , k) ;
 
		printf("%d" , res) ;
		if (i != m - 1) printf("\n") ;
	}
 
	return 0 ;
}
