#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int cases;
	double x,y;
	cin >> cases;
	char ficha;

	while (cases--){
		cin >> ficha >> x >> y;
		switch(ficha){
		case 'r':
			cout << (x>y?y:x);
			break;
		case 'k':
			cout << ceil((x*y)/2) ;
			break;
		case 'Q':
			cout << (x<y?x:y);
			break;
		case 'K':
			cout << ceil(x/2.0) * ceil(y/2);
			break;
		}
		cout << endl;
	}

	return 0;
}
