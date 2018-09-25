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

static void burbujeo(TColaCP cola,TNodo nodoAcomodar);

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
                padreNuevo=buscar_nodo_insertar(cola,cola->raiz);
                nuevoNodo->padre=padreNuevo;
                if(cola->cantidad_elementos%2!=0){
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

 static void burbujeo(TColaCP cola,TNodo nodoAcomodar){
    TNodo hijoIzquierdoPadre,hijoDerechoPadre,padrePadre,hijoDerechoAcomodar,hijoIzquierdoAcomodar,padreAcomodar,padre;
    while((cola->f(nodoAcomodar->entrada,nodoAcomodar->padre->entrada))==1){
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

static TNodo ultimoNodo(TNodo r);
static void acomodar(TColaCP cola,TNodo r);

TEntrada cp_eliminar(TColaCP cola){
    TEntrada eliminar=ELE_NULO;
    TNodo nuevaRaiz;
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        if(cola->cantidad_elementos!=0){
            nuevaRaiz=ultimoNodo(cola->raiz);
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
    return eliminar;
}

static TNodo ultimoNodo(TNodo r){
    TNodo retorno=NULL;
    if(r->hijo_derecho==NULL&&r->hijo_izquierdo==NULL){
        retorno=r;
    }
    else{
        if(r->hijo_izquierdo!=NULL)
            ultimoNodo(r->hijo_izquierdo);
        if(r->hijo_derecho!=NULL)
            ultimoNodo(r->hijo_derecho);
    }
    return retorno;
}

static void intercambiar(TNodo hijo,TNodo padre);

static void acomodar(TColaCP cola,TNodo r){
    intercambiar(r,r); // no sirve de nada, puesto para que no tire ningun warning
}

static void intercambiar(TNodo hijo,TNodo padre){
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


static void cp_destruirAux(TNodo r);
//No hay caso en el que pueda fallar por eso retorna siempre true
int cp_destruir(TColaCP cola){
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        cp_destruirAux(cola->raiz);
    }
    return TRUE;
}

static void cp_destruirAux(TNodo r){
    if(r->hijo_izquierdo!=ELE_NULO){
        cp_destruirAux(r->hijo_izquierdo);
    }
    if(r->hijo_derecho!=ELE_NULO){
        cp_destruirAux(r->hijo_derecho);
    }
    free(r);
}
