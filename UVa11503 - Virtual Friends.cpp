#include <iostream>
#include <map>
#include <set>

using namespace std;

string find_set( map<string,string> &m, const string a ){
	string aux = a;
	while (m[aux] != aux) aux = m[aux];
	m[a] = aux;
	return aux;
}

int main() {
	int test, connections;
	cin >> test;
	while (test--	){
		cin >> connections;
		string a,b;
		map<string, string> groups;
		map<string, int> counter;
		while(connections--){
			cin >> a >> b;
			map<string,string>::iterator
					ia = groups.find(a),
					ib = groups.find(b);
			int counter_to_show=0;
			if( ia != groups.end() && ib != groups.end() ) {// if a and b exist
				string p_a = find_set(groups,a),
						 p_b = find_set(groups,b);
				if (p_a != p_b){
					groups[p_b] = p_a;
					counter_to_show = (counter[p_a] += counter[p_b]);
				}else{
					counter_to_show = counter[p_a];
				}
			}else if(ia != groups.end()){ // if only a exist
				string p = find_set(groups, a);
				groups[b] = p;
				counter_to_show = ++counter[p];
			}else if (ib != groups.end()) { // if only b exist
				string p = find_set(groups, b);
				groups[a] = p;
				counter_to_show = ++counter[p];
			}else{ // if any exist
				groups[b] = a;
				groups[a] = a;
				counter_to_show = (counter[a] = 2);
			}

			//show the counter
			cout << counter_to_show <<endl;
		}
	}
}
