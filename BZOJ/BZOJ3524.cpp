#include <stdio.h>
#include <stdlib.h>

#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const int MAX_N = 5e5 + 10 , lgN = 20 + 5 ;

struct Node {
	int num ;
	Node *ch[2] ;
}tre[MAX_N * lgN] ;

int n , m , cur ;
Node *root[MAX_N] ;

void modify(Node *ort , Node *&rt , int x , int y , int f) {
	if (y < f || f < x) return ;

	rt = &tre[cur++] ;
	*rt = *ort ; ++rt->num ;
	if (x == y) return ;

	int mid = (x + y) >> 1 ;
	modify(ort->ch[0] , rt->ch[0] , x , mid , f) ;
	modify(ort->ch[1] , rt->ch[1] , mid + 1 , y , f) ;
}

int find(Node *r1 , Node *r2 , int x , int y , int k) {
	if (x == y) return x ;

	int mid = (x + y) >> 1 ;
	if (r1->ch[0]->num - r2->ch[0]->num >= k) return find(r1->ch[0] , r2->ch[0] , x , mid , k) ;
	else if (r1->ch[1]->num - r2->ch[1]->num >= k) return find(r1->ch[1] , r2->ch[1] , mid + 1 , y , k) ;
	else return 0 ;
}

int main() {
	scanf("%d %d" , &n , &m) ;
	(root[0] = &tre[cur++])->num = 0 ;
	root[0]->ch[0] = root[0]->ch[1] = root[0] ;

	for (int i = 1 ; i <= n ; ++i) {
		int a ; scanf("%d" , &a) ;
		modify(root[i - 1] , root[i] , 1 , n , a) ;
	}

	///

	for (; m-- ;) {
		int x , y , len , k ;
		scanf("%d %d" , &x , &y) ;
		len = y - x + 1 ; k = len / 2 + 1 ;

		printf("%d\n" , find(root[y] , root[x - 1] , 1 , n , k)) ;
	}

	return 0 ;
}