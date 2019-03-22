#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e5 + 10 , MAX_T = 2e5 + 10 , lgN = 20 + 5 ;

struct Node {
	int minl , maxl , pl ;
	Node *ch[26] , *fail ;
}sam[MAX_T] ;
struct TREE {
	int num ;
	TREE *ch[2] ;
}tre[MAX_T * lgN] ;
struct Link {
	int num ;
	Link *next ;
}list[MAX_T] ;

Node *last ;
char s[MAX_N] ;
Link *head[MAX_T] ;
TREE *root[MAX_T] ;
int n , m , tot , cur , samp[MAX_T] , fa[MAX_T][lgN] ;
int ti , dfn[MAX_T] , ed[MAX_T] , dfp[MAX_T] , dep[MAX_T] , mk[MAX_T] ;

///

Node *extend(int c , int pt) {
	Node *cur = &sam[tot++] , *p = last ;
	cur->maxl = last->maxl + 1 ; cur->pl = pt ;

	for (; p && !p->ch[c] ; p = p->fail) p->ch[c] = cur ;
	if (!p) cur->fail = &sam[0] ;
	else {
		Node *q = p->ch[c] ;
		if (p->maxl + 1 == q->maxl) cur->fail = q ;
		else {
			Node *clone = &sam[tot++] ;
			*clone = *q ; clone->maxl = p->maxl + 1 ; clone->pl = 0 ;

			for (; p && p->ch[c] == q ; p = p->fail) p->ch[c] = clone ;
			cur->fail = q->fail = clone ; q->minl = clone->maxl + 1 ;
		}
	}

	cur->minl = cur->fail->maxl + 1 ;
	return (last = cur) ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x) {
	dfn[x] = ++ti ; dfp[ti] = x ;
	for (Link *h = head[x] ; h ; h = h->next)
		{fa[h->num][0] = x ; dep[h->num] = dep[x] + 1 ; dfs(h->num) ;}
	ed[x] = ti ;
}

///

void modify(TREE *ort , TREE *&rt , int x , int y , int p) {
	rt = &tre[cur++] ;
	*rt = *ort ; ++rt->num ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	if (p <= mid) modify(ort->ch[0] , rt->ch[0] , x , mid , p) ;
	else modify(ort->ch[1] , rt->ch[1] , mid + 1 , y , p) ;
}

int find(TREE *r1 , TREE *r2 , int x , int y , int fx , int fy) {
	if (y < fx || fy < x) return 0 ;
	if (!(r1->num - r2->num)) return 0 ;
	if (fx <= x && y <= fy) return r1->num - r2->num ;

	int mid = (x + y) >> 1 ,
		s1 = find(r1->ch[0] , r2->ch[0] , x , mid , fx , fy) ,
		s2 = find(r1->ch[1] , r2->ch[1] , mid + 1 , y , fx , fy) ;

	return s1 + s2 ;
}

///

int jump(int p , int l) {
	if (sam[p].minl <= l) return p ;

	for (int k = mk[dep[p]] ; k >= 0 ; --k) {
		int np = fa[p][k] ;
		if (l < sam[np].minl) p = np ;
	}

	return fa[p][0] ;
}

bool check(int a , int b , int c , int l) {
	a = a + l - 1 ;
	int pt = jump(samp[c] , l) ;

	return find(root[ed[pt]] , root[dfn[pt] - 1] , 0 , n , a , b) ;
}

///

int main() {
	scanf("%d %d %s" , &n , &m , s) ;
	for (int i = n ; i ; --i) s[i] = s[i - 1] ;
	for (int i = n ; i ; --i) {
		int j = n - i + 1 ;
		if (i > j) std::swap(s[i] , s[j]) ;
		else break ;
	}

	///

	last = &sam[tot++] ;
	for (int i = 1 ; i <= n ; ++i) samp[i] = extend(s[i] - 'a' , i) - &sam[0] ;
	for (int i = 1 ; i < tot ; ++i) ins(sam[i].fail - &sam[0] , i) ;

	///

	mk[0] = mk[1] = 1 ;
	for (int i = 2 ; i <= tot ; ++i) mk[i] = mk[i >> 1] + 1 ;

	fa[0][0] = 0 ; dep[0] = 1 ;
	dfs(0) ;

	for (int j = 1 ; (1 << j) <= tot ; ++j)
		for (int i = 0 ; i < tot ; ++i) fa[i][j] = fa[fa[i][j - 1]][j - 1] ;

	cur = 0 ; root[0] = &tre[cur++] ;
	root[0]->ch[0] = root[0]->ch[1] = root[0] ;
	for (int i = 1 ; i <= tot ; ++i) modify(root[i - 1] , root[i] , 0 , n , sam[dfp[i]].pl) ;

	///

	for (; m-- ;) {
		int a , b , c , d ;
		scanf("%d %d %d %d" , &a , &b , &c , &d) ;
		a = n - a + 1 ; b = n - b + 1 ; c = n - c + 1 ; d = n - d + 1 ;
		std::swap(a , b) ; std::swap(c , d) ;

		int L = 0 , R = std::min(b - a + 1 , d - c + 1) + 1 ;
		for (; L + 1 < R ;) {
			int mid = (L + R) >> 1 ;
			if (check(a , b , d , mid)) L = mid ;
			else R = mid ;
		}

		printf("%d\n" , L) ;
	}

	return 0 ;
}