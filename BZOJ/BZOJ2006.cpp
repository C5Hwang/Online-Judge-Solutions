#include <queue>
#include <stdio.h>
#include <stdlib.h>

#define ll long long
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , lgN = 30 + 5 , INF = 0x3f3f3f3f ;

struct data {
	int val , pt ;

	friend bool operator <(data x , data y) {return x.val < y.val || (x.val == y.val && x.pt < y.pt) ;}
} ;
struct Node {
	int sum ;
	Node *ch[2] ;

	void init() {sum = 0 ; ch[0] = ch[1] = NULL ;}
}tre[MAX_N * lgN] ;

std::priority_queue<data> pq ;

Node *root[MAX_N] ;
int n , m , L , R , sL , sR , tot , a[MAX_N] , s[MAX_N] , kth[MAX_N] ;

Node *add(Node *ort , int x , int y , int f) {
	Node *rt = &tre[tot++] ;
	*rt = *ort ; ++rt->sum ;

	if (x == y) return rt ;

	int mid = (x + y) >> 1 ;
	if (f <= mid) rt->ch[0] = add(rt->ch[0] , x , mid , f) ;
	else rt->ch[1] = add(rt->ch[1] , mid + 1 , y , f) ;

	return rt ;
}

int find(Node *r1 , Node *r2 , int x , int y , int k) {
	if (x == y) return x ;

	int mid = (x + y) >> 1 , r = r1->ch[1]->sum - r2->ch[1]->sum ;
	if (k <= r) return find(r1->ch[1] , r2->ch[1] , mid + 1 , y , k) ;
	else return find(r1->ch[0] , r2->ch[0] , x , mid , k - r) ;
}

int main() {
	scanf("%d %d %d %d" , &n , &m , &L , &R) ;
	for (int i = 1 ; i <= n ; ++i) scanf("%d" , &a[i]) ;

	s[0] = 0 ; sL = sR = 0 ;
	for (int i = 1 ; i <= n ; ++i) {
		s[i] = s[i - 1] + a[i] ;
		sL = std::min(sL , s[i]) ; sR = std::max(sR , s[i]) ;
	}

	///

	root[0] = &tre[tot++] ;
	root[0]->init() ; root[0]->ch[0] = root[0]->ch[1] = root[0] ;
	for (int i = 1 ; i <= n ; ++i) root[i] = add(root[i - 1] , sL , sR , s[i]) ;

	for (int i = 1 ; i <= n ; ++i) {
		int le = i + L - 1 , ri = i + R - 1 ;
		if (le > n) break ;

		kth[i] = 1 ; ri = std::min(ri , n) ;
		int a = find(root[ri] , root[le - 1] , sL , sR , kth[i]) ;

		pq.push((data){a - s[i - 1] , i}) ;
	}

	ll ans = 0 ;
	for (; m-- ;) {
		data tmp = pq.top() ; int p = tmp.pt ;
		ans += tmp.val ; ++kth[p] ;

		int le = p + L - 1 , ri = std::min(p + R - 1 , n) , len = ri - le + 1 ,
			a = kth[p] <= len ? find(root[ri] , root[le - 1] , sL , sR , kth[p]) : -INF ;

		pq.pop() ; pq.push((data){a - s[p - 1] , p}) ;
	}

	printf("%lld\n" , ans) ;

	return 0 ;
}