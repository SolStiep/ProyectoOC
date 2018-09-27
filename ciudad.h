typedef struct ciudad{
    char *nombre;
    float pos_x;
    float pos_y;
}*TCiudad;

int distancia_manhattan(TCiudad ciudad1,TCiudad ciudad2);
