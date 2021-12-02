#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define TAM_MAXIMO 100

typedef struct nodo {

    int id;
    char nombre[TAM_MAXIMO];
    struct nodo *nodoSiguiente;
    struct nodo *nodoAnterior;

} nodo;

typedef struct lista {

    struct nodo *inicio;
    struct nodo *fin;

} lista;

lista *crearLista() {

    struct lista *nuevaLista = malloc(sizeof(lista));
    nuevaLista->inicio = NULL;
    nuevaLista->fin = NULL;
    return nuevaLista;
}

nodo *crearNodo(int id, char *nombre[TAM_MAXIMO]) {

    struct nodo *nuevoNodo = malloc(sizeof(nodo));
    nuevoNodo->id = id;
    strcpy(nuevoNodo->nombre, (const char *) nombre);
    nuevoNodo->nodoSiguiente = NULL;
    nuevoNodo->nodoAnterior = NULL;
    return nuevoNodo;
}

void agregarOrdenado(lista *lista, nodo *nuevoNodo) {

    if (lista->inicio != NULL) {
        if (lista->inicio->id >= nuevoNodo->id) {
            nuevoNodo->nodoSiguiente = lista->inicio;
            lista->inicio = nuevoNodo;
        } else if (lista->fin->id <= nuevoNodo->id) {
            lista->fin->nodoSiguiente = nuevoNodo;
            nuevoNodo->nodoAnterior = lista->fin;
            lista->fin = nuevoNodo;
        } else {
            struct nodo *nodoTemporal = lista->inicio;
            while (nodoTemporal != NULL) {
                if (nuevoNodo->id <= nodoTemporal->id) {
                    nuevoNodo->nodoAnterior = nodoTemporal->nodoAnterior;
                    nuevoNodo->nodoSiguiente = nodoTemporal;
                    nodoTemporal->nodoAnterior = nuevoNodo;
                    nuevoNodo->nodoAnterior->nodoSiguiente = nuevoNodo;
                    break;
                } else {
                    nodoTemporal = nodoTemporal->nodoSiguiente;
                }
            }
        }
    } else {
        lista->inicio = nuevoNodo;
        lista->fin = nuevoNodo;
    }

}
// Lista secundaria (Aux)
typedef struct nodoAux {

    int idAux;
    char nombreAux[TAM_MAXIMO];
    struct nodoAux *nodoSiguienteAux;
    struct nodoAux *nodoAnteriorAux;

} nodoAux;

typedef struct listaAux {

    struct nodoAux *inicioAux;
    struct nodoAux *finAux;

} listaAux;

listaAux *crearListaAux() {

    struct listaAux *nuevaListaAux = malloc(sizeof(listaAux));
    nuevaListaAux->inicioAux = NULL;
    nuevaListaAux->finAux = NULL;
    return nuevaListaAux;
}

nodoAux *crearNodoAux(int idAux, char *nombreAux[TAM_MAXIMO]) {

    struct nodoAux *nuevoNodoAux = malloc(sizeof(nodoAux));
    nuevoNodoAux->idAux = idAux;
    strcpy(nuevoNodoAux->nombreAux, (const char *) nombreAux);
    nuevoNodoAux->nodoSiguienteAux = NULL;
    nuevoNodoAux->nodoAnteriorAux = NULL;
    return nuevoNodoAux;
}

void agregarOrdenadoInverso(listaAux *listaAux, nodoAux *nuevoNodoAux) {
    if (listaAux->inicioAux != NULL) {
        if (listaAux->finAux->idAux <= nuevoNodoAux->idAux) {
            nuevoNodoAux->nodoAnteriorAux = listaAux->finAux;
            listaAux->finAux = nuevoNodoAux;
        } else if (listaAux->inicioAux->idAux>= nuevoNodoAux->idAux) {
            listaAux->inicioAux->nodoAnteriorAux = nuevoNodoAux;
            nuevoNodoAux->nodoSiguienteAux = listaAux->inicioAux;
            listaAux->inicioAux = nuevoNodoAux;
        } else {
            struct nodoAux *nodoTemporalAux = listaAux->finAux;
            while (nodoTemporalAux != NULL) {
                if (nuevoNodoAux->idAux >= nodoTemporalAux->idAux) {
                    nuevoNodoAux->nodoSiguienteAux = nodoTemporalAux->nodoSiguienteAux;
                    nuevoNodoAux->nodoAnteriorAux = nodoTemporalAux;
                    nodoTemporalAux->nodoSiguienteAux = nuevoNodoAux;
                    nuevoNodoAux->nodoSiguienteAux = nuevoNodoAux;
                    break;
                } else {
                    nodoTemporalAux = nodoTemporalAux->nodoSiguienteAux;
                }
            }
        }
    } else {
        listaAux->inicioAux = nuevoNodoAux;
        listaAux->finAux = nuevoNodoAux;
    }
}


int main() {

    int opcion = 0;
    struct lista *lista = crearLista();
    struct listaAux *listaAux = crearListaAux();
    do {

        printf("Seleccion una opcion: \n 1) Agregar persona \n 2) Ver personas(Ascendente) \n 3) Ver personas(Descendente) \n 4) Ver lista secundaria \n 5) Salir \n");
        scanf("%i", &opcion);

        if (opcion == 1) {

            int id = 0;
            char nombre[TAM_MAXIMO];
            printf("Digite el numero de identificacion: \n");
            scanf("%i", &id);
            printf("Digite el nombre: \n");
            scanf("%s", &nombre);
            struct nodo *nuevoNodo = crearNodo(id, (char **) &nombre);
            struct nodoAux *nuevoNodoAux = crearNodoAux(id,(char **) &nombre);
            agregarOrdenado(lista, nuevoNodo);
            agregarOrdenadoInverso(listaAux, nuevoNodoAux);

        } else if (opcion == 2) {

            nodo *nodoTemporal = lista->inicio;
            printf("--------------------------------------------\n");
            while (nodoTemporal != NULL) {

                printf("ID: %i | Nombre: %s \n", nodoTemporal->id, nodoTemporal->nombre);
                nodoTemporal = nodoTemporal->nodoSiguiente;

            }
            printf("--------------------------------------------\n");

        } else if (opcion == 3) {

            nodo *nodoTemporal = lista->fin;
            if (nodoTemporal != NULL) {
                printf("--------------------------------------------\n");
                while (nodoTemporal != NULL) {

                    printf("ID: %i | Nombre: %s \n", nodoTemporal->id, nodoTemporal->nombre);
                    nodoTemporal = nodoTemporal->nodoAnterior;

                }
                printf("--------------------------------------------\n");
            } else {
                printf("La lista esta vacia\n");
            }

        } else if (opcion == 4) {

            nodoAux *nodoTemporalAux = listaAux->finAux;
            printf("--------------------------------------------\n");
            while (nodoTemporalAux != NULL) {

                printf("ID: %i | Nombre: %s \n", nodoTemporalAux->idAux, nodoTemporalAux->nombreAux);
                nodoTemporalAux = nodoTemporalAux->nodoAnteriorAux;

            }
            printf("--------------------------------------------\n");
        } else {
            printf("Opcion incorrecta\n");
        }
    } while (opcion != 5);


    return 0;
}
