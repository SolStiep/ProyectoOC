#ifndef COLACP_H_INCLUDED
#define COLACP_H_INCLUDED

typedef void *TClave;
typedef void *TValor;

typedef struct entrada{
    TClave clave;
    TValor valor;
}*TEntrada;

typedef struct nodo{
    TEntrada entrada;
    struct nodo* padre;
    struct nodo* hijo_izquierdo;
    struct nodo* hijo_derecho;
}*TNodo;

typedef struct cola_con_prioridad{
    unsigned int cantidad_elementos;
    TNodo raiz;
    int (*f)(TEntrada,TEntrada);
}* TColaCP;


#endif // COLACP_H_INCLUDED
