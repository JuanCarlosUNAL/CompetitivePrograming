#include <iostream>
#include <queue>
/**Pendiente*/
using namespace std;

int main(){
	int cases,l,m;
	cin >> cases;
	queue<int> cola[2];
	while(cases--){
		cin >> l >> m;
		l*=100;
		int car;
		string bank;
		cola[0] = queue< int >();
		cola[1] = queue< int >();

		while (m--){
			cin >> car >> bank;
			if (bank == "left")
				cola[0].push( car );
			else
				cola[1].push( car );
		}
		int curr_bank = 0; //left
		int carga = l;
		int viajes = 0;
		while (!( cola[1].empty() and  cola[0].empty()) ){
			int next = cola[curr_bank].front();
			if( carga - next < 0 or cola[curr_bank].empty()){
				curr_bank = !curr_bank;
				carga = l;
				viajes ++;
			}else{
				carga-= next;
				cola[curr_bank].pop();
			}
		}
		cout << viajes+1 << endl;

	}
	return 0;
}
