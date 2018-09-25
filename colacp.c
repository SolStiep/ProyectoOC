#include "colacp.h"
#include <stdlib.h>


TColaCP crear_cola_cp(int (*f)(TEntrada,TEntrada)){
    TColaCP cola;
    cola=(TColaCP)malloc(sizeof(struct cola_con_prioridad));
    cola->cantidad_elementos=0;
    cola->raiz=NULL;
    cola->f=f;
    return cola;
}

static TNodo buscar_nodo_insertar(TColaCP cola,TNodo r);

static void burbujeo(TNodo nodoAcomodar);

int cp_insertar(TColaCP cola,TEntrada entr){
    TNodo padreNuevo;
    int retorno;
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        TNodo nuevoNodo=(TNodo)malloc(sizeof(struct nodo));
        if(nuevoNodo==NULL){
            retorno=FALSE;
        }
        else{
            retorno =TRUE;
        }
        nuevoNodo->entrada=entr;
        if(cola->cantidad_elementos==0){
            nuevoNodo->padre=NULL;
            nuevoNodo->hijo_derecho=NULL;
            nuevoNodo->hijo_izquierdo=NULL;
            cola->raiz=nuevoNodo;
        }
        else{
            padreNuevo=buscar_nodo_insertar(cola,cola->raiz);
            nuevoNodo->padre=padreNuevo;
            if(cola->cantidad_elementos%2!=0){
                padreNuevo->hijo_izquierdo=nuevoNodo;
            }
            else{
                padreNuevo->hijo_derecho=nuevoNodo;
            }
           burbujeo(nuevoNodo);
        }
    }
    return retorno;
}

 static TNodo buscar_nodo_insertar(TColaCP cola,TNodo r){
    TNodo retorno=NULL;
    if(r->hijo_derecho==NULL||r->hijo_izquierdo==NULL){
        retorno=r;
    }
    else{
        buscar_nodo_insertar(cola,r->hijo_derecho);
        buscar_nodo_insertar(cola,r->hijo_izquierdo);
    }
    return retorno;
}

/*
    hijoIzquierdoPadre : es el nuevo hijo izquierdo del padre del nodo a acomodar
    hijoDerechoPadre : es el nuevo hijo derecho del padre del nodo a acomodar
    hijoDerechoAcomodar : es el nuevo hijo derecho del nodo a acomodar
    hijoIzquierdoAcomodar : es el nuevo hijo izquierdo del nodo a acomodar
    padreAcomodar :  es el nuevo padre del nodo a acomdar
    padrePadre : es el nuevo padre del padre del nodo a acomodar(el mismo nodo a acomodar)
*/

 static void burbujeo(TNodo nodoAcomodar){
    TNodo hijoIzquierdoPadre,hijoDerechoPadre,padrePadre,hijoDerechoAcomodar,hijoIzquierdoAcomodar,padreAcomodar,padre;
    while( (nodoAcomodar->entrada,nodoAcomodar->padre->entrada==1)){ //aca habia una f despues del while
        padre=nodoAcomodar->padre;
        hijoDerechoPadre=nodoAcomodar->hijo_derecho;
        hijoIzquierdoPadre=nodoAcomodar->hijo_izquierdo;
        padrePadre=nodoAcomodar;
        if(padre->hijo_derecho==nodoAcomodar){
            hijoDerechoAcomodar=padre;
            hijoIzquierdoAcomodar=padre->hijo_izquierdo;
        }
        else{
            hijoDerechoAcomodar=padre->hijo_derecho;
            hijoIzquierdoAcomodar=padre;
        }
        padreAcomodar=padre->padre;
        nodoAcomodar->padre=padreAcomodar;
        nodoAcomodar->hijo_derecho=hijoDerechoAcomodar;
        nodoAcomodar->hijo_izquierdo=hijoIzquierdoAcomodar;
        padre->hijo_derecho=hijoDerechoPadre;
        padre->padre=padrePadre;
        padre->hijo_izquierdo=hijoIzquierdoPadre;
    }
}


TEntrada cp_eliminar(TColaCP cola){
    TEntrada eliminar=ELE_NULO;
    TNodo nuevaRaiz;
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        if(cola->cantidad_elementos!=0){
            nuevaRaiz=ultimoNodo(cola,cola->raiz);
            eliminar=cola->raiz->entrada;
            free(cola->raiz);
            acomodar(cola);
        }
    }
    return eliminar;
}

static TNodo ultimoNodo(TColaCP cola,TNodo r){
    TNodo retorno=NULL;
    if(r->hijo_derecho==NULL&&r->hijo_izquierdo==NULL){
        retorno=r;
    }
    else{
        if(r->hijo_derecho!=NULL)
            ultimoNodo(cola,r->hijo_derecho);
        if(r->hijo_izquierdo!=NULL)
            ultimoNodo(cola,r->hijo_izquierdo);
    }
    return retorno;
}


void acomodar(TColaCP cola){

}

int cp_size(TColaCP cola){
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    return cola->cantidad_elementos;
}

//No hay caso en el que pueda fallar por eso retorna siempre true
int cp_destruir(TColaCP cola){


}

