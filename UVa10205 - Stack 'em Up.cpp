#include <iostream>
#include <sstream>
#include <map>

using namespace std;

map<int,string> cartas;

void reset_cartas (void){
	cartas = map<int,string>();
	int i = 1;
	for (string x : { "Clubs", "Diamonds", "Hearts", "Spades" }){
		for (string y : { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" }){
			cartas[i++] = y + " of " + x;
		}
	}
}

int main(){
	string line ;
	int state = 0,
		 casos,
		 *combinaciones,
		 inicial[53],
		 pos,
		 n ;
	bool salto = false;
	while ( ! cin.eof() ){
		getline( cin, line,'\n' );
		stringstream ss;
		ss << line;

		switch(state)
		{
			case 0:
				ss >> casos ;
				reset_cartas();
				state = 1;
				break;
			case 1: /**Estado de blanco*/
				state = 2;
				break;
			case 2:
				if (casos <= 0)
					return 0;
				else
					casos--;

				for(int i = 1; i <= 52;  i++)
					inicial[i] = i;
				//for (int i: inicial) cout << i;

				ss >> n;

				combinaciones = new int[52*n];
				state = 3;
				pos = 0;
				break;
			case 3: /**Lee las combinaciones*/
				while ( pos < n*52 && ss >> combinaciones[pos]){
					pos++;
				}
				if (pos >= n*52){
					state = 4;
				}

				break;
			case 4:
				if ( isdigit(line[0] ) ){
					//print_cartas();
					int k;
					ss >> k;
					//cout << "--------------------------"<< k <<"-----------------------" << endl;
					k--;
					//cout << k << endl;
					//cout << "de " << 52*k << " hasta " << 52*(k+1) <<endl;
					int aux[53];
					for (int i = 1; i <=52; i ++){
						int destino = combinaciones[52*k + i -1 ];
						aux[i] = inicial[destino];
						//cout << i << ") "<< cartas[i] << " - " << destino << " pos " << 52*k + i<< endl;
					}
					//cout << endl;
					for (int i = 1; i <= 52; i ++){
						inicial[i] = aux[i] ;
					}
				}
				if (!isdigit(line[0] )|| cin.eof() ){
					for(int x : inicial){
						if (salto) cout << cartas[x] << endl;
						else salto = true;
					}
					state = 2;
					continue;
				}
				break;
			default:
				break;

		}
	}
	return 0;
}
