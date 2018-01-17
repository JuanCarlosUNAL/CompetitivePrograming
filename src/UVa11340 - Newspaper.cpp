#include <iostream>
#include <sstream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

int main(){
	int cases,k ;
	cin >> cases;
	while (cases--){
		cin >> k;
		cin.ignore(5,'\n');
		map<char,double> cost;
		for(int i = 0; i < k ; i++){
			double value;
			char a;
			cin >> a >> value;
			cost[a] = value;
		}
		cin >> k;
		cin.ignore(1,'\n');
		string text;
		for (int i = 0; i < k; i++){
			string line;
			getline(cin,line,'\n');
			text += line + "\n";
		}
		double coincidences = 0;
		for (auto x : cost)
			coincidences += count(text.begin(),text.end(),x.first) * (x.second);

		printf("%.2f$\n",coincidences/100);
	}
	return 0;
}
