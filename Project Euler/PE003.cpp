#include <bits/stdc++.h>

#define ll long long

ll N = 600851475143 ;

int main() {
	ll res = 0 ;
	for (ll i = 2 ; i * i <= N ; ++i)
		for (; !(N % i) ; N /= i , res = i) ;

	printf("%lld\n" , std::max(res , N)) ;

	return 0 ;
}