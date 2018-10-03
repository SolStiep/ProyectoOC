#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "colacp.h"
#include "ciudad.h"

typedef struct par{
    int x;
    int y;
}*TPar;

void obtenerListado(TLista lista_ciudades, TColaCP cola);
int funcionAscendente(TEntrada t1,TEntrada t2);
int funcionDescendente(TEntrada t1,TEntrada t2);
int distancia_ciudad_usuario(TPar ubicacion_ciudad);

//global
TPar ubicacion_usuario;

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
// PROGRAMA PRINCIPAL

    int operacion=0;
    char nombre_archivo[26];

    TLista lista_cuidades; // podria ser global tambien ¿?


    printf("Ingrese nombre del archivo: ");
    scanf("%s",nombre_archivo);
    FILE *archivo=fopen(nombre_archivo,"r");

    while(operacion!=4){
        printf("Elija operacion a realizar: ");
        scanf("%i",&operacion);
        if(operacion==1){
            TColaCP cola=crear_cola_cp(funcionAscendente);
            obtenerListado(lista_cuidades,cola);
        }
        else{
            if(operacion==2){
                TColaCP cola=crear_cola_cp(funcionDescendente);
                obtenerListado(lista_cuidades,cola);
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

int distancia_ciudad_usuario(TPar ubicacion_ciudad){
    return abs(ubicacion_usuario->x-ubicacion_ciudad->x)+abs(ubicacion_usuario->y-ubicacion_ciudad->y);
}

void obtenerListado(TLista lista_ciudades, TColaCP cola){
    TPar clav;
    TCiudad val,ciu;
    TEntrada entr;
    TPosicion elem;
    int i=1;
    if(l_size(lista_ciudades)>0){
        elem=l_primera(lista_ciudades);
        ciu=elem->elemento;
    }
    // por cada ciudad de la lista la agrego a la cola
    while(i<l_size(lista_ciudades)){
        clav=(TPar)malloc(sizeof(struct par));
        val=(TCiudad)malloc(sizeof(struct ciudad));
        entr=(TEntrada)malloc((sizeof(struct entrada)));
        clav->x=ciu->pos_x;
        clav->y=ciu->pos_y;
        entr->clave=clav;
        entr->valor=ciu;
        cp_insertar(cola,entr);
        elem=l_siguiente(lista_ciudades,elem);
        ciu=elem->elemento;
        i++;
    }
}

int funcionAscendente(TEntrada t1,TEntrada t2){
    int retorno,dist_ciu1,dist_ciu2;
    dist_ciu1=distancia_ciudad_usuario(t1->clave);
    dist_ciu2=distancia_ciudad_usuario(t2->clave);
    if(dist_ciu1<dist_ciu2){
        retorno=1;
    }
    else{
        if(dist_ciu1>dist_ciu2){
            retorno=-1;
        }
        else{
            retorno=0;
        }
    }
    return retorno;
}

int funcionDescendente(TEntrada t1,TEntrada t2){
    int retorno,dist_ciu1,dist_ciu2;
    dist_ciu1=distancia_ciudad_usuario(t1->clave);
    dist_ciu2=distancia_ciudad_usuario(t2->clave);
    if(dist_ciu1>dist_ciu2){
        retorno=1;
    }
    else{
        if(dist_ciu1<dist_ciu2){
            retorno=-1;
        }
        else{
            retorno=0;
        }
    }
    return retorno;
}


