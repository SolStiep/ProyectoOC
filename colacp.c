#include "colacp.h"
#include <stdlib.h>
#include "constantes.h"

TColaCP crear_cola_cp(int (*f)(TEntrada,TEntrada)){
    TColaCP cola;
    cola=(TColaCP)malloc(sizeof(struct cola_con_prioridad));
    cola->cantidad_elementos=0;
    cola->raiz=NULL;
    cola->f=f;
    return cola;
}


int cp_insertar(TColaCP cola,TEntrada entr){
    int posicion,i;
    TNodo padreNuevo;
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        TNodo nuevoNodo=(TNodo)malloc(sizeof(struct nodo));
        nuevoNodo->entrada=entr;
        if(cola->cantidad_elementos==0){
            nuevoNodo->padre=NULL;
            nuevoNodo->hijo_derecho=NULL;
            nuevoNodo->hijo_izquierdo=NULL;
            cola->raiz=nuevoNodo;
        }
        else{
            padreNuevo=buscar_nodo_insertar(cola);
            nuevoNodo->padre=padreNuevo;
            if(cola->cantidad_elementos%2!=0){
                padreNuevo->hijo_derecho=nuevoNodo;
            }
            else{
                padreNuevo->hijo_izquierdo=nuevoNodo;
            }
            burbujeo(nuevoNodo);
        }
    }
}

private TNodo buscar_nodo_insertar(TColaCP cola){
    int posicionPadre;
    if(cola->cantidad_elementos%2==0){
        posicionPadre=(cola->cantidad_elementos%2)%2;
    }
    else{
        posicionPadre=((cola->cantidad_elementos%2)+1)%2;
    }
    return buscarPadre(cola,posicionPadre);
}

private TNodo buscarPadre(TColaCP cola,int posicionPadre){
    int aux=1;
    while(aux)
}
TEntrada cp_eliminar(TColaCP cola){

}

int cp_size(TColaCP cola){
    return cola->cantidad_elementos;
}

int cp_destruir(TColaCP cola){

}
