#include "ciudad.h"
#include <math.h>
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

int distancia_manhattan(TCiudad ciudad1,TCiudad ciudad2){
    int distancia=fabs(ciudad2->pos_x-ciudad1->pos_x)+fabs(ciudad2->pos_y+ciudad1->pos_y);
    return distancia;
}

TCiudad crear_ciudad(float x, float y , char* name){

    TCiudad city = (TCiudad) malloc(sizeof(struct ciudad));
    city->nombre = (char *) malloc(sizeof(char) * strlen(name));
    strcpy(city->nombre , name);
    city->pos_x = x;
    city->pos_y = y;

    return city;

}

void destruir_ciudad(TCiudad city){
    free(city->nombre);
    free(city);
}
