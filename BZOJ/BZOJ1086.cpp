#include <stack>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 1e3 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

std::stack<int> sta ;

Link *head[MAX_N] ;
int n , B , tot , cur , siz[MAX_N] , belong[MAX_N] , cap[MAX_N] ;

void dfs(int x , int fa) {
	sta.push(x) ;

	siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		dfs(nx , x) ;

		siz[x] += siz[nx] ;
		if (siz[x] > B) {
			++tot ;
			for (; sta.top() != x ; sta.pop() , --siz[x])
				belong[sta.top()] = tot ;
			cap[tot] = x ;
		}
	}
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

int main() {
	scanf("%d %d" , &n , &B) ;
	for (int i = 1 ; i < n ; ++i) {
		int a , b ; scanf("%d %d" , &a , &b) ;
		ins(a , b) ; ins(b , a) ;
	}

	///

	dfs(1 , 1) ;

	for (; !sta.empty() ; sta.pop()) belong[sta.top()] = tot ;

	///

	printf("%d\n" , tot) ;
	for (int i = 1 ; i <= n ; ++i) printf("%d " , belong[i]) ;
	printf("\n") ;
	for (int i = 1 ; i <= tot ; ++i) printf("%d " , cap[i]) ;
	printf("\n") ;

	return 0 ;
}