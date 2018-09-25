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

    if(celda == NULL)
        return FALSE;

    if (*lista == POS_NULA){
        *lista = celda;
    }
    else{

    }


}

