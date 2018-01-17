#include <iostream>

using namespace std;

int main(){
    int len = 0, steps = 0,postarget = 0,posgrasshoper;
    string arreglo;
    cin >> len >> steps;
    bool saltamontes= false , objetivo = false;
    cin >> arreglo;
    for (int i = 0; i < len || !(saltamontes && objetivo) ; i++){
        if (arreglo[i] == 'T'){
            postarget = i;
            objetivo = true;
        }
        else if (arreglo[i] == 'G'){
            posgrasshoper = i;
            saltamontes = true;
        }
    }
    int right= posgrasshoper > postarget ? posgrasshoper: postarget,
        left = posgrasshoper < postarget ? posgrasshoper: postarget;

    bool posible = true;
    if( (postarget-posgrasshoper)%steps == 0) {
        while (right >= left){
            if (arreglo[right]== '#' || arreglo[left]== '#'){
                posible = false;
                break;
            }
            left += steps;
            right-= steps;
        }
    }else{
        posible = false;
    }

    if (posible){
        cout << "YES"<<endl;
    }else{
        cout << "NO"<<endl;
    }
}
