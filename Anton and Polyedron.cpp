#include <iostream>
#include <map>

using namespace std;

int main(){
	int datos;
	cin >> datos;
	map<string,int> poliedros;

	poliedros["Tetrahedron"] = 4;
	poliedros["Cube"] = 6;
	poliedros["Octahedron"] =  8;
	poliedros["Dodecahedron"] = 12;
	poliedros["Icosahedron"] = 20;

	int sum = 0;
	string figure;
	while (datos--){
		cin >> figure;
		sum += poliedros[figure];
	}
	cout << sum;
	return 0;
}
