#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

char *set;

void make_sets(){
	delete set;
	set = new char[26];
	for (int i = 0; i < 26; i++) set[ i ] = i;
}

void union_set(char a, char b){
	set[b] = a;
}

char find_set (const char i) {
	char aux = i;
	while (set[aux] != aux) {
		aux = set[aux];
	};
	set[i] = aux;
	return aux;
}

bool same_set(char a, char b){
	return find_set(a) == find_set(b);
}

void make_link(vector<vector<short>> &g, short a, short b){
	g[a].push_back(b);
	g[b].push_back(a);
}

int main()
{
	int slept_areas, connections;
	while ( cin >> slept_areas >> connections )
	{
		make_sets();
		char a, b, initial_areas[3];
		cin >> initial_areas[0] >> initial_areas[1] >> initial_areas[2];

		//read induced areas
		initial_areas[0] -= 'A';
		for(int i = 1; i < 3; i++){
			initial_areas[i] -= 'A';
			union_set(initial_areas[0],initial_areas[i]);
		}

		//read connections
		vector<vector<short>> brain(26);
		for(int i = 0; i < connections; i ++){
			cin >> a >> b;
			a -= 'A';
			b -= 'A';
			make_link(brain, a, b);
		}

		//extreme cases
		if(slept_areas <= 3){
			cout << "WAKE UP IN, 0, YEARS" << endl;
			continue;
		}else if (connections == 0){
			cout << "THIS BRAIN NEVER WAKES UP" << endl;
			continue;
		}

		int years = 0,
			 wake_up_iteration,
			 total_wake_up = 3;
		list<short> waiting;
		while(true){
			wake_up_iteration = 0;
			for(short i= 0; i < 26; i ++){ // for all neurons in the brain
				if( ! same_set(initial_areas[0], i) ) { //if i neuron is not wake up then count its connections
					int counter = 0;
					for( short j: brain[i] ) {//for each connection of i
						if ( same_set(initial_areas[0],j) ) counter++; // if j is wake up then counter up
						if (counter>=3){ // if i is connected with 3 or more neurons then add i to waiting list
							waiting.push_back(i);
							wake_up_iteration++;
						}
					}
				}
			}

			//wake up the neurons in the list
			for(int i = 0; i < wake_up_iteration; i++){
				union_set(initial_areas[0],waiting.back());
				waiting.pop_back();
			}

			total_wake_up += wake_up_iteration;
			if (wake_up_iteration <= 0){
				break;
			}
			years++;
		}

		if( slept_areas - total_wake_up <= 0 ){
			cout << "WAKE UP IN, "<<years<<", YEARS"<<endl;
		}else {
			cout << "THIS BRAIN NEVER WAKES UP" << endl;
		}

	}
	return 0;
}
