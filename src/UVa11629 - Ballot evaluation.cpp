#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
using namespace std;

struct FLOAT {
	long long a;
	short b;
};

istream& operator >> (istream &in, FLOAT& f){
	in.ignore();
	string aux1;
	getline(in,aux1,'\n');
	stringstream ss;
	ss << aux1;
	ss >> f.a ;
	ss.ignore(1);
	ss >> f.b;
	return in;
}

ostream& operator << (ostream &out, FLOAT& f ){
	out << f.a << '.' << f.b;
	return out;
}

FLOAT& operator += (FLOAT& a, const FLOAT& b){
	a.a = a.a+b.a;
	a.b = a.b+b.b;
	if (a.b > 9){
		a.a += a.b /10;
		a.b %= 10;
	}
	return a;
}

bool operator < (FLOAT& a, long long& b){
	return a.a < b;
}
bool operator > (FLOAT& a, long long& b){
	if (a.a > b)
		return true;
	else if (a.a == b && a.b > 0)
		return true;
	else return false;
}
bool operator == (FLOAT& a, long long b){
	if (a.a == b && a.b == 0)
		return true;
	else return false;
}
bool operator <= (FLOAT& a, long long& b){
	return a < b || a==b;
}
bool operator >= (FLOAT& a, long long& b){
	return a > b || a==b;
}

int main(){
	int p,g;
	while(cin >> p >> g ){
		map <string, FLOAT>mp;
		string key;
		FLOAT val;
		while (p--){
			cin >> key >> val;
			mp[key] = val;
		}
		int i = 0;
		while (i++ < g){
			getline(cin,key,'\n');
			replace(key.begin(),key.end(),'+',' ');
			stringstream ss;
			ss << key;
			FLOAT sum = { 0 ,0};
			do{
				ss >> key;
				if (mp.count(key))
					sum += mp[key];
			}while(mp.count(key));
			long long res;
			ss >> res;
			//cout << sum << ' ' << key << ' ' << res << " ... ";
			bool ans;
			if (key == "="){
				ans = sum == res;
			}else if (key == "<"){
				ans = sum < res;
			}else if (key == "<="){
				ans = sum <= res;
			}else if (key == ">"){
				ans = sum > res;
			}else if (key == ">="){
				ans = sum >= res;
			}
			cout << "Guess #" << i <<" was ";
			if(ans){
				cout << "correct." << endl;
			}else{
				cout << "incorrect." << endl;
			}
		}
	}
	return 0;
}
