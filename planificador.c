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


void generar_cola(TLista lista_ciudades, TColaCP cola); //preguntar si no hay que pasar un puntero a la cola
int funcionAscendente(TEntrada t1,TEntrada t2);
int funcionDescendente(TEntrada t1,TEntrada t2);
float distancia_ciudad_usuario(TPar* ubicacion_ciudad);
TLista generar_lista(FILE* arch);
void mostrarCola(TColaCP cola);
float generar_cola_menos_manejo(TLista lista_ciudades , TColaCP cola); //preguntar si no hay que pasar un puntero a la cola

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
                TColaCP cola=crear_cola_cp(&funcionAscendente);
                generar_cola(lista_ciudades,cola);
                printf("El listado ascendentes de las ciudades es: \n");
                mostrarCola(cola);
                cp_destruir(cola); // LLAMAMOS A DESTRUIR O DIRECTAMENTE HACEMOS FREE(COLA) ?
                break;              //PORQUE YA QUEDO LIBERADA LA MEMORIA DE TODOS LOS ELEMENTOS AL ELIMINARLOS.
            }
            case 2:{
                TColaCP cola=crear_cola_cp(&funcionDescendente);
                generar_cola(lista_ciudades,cola);
                printf("El listado descendentes de las ciudades es: \n");
                mostrarCola(cola);  // LLAMAMOS A DESTRUIR O DIRECTAMENTE HACEMOS FREE(COLA) ?
                cp_destruir(cola); //PORQUE YA QUEDO LIBERADA LA MEMORIA DE TODOS LOS ELEMENTOS AL ELIMINARLOS.
                break;
            }
            case 3:{
                TColaCP cola = crear_cola_cp(&funcionAscendente);
                float f = generar_cola_menos_manejo(lista_ciudades , cola);
                printf("Reducir horas manejo \n");
                mostrarCola(cola);
                cp_destruir(cola);
                printf("Total recorrido: %f. \n" ,f);
                break;
            }
            case 4:{
                //limpiar memoria
                l_destruir(&lista_ciudades); // solo eso porque las colas se destruyen despues de usarlas en c/operacion no?
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
    TPar ubicacion_ciudad = *p_ubicacion_ciudad;
    return abs(ubicacion_usuario.x-ubicacion_ciudad.x)+abs(ubicacion_usuario.y-ubicacion_ciudad.y);
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
        TPosicion pos = POS_NULA;

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

void generar_cola(TLista lista_ciudades, TColaCP cola){ //preguntar si no hay que pasar un puntero a la cola
    TPar clav;
    TCiudad ciu;
    TEntrada entr;
    TPosicion pos;

    pos = l_primera(lista_ciudades);

    // por cada ciudad de la lista la agrego a la cola
    while(pos != POS_NULA){
        ciu = (TCiudad) pos->elemento; //preguntar por este casteo
        clav = crear_par(ciu->pos_x , ciu->pos_y); //al no ser un puntero no podemos destruirlo. no importa? en que momento se libera esta memoria?
        entr=(TEntrada)malloc((sizeof(struct entrada))); //cuando liberamos esta entrada?
        entr->clave= &clav;
        entr->valor= ciu;
        cp_insertar(cola,entr);
        pos=l_siguiente(lista_ciudades,pos);
    }
}

void mostrarCola(TColaCP cola){
    int i=0;
    TCiudad city;
    TEntrada entr;
    while(i<cp_size(cola)){
        entr=cp_eliminar(cola)->valor;
        city = (TCiudad) entr->valor;
        printf("%i. %s\n",i+1,city->nombre);
        free(entr);
        i++;
    }
}

float generar_cola_menos_manejo(TLista lista_ciudades , TColaCP cola){ //preguntar si no hay que pasar un puntero a la cola
    TColaCP cola_aux; // es la cola que se ira llenando y vaciando, a fin de devolver la ciudad mas cercana al usuario
    TLista lista_aux = crear_lista(); // es la lista que se ira llenando y vaciando, a fin de excluir la ciudad que ya fue visitada
    TPosicion pos = l_primera(lista_ciudades);

    TCiudad ciu;
    TEntrada entr;
    TPar* p_clav;

    float dist_recorrida = 0;

    while(pos!=POS_NULA){ //generamos la lista_aux por primera vez.
        l_insertar(&lista_aux, POS_NULA , pos->elemento); //insertamos siempre en la primer posicion
        pos = l_siguiente(lista_ciudades , pos);
    }

    while(l_size(lista_aux) > 0){
        cola_aux = crear_cola_cp(&funcionAscendente);
        generar_cola(lista_aux , cola_aux);

        entr = cp_eliminar(cola_aux);
        cp_insertar(cola,entr);

        ciu = (TCiudad) entr->valor;
        p_clav = (TPar*) entr->clave;

        dist_recorrida+= distancia_ciudad_usuario(p_clav);

        ubicacion_usuario.x = ciu->pos_x;
        ubicacion_usuario.y = ciu->pos_y;

        l_destruir(&lista_aux);
        lista_aux = crear_lista();

        int i=0;
        while(i<cp_size(cola)){ //es necesario hacer este while ya que la cola no le hace free a las entradas?
            TEntrada e = cp_eliminar(cola);
            ciu = (TCiudad) entr->valor;
            l_insertar(&lista_aux , POS_NULA , ciu);
            free(e);
            i++;
        }

        cp_destruir(cola_aux);

    }


    return dist_recorrida;
}
