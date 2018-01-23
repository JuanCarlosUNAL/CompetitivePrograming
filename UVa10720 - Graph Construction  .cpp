#include <iostream>
#include <algorithm>
#include <valarray>
using namespace std;

/**
 * Basado en el teorema de Erdos-Gallai
 */
int main(){
	int n;
	cin >> n;
	while (n){
		valarray<int> degree(n);
		int index = 0;
		int sum = 0;
		while(index < n){
			cin >> degree[index++];
			sum += degree[index-1];
		}
		bool possible = !(sum&1);
		degree = -degree;
		sort( begin(degree), end(degree) );
		degree = -degree;
		if ( possible ){
			int sum_left, sum_rigth ;

			for(int k = 1; k <= n && possible ; k++){
				sum_left = 0;
				sum_rigth = k*(k-1);
				int i = 0;
				while (i < k){
					sum_left += degree[i];
					i++;
				}
				while(i < n){
					sum_rigth += k<degree[i]?k:degree[i];
					i++;
				}
				possible = sum_left <= sum_rigth;
			}
		}
		if (possible)
			cout << "Possible" << endl;
		else
			cout << "Not possible" << endl;
		cin >> n;
	}
	return 0;
}
