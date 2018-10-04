#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "colacp.h"
#include "ciudad.h"


#define max_ciudad 100

typedef struct par{
    float x;
    float y;
}TPar;

TPar crear_par(int x,int y){
    TPar par;
    par.x = x;
    par.y = y;

    return par;
}



void generar_cola(TLista lista_ciudades, TColaCP cola);
int funcionAscendente(TEntrada t1,TEntrada t2);
int funcionDescendente(TEntrada t1,TEntrada t2);
float distancia_ciudad_usuario(TPar* ubicacion_ciudad);
TLista generar_lista(FILE* arch);
//global
TPar ubicacion_usuario;

int main(int argc , char * argv[]) {

// PROGRAMA PRINCIPAL

    int operacion=0;

    if(argc != 2){
        printf("ERROR: no ha ingresado el archivo");
        exit(FALSE);
    }

    FILE *archivo = fopen(argv[1],"r"); //como hago para ver si la invocacion no fue la indicada?

    TLista lista_ciudades = generar_lista(archivo);

    while(operacion!=4){
        printf("Elija operacion a realizar: ");
        scanf("%i",&operacion);
        if(operacion==1){
            TColaCP cola=crear_cola_cp(&funcionAscendente); //como hacemos para pasar la funcion?
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
                        printf("Operacion invalida, por favor ingrese nuevamente: \n");
                    }
                }
            }
        }
    }

    return 0;
}

float distancia_ciudad_usuario(TPar* p_ubicacion_ciudad){
    TPar ubicacion_ciudad = *p_ubicacion_ciudad;
    return abs(ubicacion_usuario.x-ubicacion_ciudad.x)+abs(ubicacion_usuario.y-ubicacion_ciudad.y);
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
        clav = crear_par(ciu->pos_x , ciu->pos_y);
        entr=(TEntrada)malloc((sizeof(struct entrada)));
        entr->clave= &clav;
        entr->valor= ciu;
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
    char nombre_ciudad[max_ciudad] , num_real[20];
    double x,y;
    char c='a';
    int i=0 , l=0;

    if(fscanf(arch,"%[^\n]",linea) != EOF){ //consumimos la primer linea que es la ubicacion del usuario.

        fscanf(arch , "%c" , &c ); //consume el \n
        //procesamos la primer linea que es la ubicacion del usuario

        while(linea[l]!='\0' && c!=';'){
            num_real[i] = c;
            l++;
            i++;
        }
        num_real[i] = '0'; //para marcar el fin del numero.
        i=0;

        x = atof(num_real); //convertimos el string en real;

        while(linea[l]!='\0'){
            num_real[i] = c;
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

        while(linea[l]!='\0' && c!=';'){
            nombre_ciudad[i] = c;
            l++;
            i++;
        }
        i=0;

        while(linea[l]!='\0' && c!=';'){
            num_real[i] = c;
            l++;
            i++;
        }
        num_real[i] = '0'; //para marcar el fin del numero.
        i=0;

        x = atof(num_real); //convertimos el string en real;

        while(linea[l]!='\0'){
            num_real[i] = c;
            l++;
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


    return lista_ciudades;
}

