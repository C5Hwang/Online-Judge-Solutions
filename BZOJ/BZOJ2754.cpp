#include <map>
#include <queue>
#include <stdio.h>
#include <stdlib.h>

#define eg std::map<int , Node*>
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 2e4 + 10 , MAX_M = 5e4 + 10 , MAX_L = 1e5 + 10 ;

struct Node {
	eg ch ;
	int val , ans , ap ;
	Node *last , *fail ;
}list[MAX_L] ;

std::queue<Node*> que ;
std::vector<int> nam[2][MAX_N] ;

Node *pt[MAX_M] , *root ;
int n , m , cur , len , s[MAX_L] , res[MAX_N] ;

Node *insert(Node *rt , int p) {
	if (p == len) {rt->ap = -1 ; ++rt->val ; return rt ;}

	int c = s[p] ;
	if (!rt->ch.count(c)) rt->ch[c] = &list[cur++] ;

	return insert(rt->ch[c] , p + 1) ;
}

void build() {
	que.push(root) ;
	root->fail = root->last = NULL ;

	for (; !que.empty() ;) {
		Node *x = que.front() ; que.pop() ;

		for (eg :: iterator to = x->ch.begin() ; to != x->ch.end() ; ++to) {
			int c = to->first ;
			Node *p = x->fail , *nx = to->second ;

			for (; p && !p->ch.count(c) ; p = p->fail) ;
			if (p) nx->fail = p->ch[c] ;
			else nx->fail = root ;

			nx->last = nx->fail->val ? nx->fail : nx->fail->last ;
			que.push(nx) ;
		}
	}
}

void update(Node *rt , int &sum , int p) {
	if (!rt) return ;

	if (rt->val && rt->ap != p) {
		sum += rt->val ;
		++rt->ans ; rt->ap = p ;
	}
	update(rt->last , sum , p) ;
}

int getans(int x) {
	int sum = 0 ;

	for (int ty = 0 ; ty < 2 ; ++ty) {
		Node *rt = root ;
		int len = nam[ty][x].size() ;

		for (int i = 0 ; i < len ; ++i) {
			int c = nam[ty][x][i] ;

			for(; rt && !rt->ch.count(c) ; rt = rt->fail) ;
			if (rt) {
				rt = rt->ch[c] ;
				update(rt , sum , x) ;
			}
			else rt = root ;
		}
	}

	return sum ;
}

void read() {
	scanf("%d" , &len) ;
	for (int j = 0 ; j < len ; ++j) scanf("%d" , &s[j]) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		read() ;
		for (int j = 0 ; j < len ; ++j) nam[0][i].push_back(s[j]) ;

		read() ;
		for (int j = 0 ; j < len ; ++j) nam[1][i].push_back(s[j]) ;
	}

	root = &list[cur++] ;
	for (int i = 0 ; i < m ; ++i) {
		read() ;
		pt[i] = insert(root , 0) ;
	}

	///

	build() ;
	for (int i = 0 ; i < n ; ++i) res[i] = getans(i) ;
	for (int i = 0 ; i < m ; ++i) printf("%d\n" , pt[i]->ans) ;
	for (int i = 0 ; i < n ; ++i) printf("%d " , res[i]) ;
	printf("\n") ;

	return 0 ;
}