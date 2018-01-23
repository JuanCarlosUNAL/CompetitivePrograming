#include <iostream>
#include <algorithm>
#include <valarray>
using namespace std;

int main(){
	int test, curr =0;
	cin >> test;
	while (curr++ < test){
		int R,C,M,N;
		cin >> R>>C>>M>>N;
		valarray<int> zones(26);
		for(int i = 0; i < 26; i++)
			zones[i] = 0;

		for (int i = 0; i < R*C; i++){
			char letter;
			cin >> letter;
			zones[letter-'A'] += 1;
		}
		int maximun =  zones.max(),
			*pos = max_element(begin(zones),end(zones));

		int n_incidences = 0;
		while (maximun == *pos ){
			*pos = 0;
			pos = max_element(begin(zones),end(zones));
			n_incidences ++;
		}

		cout << "Case "<< curr << ": " << (n_incidences * maximun * M) + (zones.sum()*N) << endl;

	}
}
