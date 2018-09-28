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

TNodo buscar_nodo(TColaCP cola,int cant);
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
                padreNuevo=buscar_nodo(cola,cola->cantidad_elementos);
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


TNodo buscar_nodo(TColaCP cola,int cant){
    TNodo retorno, siguiente;
    if(cant==1){
        retorno= cola->raiz;
    }
    else{
        retorno=buscar_nodo(cola,cant/=2);
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


//podrían simplemente intercambiar las entradas?
 void burbujeo(TColaCP cola,TNodo nodoAcomodar){
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

void acomodar(TColaCP cola);

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
                cola->raiz=NULL; // preguntar sobre null
                cola->cantidad_elementos=0;
            }
            else{
                nuevaRaiz=buscar_nodo(cola,cola->cantidad_elementos);
                eliminar=cola->raiz->entrada;
                nuevaRaiz->padre=NULL;
                nuevaRaiz->hijo_derecho=cola->raiz->hijo_derecho;
                nuevaRaiz->hijo_izquierdo=cola->raiz->hijo_izquierdo;
                free(cola->raiz);
                cola->raiz=nuevaRaiz;
                cola->cantidad_elementos=cola->cantidad_elementos-1;
                acomodar(cola);
            }
        }
    }
    return eliminar;
}


void intercambiar(TNodo hijo,TNodo padre);

void acomodar(TColaCP cola){
    TNodo mayor,r=cola->raiz,HI=r->hijo_izquierdo,HD=r->hijo_derecho;
    while(HD!=NULL&&HI!=NULL){
        if(cola->f(HI->entrada,HD->entrada)==1){
            mayor=HI;
        }
        else{
            mayor=HD;
        }
        if(cola->f(r->entrada,mayor->entrada)==-1){
            intercambiar(mayor,r);
        }
    }
    if(HI!=NULL){
        intercambiar(HI,r);
    }
    if(HD!=NULL){
        intercambiar(HD,r);
    }
}

void intercambiar(TNodo hijo,TNodo padre){
    TEntrada auxHijo=hijo->entrada;
    hijo->entrada=padre->entrada;
    padre->entrada=auxHijo;

}

/*
void intercambiar(TNodo hijo,TNodo padre){
    TNodo aux,hijoDAux,hijoIAux;
    if(padre->hijo_derecho==hijo){
        aux=padre->hijo_derecho;
        hijoDAux=aux->hijo_derecho;
        hijoIAux=aux->hijo_izquierdo;
        padre->hijo_derecho->padre=padre->padre;
        padre->hijo_derecho->hijo_derecho->padre=padre;
        padre->hijo_derecho->hijo_izquierdo=padre->hijo_izquierdo;
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

*/

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
