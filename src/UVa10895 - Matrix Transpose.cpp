#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(){
	int rows, col;
	typedef pair<int,int> ii;
	typedef vector<ii> vii;
	while (cin >> rows >> col) {
		vector<vii> matris(col);
		for(int i = 0; i < rows; i++){
			int n; // numero de entradas en la fila i-esima distintas de 0
			cin >> n;
			int indices[n]; //indices
			for(int j = 0;j < n; j++){
				cin >> indices[j];
			}
			//Leer el contenido de los indices

			for(int ind: indices){
				int val;
				cin >> val;
				matris[ind-1].push_back( ii(i,val) );
			}
		}
		cout << col << " " << rows << endl;
		for( vii line: matris ){
			cout <<line.size() ;
			for( ii par : line ){
				cout <<" "<< par.first+1 ;
			}
			cout << endl;
			int t = false;
			for( ii par : line ){
				if (t++)
					cout << " " ;
				cout << par.second ;
			}
			cout << endl;
		}
	}
	return 0;
}
