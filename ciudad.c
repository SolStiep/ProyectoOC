#include "ciudad.h"
#include <math.h>

int distancia_manhattan(TCiudad ciudad1,TCiudad ciudad2){
    int distancia=fabs(ciudad2->pos_x-ciudad1->pos_x)+fabs(ciudad2->pos_y+ciudad1->pos_y);
    return distancia;
}
