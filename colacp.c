#include "colacp.h"
#include <stdlib.h>
#include "ciudad.h"
#include <stdio.h>

typedef struct par{
    float x;
    float y;
}TPar;

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
                cola->cantidad_elementos=1;
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

   // printf("raiz=%i  hijoI= %p  hijoD=%p\n",cola->raiz->entrada->clave,cola->raiz->hijo_izquierdo,cola->raiz->hijo_derecho);
    return retorno;
}


TNodo buscar_nodo(TColaCP cola,int cant){
    TNodo retorno, siguiente;
    if(cant==1){
        retorno= cola->raiz;
    }
    else{
        retorno=buscar_nodo(cola,cant/2);

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
    while((nodoAcomodar!=cola->raiz)&&(cola->f(nodoAcomodar->entrada,nodoAcomodar->padre->entrada))==1){
        intercambiar(nodoAcomodar,nodoAcomodar->padre);
        nodoAcomodar=nodoAcomodar->padre;
    }
}

void intercambiar(TNodo hijo,TNodo padre){
    TEntrada auxHijo=hijo->entrada;
    hijo->entrada=padre->entrada;
    padre->entrada=auxHijo;
}


TEntrada cp_eliminar(TColaCP cola){
    TEntrada eliminar=NULL;
    TNodo nuevaRaiz;
    if(cola==NULL){
        exit(CCP_NO_INI);
    }
    else{
        if(cola->cantidad_elementos!=0){
            if(cola->cantidad_elementos==1){
                eliminar=cola->raiz->entrada;
                free(cola->raiz);
                cola->raiz=NULL;
                cola->cantidad_elementos=0;
            }
            else{
                 nuevaRaiz=buscar_nodo(cola,cola->cantidad_elementos);
                eliminar=cola->raiz->entrada;

                cola->raiz->entrada = nuevaRaiz->entrada;

                if(nuevaRaiz->padre->hijo_derecho==nuevaRaiz){
                    nuevaRaiz->padre->hijo_derecho=NULL;
                }
                else{
                    nuevaRaiz->padre->hijo_izquierdo=NULL;
                }
                nuevaRaiz->entrada=NULL;
                free(nuevaRaiz);

                cola->cantidad_elementos=cola->cantidad_elementos-1;
                acomodar(cola);
            }
        }
    }
    return eliminar;
}


void acomodar(TColaCP cola){
    TNodo mayor , r=cola->raiz,HI=r->hijo_izquierdo , HD=r->hijo_derecho;

    while(HD!=NULL&&HI!=NULL){
        if(cola->f(HI->entrada,HD->entrada)==1){
            mayor=HI;
        }
        else{
            mayor=HD;
        }

        if(cola->f(r->entrada , mayor->entrada) == -1){
            intercambiar(mayor,r);
            r=mayor;
            HD=r->hijo_derecho;
            HI=r->hijo_izquierdo;
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
        if(cola->raiz!=NULL){
            cp_destruirAux(cola->raiz);
        }
        free(cola);
        cola = NULL;
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

void pre(TColaCP cola , TNodo raiz);


void mostrar_Cola(TColaCP cola){
    pre(cola , cola->raiz);
}

void pre(TColaCP cola , TNodo raiz){
    TCiudad city = (TCiudad) raiz->entrada->valor;
    printf("city: %s \n" , city->nombre);
    TPar *p=(TPar *)raiz->entrada->clave;
    printf("par x: %f  ",p->x);
    printf("par y: %f\n",p->y);

    if(raiz->hijo_izquierdo != NULL)
        pre(cola,raiz->hijo_izquierdo);
    if(raiz->hijo_derecho != NULL)
        pre(cola , raiz->hijo_derecho);
}

