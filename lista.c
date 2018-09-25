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
        if (pos->celda_anterior!=POS_NULA){
            pos->celda_anterior->celda_siguiente = celda;
            celda->celda_anterior = pos->celda_anterior;
        }
        pos->celda_anterior = celda;
        celda->celda_siguiente = pos;

    }

    return TRUE;

}

int l_eliminar(TLista *lista , TPosicion pos){
    if (*lista == POS_NULA || pos == POS_NULA)
        return FALSE;

    if(pos->celda_anterior != POS_NULA){
        pos->celda_anterior->celda_siguiente = pos->celda_siguiente;
    }
    if(pos->celda_siguiente != POS_NULA){
        pos->celda_siguiente->celda_anterior = pos->celda_anterior;
    }

    pos->celda_anterior = POS_NULA;
    pos->celda_siguiente = POS_NULA;

    free(pos);

    return TRUE;
    }

