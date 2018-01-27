#include <cstdio>
#include <vector>
#include <cmath>

#define LEFT(n) (n * 2 + 1)
#define RIGHT(n) (n * 2 + 2)

using namespace std;

struct NODO {
    int count, from, to;
};

void make_tree(NODO*, NODO*, int, int, int);
int query(NODO*, int, int, int, int, int);

int main(){
    int n, q, a, b;
    while(scanf("%i %i", &n, &q) && n){
        NODO list[n];                                  //Lista de Intervalos
        
        int val1, val2, first = 0, ind = 0;
        for(int i = 0; i < n; i++){                         //Leer la lista
            scanf("%i",&val1);
            
            if(i == 0)  val2 = val1;                        //Inicialización
            if(val2 != val1){                               // Detectar el fin del intervalo y almacenarlo

                NODO nodo;
                nodo.count = i - first;
                nodo.from = first;
                nodo.to = i;

                list[ind++] = nodo ;
                first = i;
                val2 = val1;
            }
        }
        NODO nodo;
        nodo.count = n - first;
        nodo.from = first;
        nodo.to = n;

        list[ind++] = nodo;              // Almacenar el ultimo nodo

        // Árbol de tamaño (2 ^ (ceil( log( len(list) ) ) + 1) ) - 1
        NODO tree[( (1 << (int)( ceil( log(ind) / log(2) ) + 1)) - 1 )];
        
        /**
         * Hacer el árbol y  guardaro en la variable tree de acuerdo a los valores de la lista
         * se organiza como un heap empezando en 0
         * y se almacena el punto de inicio, 0, y el punto final, el tamaño de la lista
         */
        make_tree(tree, list, 0, 0, ind );

        for(int i = 0; i < q; i++) {
            scanf("%i %i", &a, &b);
            printf("%i\n", query(tree, 0, 0, ind, a - 1, b));
        }
    }
    return 0;
}

/**
 * Construir el árbol recursivamente
 */
void make_tree(NODO *tree, NODO *list, int index, int l, int r){
    if(r-l == 1)
        tree[index] = list[l];
    else{
        int m = (l+r)/2;
        make_tree(tree, list, LEFT(index) , l, m);
        make_tree(tree, list, RIGHT(index), m, r);

        NODO n_l = tree[LEFT(index)];
        NODO n_r = tree[RIGHT(index)];

        NODO nodo;
        nodo.count = max(n_l.count, n_r.count);
        nodo.from = n_l.from;
        nodo.to = n_r.to;

        tree[index] = nodo;
    }
}

/**
 * Buscar en el intervalo
 */
int query(NODO *tree, int d, int from, int to, int a, int b){
    
    NODO &n = tree[d];
    if(b < n.from || a > n.to) {                    // Si la petición está por fuera de los limites
        return 0;
    }
    if(a <= n.from && b >= n.to) {                  // Si el nodo está dentro del intervalo pedido
        return n.count;
    }
    if(to - from == 1){                             // Si llego a un nodo hoja entonces hace el cálculo
        from = max(n.from, a);
        to = min(n.to, b);
        return to - from;                           // Devuelve unicamente la cantidad de números en el intervalo
    }

    // Si ninguno de los anteriores se cumple es por que el intervalo aun es grande 
    int m = (from + to) / 2;
    int l = query(tree, LEFT(d), from, m, a, b );
    int r = query(tree, RIGHT(d), m, to, a, b);

    return max(l, r);
}