#include <iostream>
#include <map>
using namespace std;

int main(){
	int test;
	string arbol;
	map<string, unsigned long long> lista;
	unsigned long long n;

	cin >> test;
   cin.ignore();
   cin.ignore();
   cout.setf(ios::fixed);
   cout.precision(4);
   bool space = false;
	while ( test-- ){
		n = 0;
		lista.clear();
		if ( !space ){
			space = true;
		}else{
			cout << endl;
		}
		do {
			getline(cin,arbol,'\n');
			//cout << arbol << endl;
			if (arbol.size() > 0 && !cin.eof() ){
				n++;
				if ( lista.count(arbol) == 0 ){
					lista[arbol] = 0;
				}
				lista[arbol]++;
			}else{
				for (auto x : lista){
					cout << x.first << " " << ((double)x.second) /((double) n )* 100 << endl;
				}
				break;
			}
		}while( true );
	}
	return 0;
}
