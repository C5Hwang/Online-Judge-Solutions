#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e5 + 10 , lgN = 20 + 5 ;

struct Node {
	int sum ;
	Node *ch[2] ;

	void init(int a) {sum = 0 ; ch[0] = ch[1] = NULL ;}
}tre[MAX_N * lgN] ;
struct Query {
	int x , y , k ;
}a[MAX_N] ;

std::vector<int> bul[MAX_N] ;

Node *root[MAX_N] ;
int n , m , mx , cur , ans[MAX_N] ;

///

inline int read() {
	char c = getchar() ;
	int num = 0 , f = 1 ;

	for (; c < '0' || c > '9' ; c = getchar()) if (c == '-') f = -f ;
	for (; c >= '0' && c <= '9' ; c = getchar()) num = num * 10 - '0' + c ;

	return num * f ;
}

void build(Node *&rt , int x , int y) {
	rt = &tre[cur++] ;
	rt->init(0) ;

	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	build(rt->ch[0] , x , mid) ; build(rt->ch[1] , mid + 1 , y) ;
}

void modify(Node *ort , Node *&rt , int x , int y , int f) {
	rt = &tre[cur++] ;
	*rt = *ort ; ++rt->sum ;

	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	if (f <= mid) modify(ort->ch[0] , rt->ch[0] , x , mid , f) ;
	else modify(ort->ch[1] , rt->ch[1] , mid + 1 , y , f) ;
}

int find(Node *r1 , Node *r2 , int x , int y , int k) {
	if (x == y) return x ;

	int s = r1->ch[0]->sum - r2->ch[0]->sum , mid = (x + y) >> 1 ;

	if (k <= s) return find(r1->ch[0] , r2->ch[0] , x , mid , k) ;
	else return find(r1->ch[1] , r2->ch[1] , mid + 1 , y , k - s) ;
}

///

int main() {
	freopen("shooting.in" , "r" , stdin) ;
	freopen("shooting.out" , "w" , stdout) ;

	n = read() ; m = read() ;
	for (int i = 0 ; i < n ; ++i) {
		Query *p = &a[i] ;
		p->x = read() ; p->y = read() ; p->k = read() ;

		mx = std::max(mx , p->y) ;
	}
	for (int i = 1 ; i <= m ; ++i) {
		int x = read() ;
		bul[x].push_back(i) ;

		mx = std::max(mx , x) ;
	}

	///

	build(root[0] , 1 , n) ;
	for (int i = 1 ; i <= mx ; ++i) {
		Node *nrt = root[i - 1] ;
		int len = bul[i].size() ;

		for (int j = 0 ; j < len ; ++j) {
			Node *tmp = NULL ;
			modify(nrt , tmp , 1 , n , bul[i][j]) ;
			nrt = tmp ;
		}

		root[i] = nrt ;
	}

	///

	for (int i = 0 ; i < n ; ++i) {
		Query *p = &a[i] ;
		if (root[p->y]->sum - root[p->x - 1]->sum < p->k) continue ;

		++ans[find(root[p->y] , root[p->x - 1] , 1 , n , p->k)] ;
	}

	for (int i = 1 ; i <= m ; ++i) printf("%d\n" , ans[i]) ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}