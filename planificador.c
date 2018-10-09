#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "colacp.h"
#include "ciudad.h"
#include <math.h>

#define max_ciudad 100

typedef struct par{
    float x;
    float y;
}TPar;

void generar_cola(TLista lista_ciudades, TColaCP cola); //preguntar si no hay que pasar un puntero a la cola
int funcionAscendente(TEntrada t1,TEntrada t2);
int funcionDescendente(TEntrada t1,TEntrada t2);
float distancia_ciudad_usuario(TPar* p_ubicacion_ciudad);
TLista generar_lista(FILE* arch);
void mostrar_cola(TColaCP cola);
float generar_cola_menos_manejo(TLista lista_ciudades);

//global
TPar ubicacion_usuario;

int main(int argc , char * argv[]) {

// PROGRAMA PRINCIPAL

    int operacion=0;

    if(argc != 2){
        printf("ERROR: no ha ingresado el archivo");
        exit(FALSE);
    }

    FILE *archivo = fopen(argv[1],"r");
    if(archivo==NULL){
        printf("ERROR: no se pudo abrir el archivo con el nombre ingresado");
        exit(FALSE);
    }

    TLista lista_ciudades = generar_lista(archivo);

    while(operacion!=4){
        printf("Listado de operaciones: \n");
        printf("1: Mostrar ascendente.\n");
        printf("2: Mostrar descendente.\n");
        printf("3: Reducir horas de manejo.\n");
        printf("4: Salir.\n");
        printf("Elija el numero de operacion a realizar: ");
        scanf("%i",&operacion);
        switch(operacion){
            case 1:{
                TColaCP cola= crear_cola_cp(&funcionAscendente);
                generar_cola(lista_ciudades,cola);
                printf("El listado ascendente de las ciudades es: \n");
                mostrar_cola(cola);
                cp_destruir(cola);
                break;
            }
            case 2:{
                TColaCP cola_2=crear_cola_cp(&funcionDescendente);
                generar_cola(lista_ciudades,cola_2);
                printf("El listado descendente de las ciudades es: \n");
                mostrar_cola(cola_2);
                cp_destruir(cola_2);
                break;
            }
            case 3:{
                printf("Reducir horas manejo \n");
                float f = generar_cola_menos_manejo(lista_ciudades);
                printf("Total recorrido: %f. \n" ,f);
                break;
            }
            case 4:{
                l_destruir(&lista_ciudades);
                break;
            }
            default:{
                printf("Operacion invalida, por favor ingrese un numero valido: \n");
                break;
            }
        }
    }

    return 0;
}

float distancia_ciudad_usuario(TPar* p_ubicacion_ciudad){
    return fabs(ubicacion_usuario.x-p_ubicacion_ciudad->x)+fabs(ubicacion_usuario.y-p_ubicacion_ciudad->y);
}

int funcionAscendente(TEntrada t1,TEntrada t2){
    int retorno;
    float dist_ciu1 , dist_ciu2;
    TPar *par1=(TPar *)t1->clave;
    TPar *par2=(TPar *)t2->clave;
    dist_ciu1=distancia_ciudad_usuario(par1);
    dist_ciu2=distancia_ciudad_usuario(par2);
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
    TPar *par1=(TPar *)t1->clave;
    TPar *par2=(TPar *)t2->clave;
    dist_ciu1=distancia_ciudad_usuario(par1);
    dist_ciu2=distancia_ciudad_usuario(par2);
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
    char nombre_ciudad[max_ciudad] , num_real[30];
    double x,y;
    char c;
    int i=0 , l=0;

    TPosicion pos = POS_NULA;

    if(fscanf(arch,"%[^\n]",linea) != EOF){ //consumimos la primer linea que es la ubicacion del usuario.

        fscanf(arch , "%c" , &c ); //consume el \n
        //procesamos la primer linea que es la ubicacion del usuario

        while(linea[l]!='\0' && linea[l]!=';'){
            num_real[i] = linea[l];
            l++;
            i++;
        }
        l++; //avanzamos del ;
        num_real[i] = '\0'; //para marcar el fin del numero.
        i=0;

        x = atof(num_real); //convertimos el string en real;

        while(linea[l]!='\0'){
            num_real[i] = linea[l];
            l++;
            i++;
        }
        num_real[i] = '\0';
        i=0;
        l=0;

        y = atof(num_real);

        ubicacion_usuario.x = x;
        ubicacion_usuario.y = y;

    }

    while(fscanf(arch,"%[^\n]",linea) != EOF){ //consume una linea entera, lee hasta fin de archivo

        fscanf(arch , "%c" , &c ); //consume el \n

        l=0; //recorremos la linea desde el inicio
        i=0;

        while(linea[l]!='\0' && linea[l]!=';'){
            nombre_ciudad[i] = linea[l];
            l++;
            i++;
        }
        nombre_ciudad[i] = '\0';
        l++; //avanzamos del ;
        i=0;

        while(linea[l]!='\0' && linea[l]!=';'){
            num_real[i] = linea[l];
            l++;
            i++;

        }
        num_real[i] ='\0'; //para marcar el fin del numero.
        l++; //avanzamos del ;
        i=0;

        x = atof(num_real); //convertimos el string en real;

        while(linea[l]!='\0'){
            num_real[i] = linea[l];
            l++;
            i++;
        }
        num_real[i] = '\0';
        i=0;
        l=0; //terminamos de recorrer la linea
        y = atof(num_real);


        //ahora construimos la ciudad y la insertamos en la lista

        TCiudad city = crear_ciudad(x,y,nombre_ciudad);



        if(pos == POS_NULA){
            l_insertar(&lista_ciudades , POS_NULA , city);
            pos = l_primera(lista_ciudades);
        }
        else{
            l_insertar(&lista_ciudades , pos , city);
            pos = l_siguiente(lista_ciudades , pos);
        }

    }

    fclose(arch);

    return lista_ciudades;
}

