#include "lista.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} Nodo;

struct lista {
	Nodo *primer_nodo;
};

Lista *lista_crear()
{
	Lista *lista = malloc(sizeof(Lista));
	lista->primer_nodo = NULL;
	return lista;
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (!lista->primer_nodo || !lista)
		return 0;
	Nodo *actual = lista->primer_nodo;
	size_t contador = 0;
	while (actual != NULL) {
		actual = actual->siguiente;
		contador++;
	}
	return contador;
}

void lista_destruir(Lista *lista)
{
	if (!lista)
		return;
	free(lista);
}
