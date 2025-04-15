#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define DURACION_MINIMA 10
#define DURACION_MAXIMA 100
#define LONGITUD_DESCRIPCION_MAXIMA 100

struct Tarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;  //       
    int Duracion; // entre 10 – 100  
    };  
typedef struct Tarea Tarea;

struct Nodo{ 
    Tarea T;  
    Nodo *Siguiente;  
}; 
typedef struct Nodo Nodo;

Nodo* CrearListaVacia();
Tarea CrearTarea(int i);
Nodo* CrearNodo(int i); // en vez de pasarla a la tarea, la creo ahi dentro
void InsertarNodo(Nodo **tareasPendientes, Nodo *nodoNuevo);
void CargarTareas(Nodo **tareasPendientes);
void MostrarTareas(Nodo *tareas);

int main(){

    srand(time(NULL));

    Nodo *tareasRealizadas = CrearListaVacia(); 
    Nodo *tareasPendientes = CrearListaVacia();

    CargarTareas(&tareasPendientes); 
    //le paso la direccion en memoria del puntero() el contenido del puntero *tareasPendientes es la direccion en memoria del primer nodo Tarea)

    printf("-------------------- TAREAS PENDIENTES -------------------- \n");
    MostrarTareas(tareasPendientes);

    // printf("-------------------- TAREAS FREALIZADAS -------------------- \n");
    // MostrarTareas(tareasRealizadas);

    return 0;
}

Nodo* CrearListaVacia(){
    return NULL;
}
Tarea CrearTarea(int i){
    Tarea nuevaTarea;

    nuevaTarea.TareaID = 1000 + i;
    
    char *BuffDescripcion;
    BuffDescripcion = (char*)malloc( LONGITUD_DESCRIPCION_MAXIMA * sizeof(char));
    int longitudDescripcion;
    printf("Ingrese la DESCRIPCION de la tarea ID#%d: \n", nuevaTarea.TareaID);
    gets(BuffDescripcion);
    longitudDescripcion = strlen(BuffDescripcion)+1; //longitud  + delimitador '\0'
    nuevaTarea.Descripcion = (char*)malloc(longitudDescripcion * sizeof(char));
    strcpy(nuevaTarea.Descripcion, BuffDescripcion);
    
    free(BuffDescripcion);
    
    int duracion;
    do
    {
        printf("Ingrese la duracion de la tarea (entre 10 y 100): \n");
        scanf("%d", &duracion);
    } while (duracion < DURACION_MINIMA || duracion > DURACION_MAXIMA);
    
    return nuevaTarea;
}
Nodo* CrearNodo(int i){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T = CrearTarea(i);
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}
void InsertarNodo(Nodo **tareasPendientes, Nodo *nodoNuevo){
    //Inserto los nodos al inicio de la lista:

    //contenido del puntero doble: direccion de cabecera 
    Nodo *direccionCabecera  = *tareasPendientes;  //el puntero este apunta a la direccion en memoria de la cabecera
    nodoNuevo->Siguiente = direccionCabecera; // el sig de mi nuevo nodo apunta a la direccion de memoria de cabecera
    *tareasPendientes = nodoNuevo; //la cabecera apunta a la direccion de memoria del nuevo nodo xq nuevoNodo es puntero q contiene la direc del nuevoNodo
}

void CargarTareas(Nodo **tareasPendientes){

    int salir;
    int i = 0;
    Nodo *nuevoNodo;
    do
    {
        printf("------ CARGA DE TAREAS ------ \n");
        nuevoNodo = CrearNodo(i);
        if( &(nuevoNodo->T) != NULL){ //si la tarea no es null.. uso desreferenciacion
            i++;
        }

        InsertarNodo(tareasPendientes,nuevoNodo);
        MostrarTareas(*tareasPendientes);

        printf("Ingrese 0 para salir o cualquier numero para conitnuar cargando: \n");
        scanf("%d", &salir);
        fflush(stdin);

    } while (salir != 0);
    
    
}

void MostrarTareas(Nodo *tareas){
    //tipo de tarea?
    Nodo *punteroAuxiliar = tareas;
    while( punteroAuxiliar != NULL){
        printf("- ID: %d \n", punteroAuxiliar->T.TareaID); //por que me permite usar el . en vez de ->?
        printf("- Duracion: %d \n", punteroAuxiliar->T.Duracion); //por que me permite usar el . en vez de ->?
        printf("- Descripcion: %s \n", punteroAuxiliar->T.Descripcion); //por que me permite usar el . en vez de ->?

        punteroAuxiliar = punteroAuxiliar->Siguiente;
    }
}