#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 1e5 + 10 , INF = 0x3f3f3f3f ;

struct Read {
	int a , bh ;
}t[MAX_N] ;
struct Tree {
	int num , s , minn ; bool flip ;
	Tree *ch[2] , *fa ;

	int GetSon() {return fa->ch[1] == this ;}
	int GetRank() {return ch[0] ? ch[0]->s + 1 : 1 ;}
	void down() {
		if (!flip) return ;
		std::swap(ch[0] , ch[1]) ;

		if (ch[0]) ch[0]->flip ^= 1 ;
		if (ch[1]) ch[1]->flip ^= 1 ;
		flip = 0 ;
	}
	void update() {
		s = 1 ; minn = num ;
		for (int i = 0 ; i < 2 ; ++i) {
			s += ch[i] ? ch[i]->s : 0 ;
			if (ch[i]) minn = std::min(minn , ch[i]->minn) ;
		}
	}
}spy[MAX_N] ;

///

Tree *root ;
int n , cur ;

///

bool cmp1(Read x , Read y) {return x.a < y.a || x.a == y.a && x.bh < y.bh ;}
bool cmp2(Read x , Read y) {return x.bh < y.bh ;}

void init() {
	std::sort(t + 1 , t + 1 + n , cmp1) ;
	for (int i = 1 ; i <= n ; ++i) t[i].a = i ;
	std::sort(t + 1 , t + 1 + n , cmp2) ;

	cur = 0 ;
	t[0].a = t[n + 1].a = INF ;
}

void build(Tree *&rt , int x , int y) {
	if (x > y) {rt = NULL ; return ;}

	int mid = (x + y) >> 1 ;

	rt = &spy[cur++] ;
	rt->fa = NULL ; rt->num = t[mid].a ; rt->flip = 0 ;

	build(rt->ch[0] , x , mid - 1) ;
	build(rt->ch[1] , mid + 1 , y) ;

	if (rt->ch[0]) rt->ch[0]->fa = rt ;
	if (rt->ch[1]) rt->ch[1]->fa = rt ;
	rt->update() ;
}


///

void rotate(Tree *rt , int d) {
	Tree *f = rt->fa ;

	if (f->fa) {
		int fd = f->GetSon() ;
		f->fa->ch[fd] = rt ;
	}
	else root = rt ;
	if (rt->ch[d]) rt->ch[d]->fa = f ;
	
	f->ch[d^1] = rt->ch[d] ; rt->ch[d] = f ;
	rt->fa = f->fa ; f->fa = rt ;
	
	f->update() ;
}

void splay(Tree *&e , Tree *rt) {
	while (rt != e) {
		int d = rt->GetSon() ;
		Tree *f = rt->fa ;

		if (f != e) {
			int fd = f->GetSon() ;

			if (fd^d) rotate(rt , d^1) , d ^= 1 ;
			else rotate(f , fd^1) ;
		}

		rotate(rt , d^1) ;
	}

	rt->update() ;
}

///

Tree *find(Tree *rt , int k) {
	rt->down() ;
	int r = rt->GetRank() ;

	if (r == k) return rt ;
	else if (r > k) return find(rt->ch[0] , k) ;
	else return find(rt->ch[1] , k - r) ;
}

int FindMIN(Tree *rt) {
	rt->down() ;
	int m = rt->minn , r = rt->GetRank() ;

	if (rt->ch[0] && rt->ch[0]->minn == m) return FindMIN(rt->ch[0]) ;
	else if (rt->num == m) return r ;
	else return FindMIN(rt->ch[1]) + r ;
}

void change(Tree *rt , int k) {
	rt->down() ;
	int r = rt->GetRank() ;

	if (r == k) rt->num = INF ;
	else if (r > k) change(rt->ch[0] , k) ;
	else change(rt->ch[1] , k - r) ;

	rt->update() ;
}

///

int main() {
	scanf("%d" , &n) ;
	while (n != 0) {
		for (int i = 1 ; i <= n ; ++i)
			scanf("%d" , &t[i].a) , t[i].bh = i ;
		
		///

		init() ;
		build(root , 0 , n + 1) ;

		///
		
		for (int i = 1 ; i <= n ; ++i) {
			int mp = FindMIN(root) ;
			Tree *L = find(root , i) , *R = find(root , mp + 1) ;

			splay(root , L) ; splay(root->ch[1] , R) ;
			change(root , mp) ;

			root->ch[1]->ch[0]->flip ^= 1 ;
			printf("%d" , mp - 1) ;
			if (i != n) printf(" ") ;
		}

		printf("\n") ;

		scanf("%d" , &n) ;
	}

	return 0 ;
}
