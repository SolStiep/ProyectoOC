typedef void* TElemento;
typedef struct celda* TLista; // porque me deja definir el tipo de dato *TLista si todavia no defini struct celda?
typedef struct celda* TPosicion;
//porque declaramos a todo de tipo puntero?

struct celda{
    TElemento elemento;
    struct celda *celda_anterior;
    struct celda *celda_siguiente;
};


//procedimientos y funciones

TLista crear_lista();

int l_insertar(TLista *lista , TPosicion pos ,TElemento elem); //por qué un puntero a la lista?

int l_eliminar(TLista *lista , TPosicion pos);

TPosicion l_primera(TLista lista);  //porque antes pasabamos la lista como puntero y ahora no?

TPosicion l_ultima(TLista lista);

TPosicion l_anterior(TLista lista , TPosicion pos);

TPosicion l_siguiente(TLista lista , TPosicion pos);

TElemento l_recuperar(TLista lista , TPosicion pos);

int l_size(TLista lista);

int l_destruir(TLista *lista);


