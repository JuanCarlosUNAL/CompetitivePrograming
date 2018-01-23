#include <iostream>
#include <queue>

using namespace std;

int main(){
	int N;
	priority_queue<long long> p;
	while(cin >> N){
		if (N <= 0){
			break;
		}
		p = priority_queue<long long>();
		for (long long x;N > 0;N--){
			cin >> x;
			p.push(-x);
		}

		long long costo = 0;
		while ( p.size() >= 2 ){
			long long a = p.top();
			p.pop();
			long long b = p.top();
			p.pop();

			costo += a + b;
			//cout << a << "+" << b << "=" << a+b << endl;
			p.push(a+b);
		}
		cout << -(costo) << endl;

	}
	return 0;
}
