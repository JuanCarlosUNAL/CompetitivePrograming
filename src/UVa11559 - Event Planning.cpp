#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

int main(){

    int participantes, presupuesto, hoteles, semanas;
    int precio;

    while ( cin >> participantes>> presupuesto>> hoteles>> semanas ){
        int costo = -1;
        int dias = -1;
        for(int i = 0; i < hoteles; i++){
            int precio_aux, cap_dia,sem_disponibles = 0,
					 max_dias = 0,
                aux =0;
            cin >> precio;
            max_dias = presupuesto/(precio*participantes);
            for (int j = 0; j < semanas;j++){ 		// da el numero de dias con habitaciones disponibles
                cin >> cap_dia;
                if (cap_dia >= participantes){
                	aux += 1;
                }else {
                	aux = 0;
                }
                if(aux > sem_disponibles){
						sem_disponibles = aux;
                }
            }

				if (sem_disponibles > 0 and max_dias > 0){
					int costo_aux = precio*participantes;
					if (costo > costo_aux or costo == -1){
						//cout << "posible en hotel "<<i << " dias: "<< 1 << " por: " << costo_aux <<endl;
						costo = costo_aux;
					}else{
						//cerr << "imposible en hotel "<<i << " dias: "<<1<< " por: " << costo_aux <<endl;
					}
				}
        }
        if (costo <= 0 ){
				cout << "stay home"<<endl;
        }else{
        		cout <<costo<<endl;
        }
    }
    return 0;
}
