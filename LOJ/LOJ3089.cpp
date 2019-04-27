#include <queue>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#define db double
#define DEBUG printf("Passing [%s] in Line %d\n" , __FUNCTION__ , __LINE__) ;

const db eps = 1e-5 ;
const int MAX_N = 1500 + 10 ;

struct data {int x , y ;}pre[MAX_N][MAX_N] ;
struct Node {
    int cnt ; db val ;
    Node *ch[10] , *fail ;

    void init() {
        val = 0 ; fail = NULL ;
        for (int i = 0 ; i < 10 ; ++i) ch[i] = NULL ;
    }
}tre[MAX_N] ;

std::queue<Node*> qtre ;

Node *root ;
db f[MAX_N][MAX_N] ;
bool ap[MAX_N][MAX_N] ;
int n , m , tot , tr[MAX_N][10] ;
char s[MAX_N] , ts[MAX_N] , ch[MAX_N][MAX_N] ;

void add(char *s , db v) {
    Node *rt = root ;
    int len = strlen(s) ;

    for (int i = 0 ; i < len ; ++i) {
        int c = s[i] - '0' ;
        if (!rt->ch[c]) (rt->ch[c] = &tre[tot++])->init() ;

        rt = rt->ch[c] ;
    }

    rt->val += v ; ++rt->cnt ;
}

void build() {
    qtre.push(root) ;

    for (; !qtre.empty() ;) {
        Node *x = qtre.front() ; qtre.pop() ;
        if (x->fail) x->val += x->fail->val , x->cnt += x->fail->cnt ;

        for (int c = 0 ; c < 10 ; ++c) {
            Node *nx = x->ch[c] , *p = x->fail ;
            if (!nx) continue ;

            for (; p && !p->ch[c] ; p = p->fail) ;
            if (!p) nx->fail = root ;
            else nx->fail = p->ch[c] ;

            qtre.push(nx) ;
        }
    }
}

int trans(int x , int c) {
    Node *p = &tre[x] ;
    for (; p && !p->ch[c] ; p = p->fail) ;

    if (!p) return 0 ;
    else return p->ch[c] - root ;
}

void dealwith(int x , int y , int c , db k) {
    int tl = x + 1 , tp = tr[y][c] ;
    db res = f[x][y] + tre[tp].val - k * tre[tp].cnt ;

    if (!ap[tl][tp]) {
    	f[tl][tp] = res ; ap[tl][tp] = 1 ;
        ch[tl][tp] = c + '0' ; pre[tl][tp] = (data){x , y} ;
    }
    else if (res - f[tl][tp] > eps) {
        f[tl][tp] = res ;
        ch[tl][tp] = c + '0' ; pre[tl][tp] = (data){x , y} ;
    }
}

bool check(db k) {
    f[0][0] = 0 ; ap[0][0] = 1 ;

    for (int i = 0 ; i < n ; ++i)
    	for (int j = 0 ; j < tot ; ++j) {
    		if (!ap[i][j]) continue ;
    		ap[i][j] = 0 ;

    		if (s[i + 1] != '.') dealwith(i , j , s[i + 1] - '0' , k) ;
    		else for (int p = 0 ; p < 10 ; ++p) dealwith(i , j , p , k) ;
    	}
    for (int i = 0 ; i < tot ; ++i) ap[n][i] = 0 ;

    for (int i = 0 ; i < tot ; ++i) if (f[n][i] > eps) return 1 ;
    return 0 ;
}

void print(data pt) {
    if (!pt.x) return ;

    print(pre[pt.x][pt.y]) ;
    putchar(ch[pt.x][pt.y]) ;
}

int main() {
    db L = -1 , R = 0 ;
    scanf("%d %d %s" , &n , &m , s) ;
    for (int i = n ; i ; --i) s[i] = s[i - 1] ;

    (root = &tre[tot++])->init() ;
    for (int i = 0 ; i < m ; ++i) {
        int a ;
        scanf("%s %d" , ts , &a) ;
        add(ts , log(a)) ; R = std::max(R , (db)log(a)) ;
    }

    ///

    build() ;
    for (int i = 0 ; i < tot ; ++i)
    	for (int j = 0 ; j < 10 ; ++j) tr[i][j] = trans(i , j) ;

    for (; R - L > eps ;) {
        db mid = (L + R) / 2 ;
        if (check(mid)) L = mid ;
        else R = mid ;
    }

    check(L) ;
    for (int i = 0 ; i < tot ; ++i)
        if (f[n][i] > eps) {print((data){n , i}) ; break ;}
    printf("\n") ;

    return 0 ;
}