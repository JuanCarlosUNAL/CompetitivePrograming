#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main(){
	int n,m;
	while (cin >> n >> m){
		int i = 0;
		map<int, vector<int> > arr ;
		while(i++ < n){
			int val ;
			cin >> val;
			if(arr.count(val) == 0){
				arr[val] = vector<int>();
			}
			arr[val].push_back(i);
		}
		int k,v;
		while(m--){
			cin >> k >> v;
			if(arr[v].size() >= k)
				cout << arr[v][k-1] << endl;
			else
				cout << 0 << endl;
		}
	}
	return 0;
}
