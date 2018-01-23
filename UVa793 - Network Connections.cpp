#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int *g;

void make_sets(int l ){
	delete g;
	g = new int[l];
	for (int i = 0; i < l; g[i]= i++ );
}

int find_set(int i ){
	int aux = i;
	while ( g[i] != i ) i = g[i];
	g[aux] = i;
	return i;
}

bool are_disjoint(int a, int b){
	return find_set(a) != find_set(b);
}

void union_set(int a, int b){
	if ( are_disjoint(a,b) )
		g[ find_set(a) ] = b;
}

int main(){
	int cases,computers;
	cin >> cases ;
	bool first_space =  true;

	while(cases--){
		cin >> computers;
		make_sets( computers );
		string line;
		stringstream ss ;

		char c;
		int a, b, count_success=0, count_fail=0;

		cin.ignore();
		while ( true ) {
			getline(cin,line,'\n');
			if (line.size() < 3)
				break;

			ss.clear();
			ss << line;
			ss >> c >> a >> b;

			a--;
			b--;

			switch (c){
			case 'c':
				union_set(a,b);
			break;
			case 'q':
				if ( are_disjoint(a,b) ) count_fail ++;
				else count_success ++;
			break;
			}
		}

		if (!first_space) cout << endl;
		else first_space = false;

		cout  << count_success << ',' << count_fail << endl;

	}

	return 0;
}
