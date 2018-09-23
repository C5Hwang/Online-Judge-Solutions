#include <stack>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_N = 100 + 10 , MAX_C = 'z' + 10 , INF = 0x3f3f3f3f ;

struct data {
	char bl ;
	int bh ;
} ;
struct FOR {
	int x , y ;
}rew[MAX_N] ;

std::stack<data> st ;

int T , l , tot , f[MAX_N] ;
char rt[50] , x[50] , y[50] ;
bool ap[MAX_C] , nodo[MAX_N] ;

bool check() {
	if (x[0] == 'n') return 0 ;
	if (y[0] == 'n') return 1 ;
	
	return 0 ;
}

int ToNUM(char *s) {
	if (s[0] == 'n') return INF ;
	
	int num = 0 , len = strlen(s) ;
	for (int i = 0 ; i < len ; ++i) num = num * 10 + s[i] - '0' ;
	
	return num ;
}

void init() {
	tot = 0 ;
	memset(f , 0 , sizeof(f)) ;
	memset(ap , 0 , sizeof(ap)) ;
	memset(nodo , 0 , sizeof(nodo)) ;
	
	for (; !st.empty() ; st.pop()) ;
}

int main() {
	freopen("complexity.in" , "r" , stdin) ;
	freopen("complexity.out" , "w" , stdout) ;
	
	scanf("%d" , &T) ;
	while (T--) {
		init() ;
		scanf("%d %s" , &l , rt) ;
		
		bool err = 0 ;
		for (int i = 0 ; i < l ; ++i) {
			char op , a ;
			scanf(" %c" , &op) ;
			
			///
			
			if (op == 'F') {
				scanf(" %c %s %s" , &a , &x , &y) ;
				if (ap[a]) err = 1 ;
				if (err) continue ;
				
				ap[a] = 1 ; ++tot ;
				if (st.empty()) {f[tot] = check() ;}
				else {					
					data tp = st.top() ;
					
					if (!nodo[tp.bh]) f[tot] = f[tp.bh] + check() ;
					else {nodo[tot] = 1 ; f[tot] = 0 ;}
				}
				
				rew[tot] = (FOR){ToNUM(x) , ToNUM(y)} ;
				if (rew[tot].x > rew[tot].y) nodo[tot] = 1 ;
				st.push((data){a , tot}) ;
			}
			else {
				if (st.empty()) err = 1 ;
				if (err) continue ;
				
				data tp = st.top() ;
				ap[tp.bl] = 0 ; st.pop() ;
			}
		}
		
		///
		
		if (!st.empty()) err = 1 ;
		if (err) {printf("ERR\n") ; continue ;}
		
		int ans = 0 , need = 0 ;
		if (rt[2] == '1') need = 0 ;
		else {
			need = rt[4] - '0' ;
			for (int i = 5 ; rt[i] >= '0' && rt[i] <= '9' ; ++i) need = need * 10 + rt[i] - '0' ;
		}
		
		for (int i = 1 ; i <= tot ; ++i) ans = std::max(ans , f[i]) ;
		if (ans == need) printf("Yes\n") ;
		else printf("No\n") ;
	}
	
	fclose(stdin) ; fclose(stdout) ;
	
	return 0 ;
}
