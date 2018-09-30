#include "colacp.h"
#include <stdlib.h>
//estas son las declaraciones de las funciones privadas auxiliares
void intercambiar(TNodo hijo,TNodo padre);
void burbujeo(TColaCP cola,TNodo nodoAcomodar);
void acomodar(TColaCP cola);
TNodo buscar_nodo(TColaCP cola,int cant);
void cp_destruirAux(TNodo r);

TColaCP crear_cola_cp(int (*f)(TEntrada,TEntrada)){
    TColaCP cola;
    cola=(TColaCP)malloc(sizeof(struct cola_con_prioridad));
    cola->cantidad_elementos=0;
    cola->raiz=NULL;
    cola->f=f;
    return cola;
}


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
                cola->cantidad_elementos=cola->cantidad_elementos+1;
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


void burbujeo(TColaCP cola,TNodo nodoAcomodar){

    while((cola->f(nodoAcomodar->entrada,nodoAcomodar->padre->entrada))==1){
        intercambiar(nodoAcomodar,nodoAcomodar->padre);
    }
}

void intercambiar(TNodo hijo,TNodo padre){
    TEntrada auxHijo=hijo->entrada;
    hijo->entrada=padre->entrada;
    padre->entrada=auxHijo;
}


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
                cola->raiz=NULL;
                cola->cantidad_elementos=0;
            }
            else{
                nuevaRaiz=buscar_nodo(cola,cola->cantidad_elementos);
                eliminar=cola->raiz->entrada;

                nuevaRaiz->padre=NULL;
                nuevaRaiz->hijo_derecho=cola->raiz->hijo_derecho;
                nuevaRaiz->hijo_izquierdo=cola->raiz->hijo_izquierdo;

                cola->raiz->entrada = NULL;
                cola->raiz->hijo_derecho = NULL;
                cola->raiz->hijo_izquierdo = NULL;
                free(cola->raiz);

                cola->raiz=nuevaRaiz;
                cola->cantidad_elementos=cola->cantidad_elementos-1;
                acomodar(cola);
            }
        }
    }
    return eliminar;
}


void acomodar(TColaCP cola){
    TNodo mayor , r=cola->raiz , HI=r->hijo_izquierdo , HD=r->hijo_derecho;

    while(HD!=NULL&&HI!=NULL){
        if(cola->f(HI->entrada,HD->entrada)==1){
            mayor=HI;
        }
        else{
            mayor=HD;
        }

        if(cola->f(r->entrada , mayor->entrada) == -1){
            intercambiar(mayor,r);
        }
        else{
            break;
        }

    }

    if(HI!=NULL){
        if(cola->f(r->entrada , HI->entrada) == -1)
        intercambiar(HI,r);
    }
    if(HD!=NULL){
        if(cola->f(r->entrada , HD->entrada) == -1)
        intercambiar(HD,r);
    }
}


int cp_size(TColaCP cola){
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    return cola->cantidad_elementos;
}


int cp_destruir(TColaCP cola){
    if(cola==NULL){
        return FALSE;
    }
    else{
        cp_destruirAux(cola->raiz);
        free(cola);
    }
    return TRUE;
}

void cp_destruirAux(TNodo r){
    if(r->hijo_izquierdo!=NULL){
        cp_destruirAux(r->hijo_izquierdo);
    }
    if(r->hijo_derecho!=NULL){
        cp_destruirAux(r->hijo_derecho);
    }
    r->entrada = NULL;
    r->hijo_derecho = NULL;
    r->hijo_izquierdo = NULL;
    r->padre = NULL;
    free(r);
}
