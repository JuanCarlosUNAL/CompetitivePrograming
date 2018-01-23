#include <iostream>

using namespace std;

unsigned long long contador ;

void merge(unsigned long long *numeros,const unsigned long long p, const unsigned long long q, const unsigned long long r){
	unsigned long long L[q - p + 2],
		  			 R[r-q+1];

	for(unsigned long long i = 0; i+p <= q; i++)
		L[i]= numeros[i+p];
	for(unsigned long long i = 0; i+q+1 <= r; i++)
		R[i]= numeros[i+q+1];

	L[q - p + 1] = ~0;
	R[r-q] = ~0;

	for(unsigned long long i = p, a = 0, b = 0; i < r+1 ;i++){
		if (L[a] < R[b] ){
			numeros[i] = L[a++];
		}else{
			contador += q - p + 1 - a;
			numeros[i] = R[b++];
		}
	}
}
void mergesort(unsigned long long *numeros,unsigned long long p, unsigned long long r){
	if(p < r){
		unsigned long long q = (p+r)/2;
		mergesort(numeros, p, q);
		mergesort(numeros, q+1, r);
		merge(numeros, p, q, r);
	}
}

int main(){
	unsigned long long cases;
	while(cin >> cases){

		unsigned long long numeros[cases];
		for(long long i = 0;i < cases;i++){
			cin >> numeros[i];
		}
		contador = 0;
		mergesort(numeros, 0, cases-1);
		cout << contador << endl;

	}
	return 0;
}