void generar_cola(TLista lista_ciudades, TColaCP cola){
    TPar *clav;
    TCiudad ciu;
    TEntrada entr;
    TPosicion pos;

    pos = l_primera(lista_ciudades);

    // por cada ciudad de la lista la agrego a la cola
    while(pos != POS_NULA){
        clav=(TPar *)malloc(sizeof(struct par));
        ciu = (TCiudad) pos->elemento;
        clav->x=ciu->pos_x;
        clav->y=ciu->pos_y;
        entr=(TEntrada)malloc((sizeof(struct entrada)));
        entr->clave= clav;
        entr->valor= ciu;
        cp_insertar(cola,entr);
        pos=l_siguiente(lista_ciudades,pos);
    }

}

void mostrar_cola(TColaCP cola){
    int i=1;
    TCiudad city;
    TEntrada entr;
    while(cp_size(cola) > 0){
        entr=cp_eliminar(cola);
        city = (TCiudad)entr->valor;
        printf("%i. %s\n",i,city->nombre);
        free(entr->clave);
        free(entr);
        i++;
    }
}

float generar_cola_menos_manejo(TLista lista_ciudades){
    TColaCP cola_aux; // es la cola que se ira llenando y vaciando, a fin de devolver la ciudad mas cercana al usuario
    TLista lista_aux = crear_lista(); // es la lista que se ira llenando y vaciando, a fin de excluir la ciudad que ya fue visitada
    TPosicion pos = l_primera(lista_ciudades);

    TCiudad ciu;
    TEntrada entr;
    TPar* p_clav;
    TPar ub_usuario;
    ub_usuario.x=ubicacion_usuario.x;
    ub_usuario.y=ubicacion_usuario.y;

    int i=1;
    float dist_recorrida = 0;

    ub_usuario.x = ubicacion_usuario.x;
    ub_usuario.y = ubicacion_usuario.y;

    while(pos!=POS_NULA){ //generamos la lista_aux por primera vez.
        l_insertar(&lista_aux, POS_NULA , pos->elemento); //insertamos siempre en la primer posicion
        pos = l_siguiente(lista_ciudades , pos);
    }

    while(l_size(lista_aux) > 0){
        cola_aux = crear_cola_cp(&funcionAscendente);
        generar_cola(lista_aux , cola_aux);

        entr = cp_eliminar(cola_aux);
        ciu=(TCiudad)entr->valor;
        printf("%i. %s \n",i,ciu->nombre);
        i++;
        p_clav = (TPar*) entr->clave;

        dist_recorrida+= distancia_ciudad_usuario(p_clav);
        ubicacion_usuario.x=p_clav->x;
        ubicacion_usuario.y=p_clav->y;
        free(p_clav);
        free(entr);

        l_destruir(&lista_aux);
        lista_aux = crear_lista();


        while(cp_size(cola_aux) > 0){
            TEntrada e = cp_eliminar(cola_aux);
            ciu = (TCiudad) e->valor;
            l_insertar(&lista_aux , POS_NULA , ciu);
            free(e->clave);
            free(e);
        }

        cp_destruir(cola_aux);

    }
    ubicacion_usuario.x=ub_usuario.x;
    ubicacion_usuario.y=ub_usuario.y;

    return dist_recorrida;
}
