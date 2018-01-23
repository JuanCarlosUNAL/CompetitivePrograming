#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

bool inline not_is_alpha(char a){
	return !isalpha(a);
}
int main(){
	unsigned int cases, curr_case = 1;
	string line;
	cin >> cases;
	cin.ignore(10,'\n');
	while(cases--){
		getline(cin,line,'\n');
		auto fin = remove_if(line.begin(), line.end(), not_is_alpha );

		double len = (double)(fin-line.begin());

		// Es un cuadrado ?
		bool is_palindromo = fmod(sqrt(len),1) == 0;

		auto b = fin, a = line.begin();

		//reglas 1 y 3
		while(is_palindromo){
			if (a > b) break;
			if (*(a++) != *(--b) ){
				is_palindromo = false;
			}
		}

		//Reglas 2 y 4
		b = fin-1, a = line.begin();
		auto guia = line.begin();
		int rep = 0;
		while(is_palindromo){
			if (*a == *guia && *b == *guia && rep < (int)sqrt(len) ){
				a+= (int)sqrt(len);
				b-= (int)sqrt(len);
				if ( a >= fin ){
					rep++;
					a = line.begin()+rep;
					b = fin - 1 - rep;
				}
				guia++;
			}else{
				a-= (int)sqrt(len);
				b+= (int)sqrt(len);
				guia--;
				if (*a != *guia || *b != *guia){
					is_palindromo = false;
				}
				break;
			}

		}
		if(is_palindromo)
			cout <<"Case #" << curr_case++ <<":\n"<< (int)sqrt(len) << endl;
		else
			cout <<"Case #" << curr_case++ <<":\nNo magic :(" << endl;
	}
	return 0;
}
