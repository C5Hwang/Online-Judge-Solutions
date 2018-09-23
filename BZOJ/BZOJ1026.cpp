#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

const int MAX_L = 15 ;

int len , num[MAX_L] ;
int a , b , f[MAX_L][MAX_L] , g[MAX_L][MAX_L] ;

int GetAns(int x) {
	len = 0 ;
	while (x > 0) {
		num[++len] = x % 10 ;
		x /= 10 ;
	}

	if (len <= 1) return x ;

	for (int i = 0 ; i < 10 ; ++i) f[1][i] = g[1][i] = 1 ;
	for (int i = 2 ; i <= len ; ++i)
		for (int j = 0 ; j < 10 ; ++j) {
			f[i][j] = g[i][j] = 0 ;
			for (int k = 0 ; k < 10 ; ++k) {
				if (abs(j - k) <= 1) continue ;
				f[i][j] += f[i - 1][k] ;

				if (num[i] != j || num[i - 1] < k) continue ;

				if (num[i - 1] == k) g[i][j] += g[i - 1][k] ;
				else g[i][j] += f[i - 1][k] ;
			}
		}

	int sum = g[len][num[len]] ;
	for (int i = 1 ; i < len ; ++i)
		for (int j = 1 ; j < 10 ; ++j) sum += f[i][j] ;
	for (int j = 1 ; j < num[len] ; ++j) sum += f[len][j] ;

	return sum ;
}

int main() {
	scanf("%d %d" , &a , &b) ;
	int s1 = GetAns(a - 1) , s2 = GetAns(b) ;

	printf("%d\n" , s2 - s1) ;

	return 0 ;
}
