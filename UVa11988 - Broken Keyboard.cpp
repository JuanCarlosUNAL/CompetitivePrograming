#include <iostream>
#include <list>
#include <sstream>
using namespace std;

bool normal = true;
list<string> text;

void poner(string a){
	if(! a.size() )
		return;
	if (normal){
		text.push_back(a);
	}else{
		text.push_front(a);
	}
	return;
}

int main(){
	char a;
	string aux = "",
			 line;
	text = list<string>();
	stringstream ss;
	while ( getline(cin,line) ){
		ss << line;
		while(ss >> a)
		{
			switch (a){
			case ']':
				poner(aux);
				aux = "";
				normal = true;
				break;
			case '[':
				poner(aux);
				aux = "";
				normal = false;
				break;
			default:
				aux += a;
				break;
			}
		}
		poner(aux);
		aux = "";
		for (string x : text)
			cout << x;
		cout << endl;
		ss.clear();
		text.clear();
	}
	return 0;
}
