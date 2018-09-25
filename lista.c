#include "lista.h"
#include <stdlib.h>

TLista crear_lista(){
    TLista L = POS_NULA;
    return L;
}

int l_insertar(TLista *lista , TPosicion pos ,TElemento elem){
    TPosicion celda = (TPosicion) malloc(sizeof(struct celda));
    celda->elemento = elem;
    celda->celda_anterior = POS_NULA;
    celda->celda_siguiente = POS_NULA;

    if(celda == NULL) //si se me lleno la heap
        return FALSE;

    if (*lista == POS_NULA){ //estamos insertando el primer elemento
        *lista = celda;
    }
    else{
        if (*lista == pos){ //estamos insertando en la primer posicion (por lo tanto hace falta que ahora lista apunte a celda)
            pos->celda_anterior = celda;
            *lista = celda;
        }
        else{
            if (pos->celda_anterior!=POS_NULA){
                pos->celda_anterior->celda_siguiente = celda;
                celda->celda_anterior = pos->celda_anterior;
            }
            pos->celda_anterior = celda;
            celda->celda_siguiente = pos;

        }

    }

    return TRUE;
}

int l_eliminar(TLista *lista , TPosicion pos){
    if (*lista == POS_NULA || pos == POS_NULA) //en caso de que la lista este vacia o la pos sea invalida
        return FALSE;

    if(*lista == pos){ //en caso de haber eliminado el primer elemento
        *lista = pos->celda_siguiente;
        pos->celda_siguiente->celda_anterior = POS_NULA;
        pos->celda_siguiente = POS_NULA; //hace falta?
    }
    else{  //en caso de haber eliminado un elemento intermedio o el ultimo.

        if(pos->celda_anterior != POS_NULA){ //no habria que chequear esta condicion, no? ya que si da falso quiere decir que era el primer elemento
            pos->celda_anterior->celda_siguiente = pos->celda_siguiente;
        }
        if(pos->celda_siguiente != POS_NULA){
            pos->celda_siguiente->celda_anterior = pos->celda_anterior;
        }

        pos->celda_anterior = POS_NULA; //hace falta?
        pos->celda_siguiente = POS_NULA; //hace falta?
    }

    free(pos);
    pos = POS_NULA; //asi el puntero no queda apuntando a la nada.

    return TRUE;
    }

TPosicion l_primera(TLista lista){
    return lista;
}

TPosicion l_ultima(TLista lista){
    TPosicion pos = lista;
    if (pos==POS_NULA)
        return pos;

    while(pos->celda_siguiente != POS_NULA){
        pos = pos->celda_siguiente;
    }
    return pos;
}

TPosicion l_anterior(TLista lista , TPosicion pos){
    return pos->celda_anterior;
}

TPosicion l_siguiente(TLista lista, TPosicion pos){
    return pos->celda_siguiente;
}

TElemento recuperar(TLista lista ,TPosicion pos){
    if(pos == POS_NULA)
        return ELE_NULO;

    return pos->elemento;

}

int l_size(TLista lista){
    int i=0;
    TPosicion pos = lista;
    while(pos!=POS_NULA){
        pos = pos->celda_siguiente;
        i++;
    }

    return i;
}

int l_destruir(TLista *lista){

    if (*lista == POS_NULA)
        return FALSE;

    TPosicion pos = *lista;
    while(pos!=POS_NULA){
        free(pos);
        pos = pos->celda_siguiente;
    }

    return TRUE;
}
