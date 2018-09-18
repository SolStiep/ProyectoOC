#include "colacp.h"
#include <stdlib.h>
#include "constantes.h"

TColaCP crear_cola_cp(int (*f)(TEntrada,TEntrada)){
    //Inicializo la cola y reservo lugar en memoria
    TColaCP cola;
    //cola=(struct cola_con_prioridad * )malloc(sizeof(struct cola_con_prioridad));
    cola=(TColaCP)malloc(sizeof(struct cola_con_prioridad));
    cola->cantidad_elementos=0;
    cola->raiz=NULL;
    cola->f=f;
    return cola;
}


int cp_insertar(TColaCP cola,TEntrada entr){
    int posicion,i;
    TNodo nodo;
    //Compruebo que la cola este inicializada
    if(cola==NULL||entr=NULL){
        exit(CCP_NO_INI);
    }
    else{
        TNodo nuevoNodo=(struct TNodo *)malloc(sizeof(struct nodo));
        nuevoNodo->entrada=entr;
        // consigo el padre del nuevo nodo
        posicion=(cola->cantidad_elementos)/2;
        nodo=cola->raiz;
        if(posicion%2==0){
            for(i=0;i<posicion;i++){
                if(i%2!=0){
                    nodo=nodo.hijo_izquierdo;
                }
                else{

                }
            }
        }
    }
}

TEntrada cp_eliminar(TColaCP cola){

}

int cp_size(TColaCP cola){
    return cola->cantidad_elementos;
}

int cp_destruir(TColaCP cola){

}
