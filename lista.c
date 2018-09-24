#include "lista.h"
//no me deja incluir las constantes
#include <stdlib.h>

TLista crear_lista(){
    TLista L;
    L = (TLista) malloc(sizeof(struct celda));
    L->celda_anterior = NULL;
    L->celda_siguiente = NULL;
    L->elemento = NULL;
    return L;
}

int l_insertar(TLista *lista , TPosicion pos ,TElemento elem){

}

