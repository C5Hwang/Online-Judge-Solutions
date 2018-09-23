#include <stdio.h>
#include <stdlib.h>

#define ll long long

const int MAX_N = 40 + 10 , MAX_S = 11e5 + 10 , hnum = 1572869 ;

struct data {
	int ti ;
	ll oper ;
} ;
struct Hash {
	ll onsta ;
	data opt ;
	Hash *next ;
}posi[2 * MAX_S] ;


bool v[MAX_N][MAX_N] ;
Hash *head[2][hnum + 10] ;
int n , m , cur , tot , a[MAX_N] ;
ll allon , insta , op[MAX_N] , allsta[MAX_S] ;

///

Hash *find(int ty , ll lon) {
	ll h = lon % hnum ;

	Hash *p = head[ty][h] ;
	while (p && p->onsta != lon) p = p->next ;

	return p ;
}

void put(int ty , ll lon , data sta) {
	ll h = lon % hnum ;

	Hash *p = head[ty][h] ;
	if (!p) {
		head[ty][h] = p = &posi[cur++] ;
		*p = (Hash){lon , sta , NULL} ;
	}
	else {
		while (p->next && p->onsta != lon) p = p->next ;
		if (p->onsta != lon) {
			p->next = p = &posi[cur++] ;
			*p = (Hash){lon , sta , NULL} ;
		}
		else if (p->opt.ti > sta.ti) p->opt = sta ;
	}
}

///

void dfs(int ty , int x , int ed , ll lon , data sta) {
	if (x == ed) {
		Hash *p = find(ty , lon) ;
		if (!p) put(ty , lon , sta) ;
		else if (p->opt.ti > sta.ti) p->opt = sta ;

		if (!ty) allsta[tot++] = lon ;

		return ;
	}

	dfs(ty , x + 1 , ed , lon , sta) ;

	++sta.ti ; sta.oper |= ((ll)1 << x) ;
	dfs(ty , x + 1 , ed , lon ^ op[x] , sta) ;
}

///

int main() {
	freopen("alice.in" , "r" , stdin) ;
	freopen("alice.out" , "w" , stdout) ;

	scanf("%d %d" , &n , &m) ;
	for (int i = 0 ; i < n ; ++i) {
		int a ;
		scanf("%d" , &a) ; v[i][i] = 1 ;
		insta += ((ll)1 << i) * a ;
	}
	allon = ((ll)1 << n) - 1 ;

	///
	
	for (int i = 0 ; i < m ; ++i) {
		int x , y ;
		scanf("%d %d" , &x , &y) ; --x ; --y ;
		v[x][y] = v[y][x] = 1 ;
	}
	for (int i = 0 ; i < n ; ++i)
		for (int j = 0 ; j < n ; ++j)
			if (v[i][j]) op[i] += (ll)1 << j ;

	///
	
	dfs(0 , 0 , n / 2 , 0 , (data){0 , 0}) ;
	dfs(1 , n / 2 , n , 0 , (data){0 , 0}) ;

	///
	
	ll ans = 0 ;
	int res = n + 1 ;
	for (int i = 0 ; i < tot ; ++i) {
		ll p = allsta[i] , q = allon ^ insta ^ p ;
		Hash *pa = find(0 , p) , *pb = find(1 , q) ;

		if (!pb) continue ;

		data a = pa->opt , b = pb->opt ;
		if (a.ti + b.ti < res) {
			res = a.ti + b.ti ;
			ans = a.oper | b.oper ;
		}
	}

	printf("%d\n" , res) ;
	for (int i = 0 ; i < n ; ++i)
		if (ans & ((ll)1 << i)) printf("%d " , i + 1) ;
	printf("\n") ;

	fclose(stdin) ; fclose(stdout) ;

	return 0 ;
}
