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

int ElegirId(Nodo **tareas);

Nodo* BuscarNodoPorId(Nodo **tareas, int idTarea);
// Nodo* QuitarNodo(Nodo **tareas, int idTarea);

void MostrarPorId(Nodo **tareasPendientees, Nodo **tareasRealizadas);
// void MostrarPorClave(Nodo **tareasPendientees, Nodo **tareasRealizadas);
void MostrarTareas(Nodo *tareas);

void CargarTareas(Nodo **tareasPendientes);
// void MoverTarea(Nodo **tareasPendientes, Nodo **tareasRealizadas,int idTarea);
void LimpiarBuffer();

int main(){

    srand(time(NULL));

    Nodo *tareasRealizadas = CrearListaVacia(); 
    Nodo *tareasPendientes = CrearListaVacia();
    
    int opcion, ingresoCorrecto;

    do
    {
        printf("------------------- M E N U -------------------\n");
        printf("1- Cargar tareas pendientes\n");
        printf("2- Mostrar todas las tareas pendientes\n");
        printf("3- Mostrar todas las tareas realizadas\n");
        printf("4- Mostrar una tarea de ID especifico\n");
        printf("5- Mostrar una tarea segun una palabra clave\n");
        printf("6- Marcar tarea como realizada\n");
        printf("7- Salir\n");
        printf("------------------------------------------------\n");

        printf("Elige una opcion:");
        scanf("%d", &opcion);
        LimpiarBuffer();
        
        switch (opcion)
        {
        case 1: CargarTareas(&tareasPendientes); //le paso la direccion en memoria del puntero() el contenido del puntero *tareasPendientes es la direccion en memoria del primer nodo Tarea)
            break;
        case 2: MostrarTareas(tareasPendientes);
            break;
        case 3: MostrarTareas(tareasRealizadas);
            break;
        case 4: MostrarPorId(&tareasPendientes,&tareasRealizadas);
            break;
        case 5:
            //MostrarPorClave(&tareasPendientes,&tareasRealizadas);
            break;        
        case 6: //mover tarea
            break;      
        default:
            if(opcion!= 7){
                printf("Opcion no valida...\n");
            }
            break;
        }
    } while (opcion!= 7);
    
    printf(" - USTED SE HA DESCONECTADO. QUE TENGA BUEN DIA :) . -");

    return 0;
}

void LimpiarBuffer() {
    while (getchar() != '\n'); // limpia el bufer, porque consume todos los caracteres restantes hasta el Enter
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
        LimpiarBuffer();
    } while (duracion < DURACION_MINIMA || duracion > DURACION_MAXIMA);

    nuevaTarea.Duracion = duracion;
    
    return nuevaTarea;
}

Nodo* CrearNodo(int i){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T = CrearTarea(i);
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
}

void InsertarNodo(Nodo **tareasPendientes, Nodo *nodoNuevo){//Inserto los nodos al inicio de la lista

    Nodo *auxCabecera  = *tareasPendientes;  //el puntero nuevo apunta a la cabecera
    nodoNuevo->Siguiente = auxCabecera; // el sig de mi nuevo nodo apunta a la direccion de memoria de cabecera
    *tareasPendientes = nodoNuevo; //la cabecera apunta al nuevo nodo 
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
        LimpiarBuffer();

    } while (salir != 0);
    
    
}

void MostrarTareas(Nodo *tareas){ //aqui no uso puntero doble ni acceso a su contenido, otra forma de hacerlo. Directamente uso la direccion de memoria del primer nodo de la lista

    Nodo *punteroAuxiliar = tareas;

    while( punteroAuxiliar != NULL){
        printf("- ID: %d \n", punteroAuxiliar->T.TareaID); //por que me permite usar el . en vez de ->?
        printf("- Duracion: %d \n", punteroAuxiliar->T.Duracion); //por que me permite usar el . en vez de ->?
        printf("- Descripcion: %s \n", punteroAuxiliar->T.Descripcion); //por que me permite usar el . en vez de ->?

        punteroAuxiliar = punteroAuxiliar->Siguiente;
    }
}

int ElegirId(Nodo **tareas){
    int idTarea;
    do
    {
        MostrarTareas(*tareas);
        printf("Elige el ID de la tarea a marcar como realizadas o ingrese 0 para salir: \n");
        scanf("%d", &idTarea);
        LimpiarBuffer();
        
    } while (idTarea!= 0 || idTarea <1000);

    return idTarea;
}

Nodo* BuscarNodoPorId(Nodo **tareas, int idTarea){
    
    Nodo *auxiliarCabecera = *tareas;

    if(idTarea >= 1000){
        while(auxiliarCabecera->Siguiente!=NULL  && auxiliarCabecera->T.TareaID != idTarea){
            auxiliarCabecera = auxiliarCabecera->Siguiente;
        }
        if(auxiliarCabecera->T.TareaID == idTarea){ //EN LA TEORIA NO VERIFICA SI EL UNICO NODO CONTIENE A ESE VALOR
            return auxiliarCabecera; // si entra al while recorre hasta encontrar y retorna, sino directamente retorna el primero si lo tiene
        }else{
            return NULL;
        }
    }else{
        printf("ID no valido. \n");
        return NULL;
    }
}

void MostrarPorId(Nodo **tareasPendientes, Nodo **tareasRealizadas){
    Nodo *auxTareasPendientes = *tareasPendientes;
    Nodo *auxTareasRealizadas = *tareasRealizadas;

    Nodo *nodoEncontrado = NULL;

    int idTarea = ElegirId(&auxTareasPendientes);
    bool encontradoPendiente = false;
    bool encontradoRealizado = false;

    //BUSCO PRIMERO POR TAREAS REALIZADAS:
    if(auxTareasRealizadas){ //si no hay tareas realizadas directamente salto al otro IF

        nodoEncontrado = BuscarNodoPorId(&auxTareasRealizadas, idTarea);

        if(nodoEncontrado){

            printf("-- TAREA ENCONTRADA: \n");
            printf("- ID: %d \n", auxTareasPendientes->T.TareaID); 
            printf("- Duracion: %d \n", auxTareasPendientes->T.Duracion); 
            printf("- Descripcion: %s \n", auxTareasPendientes->T.Descripcion);

            encontradoRealizado = true;
        }
    }
    
    //BUSCO POR TAREAS PENDIENTES:
    if(auxTareasPendientes && !encontradoRealizado){ //le agrego la 2da condicion para que no busque de nuevo si ya encontro

        nodoEncontrado = BuscarNodoPorId(&auxTareasPendientes, idTarea);

        if(nodoEncontrado){

            printf("-- TAREA ENCONTRADA: \n");
            printf("- ID: %d \n", auxTareasPendientes->T.TareaID); 
            printf("- Duracion: %d \n", auxTareasPendientes->T.Duracion); 
            printf("- Descripcion: %s \n", auxTareasPendientes->T.Descripcion);

            encontradoPendiente = true;
        }
    }
 

    if(encontradoRealizado){
        printf("- Tipo: TAREA REALIZADA.\n");
    }else if(encontradoPendiente){
        printf("- Tipo: TAREA PENDIENTE.\n");
    }else{
        printf("ERROR. No existe una tarea con ese ID. \n");
    }
}

// Nodo* QuitarNodo(Nodo **tareasPendientes, int idTarea){
//     Nodo **auxiliarCabecera = *tareasPendientes;

//     whhile(auxiliarCabecera->){

//     }

//     if(nodoAquitar){
//         Nodo *nodoTemporal = nodoAquitar;

//     }else{
//         printf("El nodo no pudo ser encontrado y movido.\n");
//         return NULL;
//     }
// }