#include <map>
#include <stack>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 500 + 10 ;

struct Link {
	int num ;
	Link *next ;
}list[MAX_N << 1] ;

std::stack<int> sta ;
std::map<int , int> ap ;
std::vector<int> dcc[MAX_N] ;

bool pt[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , ti , cnt , dfn[MAX_N] , low[MAX_N] ;

void init() {
	ap.clear() ;
	for (; !sta.empty() ; sta.pop()) ;
	for (int i = 1 ; i <= n ; ++i) head[i] = NULL ;
	for (int i = 1 ; i <= cnt ; ++i) dcc[i].clear() ;

	n = cur = ti = cnt = 0 ;
}

void ins(int x , int y) {
	list[cur].num = y ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void dfs(int x , int fa) {
	sta.push(x) ;
	dfn[x] = low[x] = ++ti ;

	int son = 0 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa) continue ;

		if (!dfn[nx]) {
			dfs(nx , x) ; ++son ;
			low[x] = std::min(low[x] , low[nx]) ;

			if (low[nx] >= dfn[x]) {
				if (x != fa || son > 1) pt[x] = 1 ;

				++cnt ;
				for (; sta.top() != x ; sta.pop()) dcc[cnt].push_back(sta.top()) ;
				dcc[cnt].push_back(x) ;
			}
		}
		else low[x] = std::min(dfn[nx] , low[x]) ;
	}
}

int main() {
	scanf("%d" , &m) ;
	for (int NUM = 1 ; m ; scanf("%d" , &m) , ++NUM) {
		init() ;

		for (int i = 0 ; i < m ; ++i) {
			int a , b ; scanf("%d %d" , &a , &b) ;

			if (!ap.count(a)) {++n ; ap[a] = n ; a = n ;}
			else a = ap[a] ;
			if (!ap.count(b)) {++n ; ap[b] = n ; b = n ;}
			else b = ap[b] ;

			ins(a , b) ; ins(b , a) ;
		}

		///

		for (int i = 1 ; i <= n ; ++i) dfn[i] = low[i] = 0 , pt[i] = 0 ;
		for (int i = 1 ; i <= n ; ++i) if (!dfn[i]) dfs(i , i) ;

		int ans = 0 ; ll sum = 1 ;
		for (int i = 1 ; i <= cnt ; ++i) {
			int len = dcc[i].size() , s = 0 ;
			for (int j = 0 ; j < len ; ++j) if (pt[dcc[i][j]]) ++s ;

			if (s == 1) ++ans , sum *= std::max(len - 1 , 1) ;
			else if (!s) {ans += 2 , sum *= std::max(len * (len - 1) >> 1 , 1) ;}
		}

		printf("Case %d: %d %lld\n" , NUM , ans , sum) ;
	}

	return 0 ;
}