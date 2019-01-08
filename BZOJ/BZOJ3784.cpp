#include <queue>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e4 + 10 , lgN = 20 + 5 ;

struct Link {
	int num , val ;
	Link *next ;
}list[MAX_N << 1] ;
struct data {
	int pl , dis , pL , pR ;

	friend bool operator <(data x , data y) {return x.dis < y.dis ;}
}tmp[MAX_N * lgN] ;

std::priority_queue<data> pq ;

bool vis[MAX_N] ;
Link *head[MAX_N] ;
int n , m , cur , root , msiz , tot , siz[MAX_N] ;
int cnt , dt , lgk[MAX_N * lgN] , dis[MAX_N * lgN] , f[MAX_N * lgN][lgN] ;

void ins(int x , int y , int v) {
	list[cur].num = y ;
	list[cur].val = v ;
	list[cur].next = head[x] ;
	head[x] = &list[cur++] ;
}

void findroot(int x , int fa) {
	int mx = 0 ; siz[x] = 1 ;
	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		findroot(nx , x) ;
		siz[x] += siz[nx] ; mx = std::max(mx , siz[nx]) ;
	}
	mx = std::max(mx , tot - siz[x]) ;

	if (msiz > mx) msiz = mx , root = x ;
}

void count(int x , int fa , int L , int R , int d) {
	dis[++cnt] = d ; tmp[dt++] = (data){cnt , 0 , L , R} ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (nx == fa || vis[nx]) continue ;

		count(nx , x , L , R , d + h->val) ;
	}
}

void work(int x) {
	dis[++cnt] = 0 ; vis[x] = 1 ;
	int L , R ; L = R = cnt ;

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		count(nx , nx , L , R , h->val) ;
		R = cnt ;
	}

	for (Link *h = head[x] ; h ; h = h->next) {
		int nx = h->num ;
		if (vis[nx]) continue ;

		root = 0 ; msiz = tot = siz[nx] ;
		findroot(nx , nx) ;
		work(root) ;
	}
}

int cmp(int a , int b) {
	if (dis[a] > dis[b]) return a ;
	else return b ;
}

int find(int x , int y) {
	int len = y - x + 1 , k = lgk[len] ;

	return cmp(f[x][k] , f[y - (1 << k) + 1][k]) ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	for (int i = 1 ; i < n ; ++i) {
		int x , y , v ;
		scanf("%d %d %d" , &x , &y , &v) ;
		ins(x , y , v) ; ins(y , x , v) ;
	}

	///

	root = 0 ; msiz = tot = n ;
	findroot(1 , 1) ;
	work(root) ;

	for (int i = 1 ; i <= cnt ; ++i) f[i][0] = i ;
	for (int i = 2 ; i <= cnt ; ++i) lgk[i] = lgk[i >> 1] + 1 ;
	for (int j = 1 ; (1 << j) <= cnt ; ++j)
		for (int i = 1 ; i <= cnt ; ++i) {
			int t = i + (1 << (j - 1)) ;
			if (t > cnt) f[i][j] = f[i][j - 1] ;
			else f[i][j] = cmp(f[i][j - 1] , f[t][j - 1]) ;
		}
	for (int i = 0 ; i < dt ; ++i) {
		data *p = &tmp[i] ;
		p->dis = dis[p->pl] + dis[find(p->pL , p->pR)] ;
		pq.push(*p) ;
	}

	///

	for (; m-- ;) {
		data t = pq.top() ;
		printf("%d\n" , t.dis) ; pq.pop() ;

		int a = find(t.pL , t.pR) , na ;
		if (a != t.pL) {
			na = find(t.pL , a - 1) ;
			pq.push((data){t.pl , dis[na] + dis[t.pl] , t.pL , a - 1}) ;
		}
		if (a != t.pR) {
			na = find(a + 1 , t.pR) ;
			pq.push((data){t.pl , dis[na] + dis[t.pl] , a + 1 , t.pR}) ;
		}
	}

	return 0 ;
}