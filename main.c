#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "colacp.h"
#include "ciudad.h"

typedef struct par{
    float x;
    float y;
}*TPar;

void generar_cola(TLista lista_ciudades, TColaCP cola);
int funcionAscendente(TEntrada t1,TEntrada t2);
int funcionDescendente(TEntrada t1,TEntrada t2);
float distancia_ciudad_usuario(TPar ubicacion_ciudad);
TLista generar_lista(FILE* arch);
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




    printf("Ingrese nombre del archivo: ");
    scanf("%s" , nombre_archivo);
    FILE *archivo = fopen(nombre_archivo,"r"); //como hago para ver si la invocacion no fue la indicada?

    TLista lista_ciudades = generar_lista(archivo); // podria ser global tambien ?

    while(operacion!=4){
        printf("Elija operacion a realizar: ");
        scanf("%i",&operacion);
        if(operacion==1){
            TColaCP cola=crear_cola_cp(funcionAscendente); //como hacemos para pasar la funcion?
            generar_cola(lista_ciudades,cola);
        }
        else{
            if(operacion==2){
                TColaCP cola=crear_cola_cp(funcionDescendente); //como hacemos para pasar la funcion?
                generar_cola(lista_ciudades,cola);
            }
            else{
                if(operacion==3){
                    //reducir horas manejo
                }
                else{
                    if(operacion==4){
                        // liberar espacio utilizado
                    }
                    else{
                        printf("operacion invalida, por favor ingrese nuevamente: \n");
                    }
                }
            }
        }
    }

    return 0;
}

float distancia_ciudad_usuario(TPar ubicacion_ciudad){
    return abs(ubicacion_usuario->x-ubicacion_ciudad->x)+abs(ubicacion_usuario->y-ubicacion_ciudad->y);
}

void generar_cola(TLista lista_ciudades, TColaCP cola){ //le añade las entradas a la cola dependiendo la funcion que tenga.
    TPar clav;
    TCiudad ciu;
    TEntrada entr;
    TPosicion pos;

    pos = l_primera(lista_ciudades); //si la lista es vacia devuelve pos_nula

    // por cada ciudad de la lista la agrego a la cola
    while(pos != POS_NULA){
        ciu = (TCiudad) pos->elemento; //preguntar por este casteo
        clav=(TPar)malloc(sizeof(struct par));
        entr=(TEntrada)malloc((sizeof(struct entrada)));
        clav->x=ciu->pos_x;
        clav->y=ciu->pos_y;
        entr->clave=clav;
        entr->valor=ciu;
        cp_insertar(cola,entr);

        pos=l_siguiente(lista_ciudades,pos);
    }
}

int funcionAscendente(TEntrada t1,TEntrada t2){
    int retorno;
    float dist_ciu1 , dist_ciu2;
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
    int retorno;
    float dist_ciu1 , dist_ciu2;
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

TLista generar_lista(FILE* arch){
    TLista lista_ciudades = crear_lista();

    char linea[250];
    char nombre_ciudad[100] , num_real[20] = "asd";
    double x,y;
    char c;
    int i=0;

    if(fscanf(arch,"%[^\n]",linea) != EOF){ //consumimos la primer linea que es la ubicacion del usuario.
        fscanf(arch , "%c" , &c ); //consume el \n

        while(fscanf(arch,"%[^\n]",linea) != EOF){ //consume una linea entera, lee hasta fin de archivo

            while(fscanf(arch,"%c", &c) != EOF && c!=';'){
                nombre_ciudad[i] = c;
                i++;
            }
            i=0;
            while(fscanf(arch,"%c", &c) != EOF && c!=';'){
                num_real[i] = c;
                i++;
            }
            num_real[i] = '0'; //para marcar el fin del numero.
            i=0;

            x = atof(num_real); //convertimos el string en real;


            while(fscanf(arch,"%c", &c) != EOF && c!=';'){
                num_real[i] = c;
                i++;
            }
            num_real[i] = '\0';
            i=0;

            y = atof(num_real);

            //ahora construimos la ciudad y la insertamos en la lista
            TCiudad city = crear_ciudad(x,y,nombre_ciudad);
            TPosicion pos;

            if(l_size(lista_ciudades) == 0){
                l_insertar(&lista_ciudades , POS_NULA , city);
                pos = l_primera(lista_ciudades);
            }
            else{
                l_insertar(&lista_ciudades , pos , city);
                pos = l_siguiente(lista_ciudades , pos);
            }


        }
    }

    return lista_ciudades;
}
