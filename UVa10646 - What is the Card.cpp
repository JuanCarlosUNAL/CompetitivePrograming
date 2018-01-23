#include <iostream>
#include <sstream>

/**
1
7C 8C 5S 8D AC JC 3S 2D 3D 6S AS 7S 9D 5H 8S JS 2C QS 3H KS QC 2S JD 6C 5D 2H AD 7H JH 9C TD 6D 6H KH 9H 4D QH 7D TC KC AH QD 9S TS 8H 3C TH 4S KD 5C 4H 4C
*/

using namespace std;

int main (){

	string cartas[52];
	int cases, caso_act = 1;
	cin >> cases;

	while ( cases-- ){
		// Lee las cartas
		for(int i =0; i < 52; i++){
			cin >> cartas[i];
		}

		int pos = 27,
			 Y = 0;

		for (int i = 3 ; i>0; i--){
			int val = 0;
			if ( isdigit( cartas[pos-1][0] ) ){
				stringstream ss ;
				ss << cartas[pos-1][0];
				ss >> val;
			}else{
				val = 10;
			}
			Y += val;
			pos -= (10 - val)+1;
		}

		//Coloca las cartas restantes que estan en la mano
		for(int i = 27; i<52; i++){
			cartas[pos++] = cartas[i];
		}

		cout << "Case " << caso_act << ": "<< cartas[Y-1] << endl;
		caso_act += 1;
	}
	return 0;
}
