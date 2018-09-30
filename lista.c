#include "lista.h"
#include <stdlib.h>

TLista crear_lista(){
    TLista L = POS_NULA;
    return L;
}

int l_insertar(TLista *lista , TPosicion pos ,TElemento elem){
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    TPosicion celda = (TPosicion) malloc(sizeof(struct celda));
    celda->elemento = elem; //no debo hacer un malloc() para el elemento?
    celda->celda_anterior = POS_NULA;
    celda->celda_siguiente = POS_NULA;

    if(celda == NULL) //si se me lleno la heap
        return FALSE;

    if (*lista == POS_NULA){ //estamos insertando el primer elemento
        *lista = celda;
    }
    else{
        if (*lista == pos || pos==POS_NULA){ //estamos insertando en la primer posicion (por lo tanto hace falta que ahora lista apunte a celda)
            pos->celda_anterior = celda;
            *lista = celda;
        }
        else{ //estamos insertando en una pos intermedia o al final
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
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    if (*lista == POS_NULA || pos == POS_NULA) //en caso de que la lista este vacia o la pos sea invalida
        return FALSE;

    if(*lista == pos){ //en caso de haber eliminado el primer elemento
        *lista = pos->celda_siguiente;
        pos->celda_siguiente->celda_anterior = POS_NULA;
    }
    else{  //en caso de haber eliminado un elemento intermedio o el ultimo.

        if(pos->celda_anterior != POS_NULA){ //no habria que chequear esta condicion, no? ya que si da falso quiere decir que era el primer elemento
            pos->celda_anterior->celda_siguiente = pos->celda_siguiente;
        }
        if(pos->celda_siguiente != POS_NULA){
            pos->celda_siguiente->celda_anterior = pos->celda_anterior;
        }

    }
    pos->celda_anterior = POS_NULA;
    pos->celda_siguiente = POS_NULA;
    pos->elemento = ELE_NULO;
    free(pos);

    return TRUE;
}

TPosicion l_primera(TLista lista){
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    return lista;
}

TPosicion l_ultima(TLista lista){
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    TPosicion pos = lista;
    if (pos==POS_NULA)
        return pos;

    while(pos->celda_siguiente != POS_NULA){
        pos = pos->celda_siguiente;
    }
    return pos;
}

TPosicion l_anterior(TLista lista , TPosicion pos){
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    return pos->celda_anterior;
}

TPosicion l_siguiente(TLista lista, TPosicion pos){
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    return pos->celda_siguiente;
}

TElemento recuperar(TLista lista ,TPosicion pos){
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    if(pos == POS_NULA)
        return ELE_NULO;

    return pos->elemento;

}

int l_size(TLista lista){
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    int i=0;
    TPosicion pos = lista;
    while(pos!=POS_NULA){
        pos = pos->celda_siguiente;
        i++;
    }

    return i;
}

int l_destruir(TLista *lista){ //invalidar los atributos
    if (lista == POS_NULA)
        return FALSE;

    TPosicion pos = *lista;
    TPosicion sgte;
    while(pos!=POS_NULA){
        sgte = pos->celda_siguiente;
        pos->elemento = ELE_NULO;
        pos->celda_anterior = POS_NULA;
        pos->celda_siguiente = POS_NULA;
        free(pos);
        pos = sgte;
    }

    return TRUE;
}
