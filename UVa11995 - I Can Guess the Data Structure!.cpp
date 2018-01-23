#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main(){
	int n,a,b;
	while (cin >> n){
		bool isStack ,isQueue, isHeap;
		isStack = isQueue = isHeap = true;

		stack<int> pila;
		priority_queue<int> monticulo;
		queue<int> cola;

		for ( unsigned int elem = 0;n > 0;n-- ){
			cin >> a >> b;
			if(a == 1){
				elem ++;
				if(isStack){
					pila.push(b);
				}
				if(isHeap){
					monticulo.push(b);
				}
				if(isQueue){
					cola.push(b);
				}
			}else{
				if ( isStack && ( !elem || b != pila.top()) ){
					isStack = false;
				}else if(isStack){
					pila.pop();
				}

				if ( isHeap && ( !elem || b != monticulo.top())){
					isHeap = false;
				}else if(isHeap){
					monticulo.pop();
				}

				if ( isQueue && (!elem || b != cola.front())){
					isQueue = false;
				}else if(isQueue){
					cola.pop();
				}
				elem -= elem>0?1:0;
			}
		}

		if ( isHeap and !isQueue and !isStack ){
			cout << "priority queue" ;
		}else if ( !isHeap and isQueue and !isStack ){
			cout << "queue";
		}else if ( !isHeap and !isQueue and isStack ){
			cout << "stack" ;
		}else if ( !isHeap and !isQueue and !isStack ){
			cout << "impossible" ;
		}else{
			cout << "not sure" ;
		}
		cout << endl;


	}

	return 0;
}
