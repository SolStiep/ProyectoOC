#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "colacp.h"

int funcion(TEntrada t1 , TEntrada t2){
    int retorno;
    int *c1=(int *)malloc(sizeof(int));
    int *c2=(int *)malloc(sizeof(int));
    c1=t1->clave;
    c2=t2->clave;
    int a =*c1;
    int b=*c2;
    if(a > b){
        retorno=1;
    }
    else{
        if(a==b){
            retorno=0;
        }
        else{
            retorno=-1;
        }
    }
    return retorno;
}


int main()
{

/*
    // ver si es asi insertar lista
    int *e1=(int *)malloc(sizeof(int));
    *e1=10;
    int *e2=(int *)malloc(sizeof(int));
    TLista L = crear_lista();
    l_insertar(&L,POS_NULA,e1);
    e2=l_primera(L)->elemento;
    printf("el primer elemento es: %i",*e2);


*/


/*
    // prueba cola

    int *c1=(int *)malloc(sizeof(int));
    int *c2=(int *)malloc(sizeof(int));
    int *c3=(int *)malloc(sizeof(int));
    int *c4=(int *)malloc(sizeof(int));
    int *v1=(int *)malloc(sizeof(int));
    int *v2=(int *)malloc(sizeof(int));
    int *eli=(int *)malloc(sizeof(int));
    *c1=5;
    *v1=1;
    *c2=40;
    *v2=2;
    *c3=45;
    *c4=10;
    TEntrada e1=(TEntrada)malloc((sizeof(struct entrada)));
    TEntrada e2=(TEntrada)malloc((sizeof(struct entrada)));
    TEntrada e3=(TEntrada)malloc((sizeof(struct entrada)));
    TEntrada e4=(TEntrada)malloc((sizeof(struct entrada)));
    TEntrada eliminar=(TEntrada)malloc((sizeof(struct entrada)));
    e1->clave=c1;
    e1->valor=v1;
    e2->clave=c2;
    e2->valor=v2;
    e3->clave=c3;
    e3->valor=v1;
    e4->clave=c4;
    e4->valor=v2;
    TColaCP cola=crear_cola_cp(funcion);
    cp_insertar(cola,e1);
    cp_insertar(cola,e2);
    cp_insertar(cola,e3);
    cp_insertar(cola,e4);
    eliminar=cp_eliminar(cola);
    eli=eliminar->clave;
    printf("tamaño: %i",cola->cantidad_elementos);
    printf("\nla clave de la entrada eliminada es: %i",*eli);
    printf("\n elimino otra: ");
    eliminar=cp_eliminar(cola);
    eli=eliminar->clave;
    printf("tamaño: %i",cola->cantidad_elementos);
    printf("\nla clave de la entrada eliminada es: %i",*eli);
    */

    return 0;
}
