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
    nuevoNodo->nodoAnterior;
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

int main() {

    int opcion = 0;
    struct lista *lista = crearLista();
    do {

        printf("Seleccion una opcion: \n 1) Agregar persona \n 2.Ver personas(Ascendente) \n 3. Ver personas(Descendente) \n 4. Salir \n");
        scanf("%i", &opcion);

        if (opcion == 1) {

            int id = 0;
            char nombre[TAM_MAXIMO];
            printf("Digite el numero de identificacion: \n");
            scanf("%i", &id);
            printf("Digite el nombre: \n");
            scanf("%s", &nombre);
            struct nodo *nuevoNodo = crearNodo(id, (char **) &nombre);
            agregarOrdenado(lista, nuevoNodo);

        } else if (opcion == 2) {

            nodo *nodoTemporal = lista->inicio;
            while (nodoTemporal != NULL) {
                printf("ID: %i | Nombre: %s \n", nodoTemporal->id, nodoTemporal->nombre);
                nodoTemporal = nodoTemporal->nodoSiguiente;

            }
        } else if (opcion == 3) {

            nodo *nodoTemporal = lista->fin;
            if (nodoTemporal != NULL) {
                while (nodoTemporal != NULL) {
                    printf("ID: %i | Nombre: %s \n", nodoTemporal->id, nodoTemporal->nombre);
                    nodoTemporal = nodoTemporal->nodoAnterior;
                }
            } else {
                printf("La lista esta vacia\n");
            }
            
        } else {
            printf("Opcion incorrecta\n");
        }
    } while (opcion != 4);


    return 0;
}
