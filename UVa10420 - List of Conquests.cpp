#include <iostream>
#include <sstream>
#include <map>
using namespace std;

int main(){
    int n ;
    string country;
    map<string,int> counter;
    cin >> n;
    for(string word; getline(cin,word,'\n') ;){
        stringstream ss;
        ss << word;
        getline(ss,country,' ');
        if ( counter.count(country) == 0 ){
            counter[country] = 0;
        }
        counter[country] += 1;
    }

    for (auto& pais: counter ){
        if (pais.first.size() > 0)
            cout << pais.first << " "<< pais.second<<endl;
    }

    return 0;
}
