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

TNodo buscar_padre(TColaCP cola,int cant);
void burbujeo(TColaCP cola,TNodo nodoAcomodar);

int cp_insertar(TColaCP cola,TEntrada entr){
    TNodo padreNuevo;
    int retorno= TRUE;
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        TNodo nuevoNodo=(TNodo)malloc(sizeof(struct nodo));
        if(nuevoNodo==NULL){
            retorno=FALSE;
        }
        else{
            nuevoNodo->entrada=entr;
            if(cola->cantidad_elementos==0){
                nuevoNodo->padre=NULL;
                nuevoNodo->hijo_derecho=NULL;
                nuevoNodo->hijo_izquierdo=NULL;
                cola->raiz=nuevoNodo;
            }
            else{
                cola->cantidad_elementos=cola->cantidad_elementos+1;
                padreNuevo=buscar_padre(cola,cola->cantidad_elementos);
                nuevoNodo->padre=padreNuevo;
                if(padreNuevo->hijo_izquierdo==NULL){
                    padreNuevo->hijo_izquierdo=nuevoNodo;
                }
                else{
                    padreNuevo->hijo_derecho=nuevoNodo;
                }
                burbujeo(cola,nuevoNodo);
            }
        }
    }
    return retorno;
}


TNodo buscar_padre(TColaCP cola,int cant){
    TNodo retorno, siguiente;
    if(cant==1){
        retorno= cola->raiz;
    }
    else{
        retorno=buscar_padre(cola,cant/=2);
        if(cant%2==0){
            siguiente=retorno->hijo_izquierdo;
        }
        else{
            siguiente=retorno->hijo_derecho;
        }
        if(siguiente!=NULL){
            retorno=siguiente;
        }
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

 void burbujeo(TColaCP cola,TNodo nodoAcomodar){
    TNodo hijoIzquierdoPadre,hijoDerechoPadre,padrePadre,hijoDerechoAcomodar,hijoIzquierdoAcomodar,padreAcomodar,padre;
    while((cola->f(nodoAcomodar->entrada->clave,nodoAcomodar->padre->entrada->clave))==1){
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

TNodo ultimoNodo(TNodo r);
void acomodar(TColaCP cola,TNodo r);

TEntrada cp_eliminar(TColaCP cola){
    TEntrada eliminar=ELE_NULO;
    TNodo nuevaRaiz;
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        if(cola->cantidad_elementos!=0){
            if(cola->cantidad_elementos==1){
                free(cola->raiz);
                cola->cantidad_elementos=0;
            }
            else{
                nuevaRaiz=buscar_padre(cola,cola->cantidad_elementos);
                eliminar=cola->raiz->entrada;
                nuevaRaiz->padre=NULL;
                nuevaRaiz->hijo_derecho=cola->raiz->hijo_derecho;
                nuevaRaiz->hijo_izquierdo=cola->raiz->hijo_izquierdo;
                free(cola->raiz);
                cola->raiz=nuevaRaiz;
                cola->cantidad_elementos=cola->cantidad_elementos-1;
                acomodar(cola,nuevaRaiz);
            }
        }
    }
    return eliminar;
}


void intercambiar(TNodo hijo,TNodo padre);

void acomodar(TColaCP cola,TNodo r){
    intercambiar(r,r); // no sirve de nada, puesto para que no tire ningun warning
}

void intercambiar(TNodo hijo,TNodo padre){
    TNodo aux,hijoDAux,hijoIAux;
    if(padre->hijo_derecho==hijo){
        aux=padre->hijo_derecho;
        hijoDAux=aux->hijo_derecho;
        hijoIAux=aux->hijo_izquierdo;
        padre->hijo_derecho->padre=padre->padre;
        padre->hijo_derecho->hijo_derecho=padre;
        padre->hijo_derecho->hijo_izquierdo=padre->hijo_derecho;
        padre->hijo_izquierdo=hijoIAux;
        padre->hijo_derecho=hijoDAux;
    }
    else{
        aux=padre->hijo_izquierdo;
        hijoDAux=aux->hijo_derecho;
        hijoIAux=aux->hijo_izquierdo;
        padre->hijo_izquierdo->padre=padre->padre;
        padre->hijo_izquierdo->hijo_derecho=padre->hijo_derecho;
        padre->hijo_izquierdo->hijo_izquierdo=padre;
        padre->hijo_izquierdo=hijoIAux;
        padre->hijo_derecho=hijoDAux;
    }
    padre->padre=aux;
}

int cp_size(TColaCP cola){
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    return cola->cantidad_elementos;
}


void cp_destruirAux(TNodo r);

//No hay caso en el que pueda fallar por eso retorna siempre true
int cp_destruir(TColaCP cola){
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        cp_destruirAux(cola->raiz);
        free(cola);
    }
    return TRUE;
}

void cp_destruirAux(TNodo r){
    if(r->hijo_izquierdo!=ELE_NULO){
        cp_destruirAux(r->hijo_izquierdo);
    }
    if(r->hijo_derecho!=ELE_NULO){
        cp_destruirAux(r->hijo_derecho);
    }
    free(r);
}
