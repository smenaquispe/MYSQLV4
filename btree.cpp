#include<iostream>
#include<algorithm>
using namespace std;

/*
implementacion de un b + tree
*/

class Nodo {
public:
    int * claves;
    Nodo ** punteros;

    // la cantidad de claves guardadas que hay en el nodo
    int cantidadClaves = 0;

    // solo para nodos hojas que apuntan al siguiente
    Nodo * sig;
    
    Nodo(int d) {
        claves = new int [d - 1];
        punteros = new Nodo * [d];

        for(int i = 0; i < d; i++) {
            punteros[i] = nullptr;
        }
    }

    ~Nodo() {
        delete claves;
        delete punteros;
    }

    // insertar clave
    void insertarClave(int clave) {
        claves[cantidadClaves++] = clave;
        cout<<clave<<endl;
        sort(claves, claves + cantidadClaves);
    }

    // imprimir claves del nodo
    void imprimirNodo() {
        for(int i = 0; i < cantidadClaves; i++) {
            cout<<claves[i]<<" ";
        }
        cout<<endl;
    }

    // retorna el nodo hijo
    Nodo * getHijo(int clave) {
        int i = 0;
        for(; i <= cantidadClaves; i++) {
            if(i == cantidadClaves) break;
            if(claves[i] > clave) break;
        }

        return punteros[i];
    }

};

class BTree {
public:
    int d;
    Nodo * cabeza;

    BTree(int d_) : d(d_) {
        cabeza = new Nodo(d);
    }

    ~BTree() {}

    void insertarClave(int clave) {
        
        // caso es la primera clave en insertar
        if(cabeza->cantidadClaves == 0) {
            cabeza->insertarClave(clave);
            return;
        }

        // caso esta lleno el nodo cabeza
        Nodo * temp = cabeza;
        Nodo * padre = nullptr;
        
        while (true)
        {
            int i = 0;
            while (i < d && temp->claves[i] < clave) {
                cout<<temp->claves[i]<<endl;
                i++;
            }

            cout<<"i:"<<i<<endl;
            cout<<clave<<endl;

            if (temp->punteros[i]) {
                padre = temp;
                temp = temp->punteros[i];
            } else {
                temp->insertarClave(clave);
                cout<<"c"<<clave<<endl;
                if (temp->cantidadClaves == d) {
                    cout<<"partir"<<endl;
                    partirNodo(temp, padre);
                }
                break;
            }
        }
    }

    void partirNodo(Nodo * nodo, Nodo * padre) {
        int posMediana = nodo->cantidadClaves / 2;
        int mediana = nodo->claves[posMediana];

        Nodo * nuevoNodo = new Nodo(d);
        nuevoNodo->cantidadClaves = nodo->cantidadClaves - posMediana - 1;

        int j = 0;
        // lenamos el lado derecho de la particion en un nuevo nodo
        for(int i = posMediana + 1; i < nodo->cantidadClaves; i++) {
            nuevoNodo->claves[j] = nodo->claves[i];
            j++;
        }

        j = 0;
        // llenamos los punteros del lado derecho en el nuevo nodo
        for(int i = posMediana + 1; i <= nodo->cantidadClaves; i++) {
            nuevoNodo->punteros[j] = nodo->punteros[i];
            j++;
        }

        nodo->cantidadClaves = posMediana;

        for (int i = nodo->cantidadClaves; i < d - 1; i++) {
            nodo->claves[i] = 0; // O podrías asignar un valor por defecto o eliminar la clave de la lista.
            nodo->punteros[i + 1] = nullptr;
        }


        if (padre) {
            int i = 0;
            while (i < padre->cantidadClaves && padre->claves[i] < mediana) {
                i++;
            }

            for (int j = padre->cantidadClaves; j > i; j--) {
                padre->claves[j] = padre->claves[j - 1];
            }

            for (int j = padre->cantidadClaves + 1; j > i + 1; j--) {
                padre->punteros[j] = padre->punteros[j - 1];
            }

            padre->claves[i] = mediana;
            padre->punteros[i + 1] = nuevoNodo;
            padre->cantidadClaves++;

            if (padre->cantidadClaves == d) {
                partirNodo(padre, nullptr);
            }
        } else {
            Nodo* nueva_cabeza = new Nodo(d);
            nueva_cabeza->claves[0] = mediana;
            nueva_cabeza->punteros[0] = cabeza;
            nueva_cabeza->punteros[1] = nuevoNodo;
            nueva_cabeza->cantidadClaves = 1;

            cabeza = nueva_cabeza;
        }
    }

    void imprimir(Nodo * nodo) {
        if(nodo) {
            nodo->imprimirNodo();
            cout<<"Nodo: ";
            for(int i = 0; i <= nodo->cantidadClaves; i++) {
                imprimir(nodo->punteros[i]);
            }
        }
    }

    void imprimir() {
        imprimir(cabeza);
    }
};

int main() {

    BTree arbol(4);

    arbol.insertarClave(5);
    arbol.insertarClave(9);
    arbol.insertarClave(1);

    arbol.insertarClave(8);

    arbol.insertarClave(10);
    arbol.insertarClave(11);

    arbol.insertarClave(13);
  
    arbol.imprimir();

    return 0;
}