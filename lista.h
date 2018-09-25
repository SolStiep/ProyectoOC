#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "constantes.h"

typedef void* TElemento;


typedef struct celda{
    TElemento elemento;
    struct celda *celda_anterior;
    struct celda *celda_siguiente;
} * TLista, * TPosicion;


//procedimientos y funciones

TLista crear_lista();

int l_insertar(TLista *lista , TPosicion pos ,TElemento elem); //por qué un puntero a la lista?

int l_eliminar(TLista *lista , TPosicion pos);

TPosicion l_primera(TLista lista);  //porque antes pasabamos la lista como puntero y ahora no?

TPosicion l_ultima(TLista lista);

TPosicion l_anterior(TLista lista , TPosicion pos);

TPosicion l_siguiente(TLista lista , TPosicion pos);

TElemento l_recuperar(TLista lista , TPosicion pos);

int l_size(TLista lista);

int l_destruir(TLista *lista);




#endif // LISTA_H_INCLUDED
