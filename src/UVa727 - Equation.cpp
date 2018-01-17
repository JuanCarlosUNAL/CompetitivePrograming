#include <iostream>
#include <string>
using namespace std;

string cadena;
int flag;

string init(void);
string initp(string);
string por(void);
string porp(string);
string caracter(void);

string init(){
	string t1 = por();
	string t2 = initp(t1);
	return t2;
}
string initp(string arg){

	if( flag >= 0 and cadena[flag] == '+'){
		flag-= 1;
		string t1 = init();
		return  t1 + arg + '+';
	}else if( flag >= 0 and cadena[flag] == '-'){
		flag-= 1;
		string t1 = init();
		return  t1 + arg + '-';
	}else{
		return arg;
	}
}
string por(){
	string t1 = caracter();
	string t2 = porp(t1);
	return t2;
}
string porp(string arg){
	if( flag >= 0 and cadena[flag] == '*'){
		flag--;
		string t1 = por();
		return t1 + arg + '*';
	}else if( flag >= 0 and cadena[flag] == '/'){
		flag--;
		string t1 = por();
		return t1 + arg + '/';
	}else{
		return arg;
	}
}
string caracter (){
	if(cadena[flag] == ')'){
		flag--;
		string t1 = init();
		flag--;
		return t1;
	}
	else if (isdigit(cadena[flag])){
		string t1 = {cadena[flag]};
		flag--;
		return t1;
	}else{
		return "";
	}
}

int main(){
	int cases;
	cin >> cases;
	cin.ignore();
	cin.ignore();

	cadena = "";
	char a;
	while ( cin.get(a) ){
		if (a == '\n'){
			flag = cadena.size()-1;
			cout << init()<< endl << endl;
			cadena = "";
		}else{
			cadena += a ;
			cin.ignore(1,'\n');
		}
	}
	flag = cadena.size()-1;
	cout << init() << endl ;

	return 0;
}
