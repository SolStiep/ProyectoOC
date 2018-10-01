#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "colacp.h"
#include "ciudad.h"

int ubicacion_usuario_x,ubicacion_usuario_y;  // ver alguna otra forma de hacerlo TIENE QUE SER GLOBAL
                                                  // PARA PODER USARLAS EN LAS DISTINTAS FUNCIONES
int funcion(TEntrada t1 , TEntrada t2);

int main()
{
/*    // ver si es asi insertar lista
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
    TColaCP cola=crear_cola_cp(&funcion);

    cp_insertar(cola,e1);
    cp_insertar(cola,e2);
    cp_insertar(cola,e3);
    cp_insertar(cola,e4);
    printf("tamaño antes de eliminar alguna entrada: %i\n",cola->cantidad_elementos);
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


// PROGRAMA PRINCIPAL

    int operacion=0;
    char nombre_archivo[26];
    TLista lista_cuidades;

    printf("Ingrese nombre del archivo: ");
    scanf("%s",nombre_archivo);
    FILE *archivo=fopen(nombre_archivo,"r");

    while(operacion!=4){
        printf("Elija operacion a realizar: ");
        scanf("%i",&operacion);
        if(operacion==1){
            //creo la cola con la funcionAscendente y
            // llamo a mostrarAscendente

        }
        else{
            if(operacion==2){
                //mostrar descendente
            }
            else{
                if(operacion==3){
                    //reducir horas manejo
                }
                else{
                    // liberar espacio utilizado
                }
            }
        }
    }

    return 0;
}

int funcion(TEntrada t1 , TEntrada t2){
    int retorno;
    int *c1=t1->clave,*c2=t2->clave;
    int a =*c1,b=*c2;
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

void mostrarAscendente(TLista lista_ciudades, TColaCP cola){
    float *clav;
    TCiudad val;
    TEntrada entr;
    TCiudad ciu;
    // por cada ciudad de la lista la agrego a la cola con la funcionAscendente
        clav=(float *)malloc(sizeof(float));
        val=(TCiudad)malloc(sizeof(struct ciudad));
        entr=(TEntrada)malloc((sizeof(struct entrada)));
        *clav=abs(ciu->pos_x-ubicacion_usuario_x)+abs(ciu->pos_y-ubicacion_usuario_y);
        entr->clave=clav;
        entr->valor=ciu;
        cp_insertar(cola,entr);
}

int funcionAscendente(TEntrada t1,TEntrada t2){
    int retorno;
    float *c1=t1->clave,*c2=t2->clave;
    float a =*c1,b=*c2;
    if(a<b){
        retorno=1;
    }
    else{
        if(a>b){
            retorno=-1;
        }
        else{
            retorno=0;
        }
    }
    return retorno;
}
