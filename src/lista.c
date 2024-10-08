#include "lista.h"
#include "stdio.h"
#include "string.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} Nodo;

struct lista {
	Nodo *primer_nodo;
	Nodo *ultimo_nodo;
	size_t tamaño;
};

struct lista_iterador {
	Nodo *nodo;
};

Lista *lista_crear()
{
	Lista *lista = malloc(sizeof(Lista));
	if (!lista)
		return NULL;

	lista->primer_nodo = NULL;
	lista->ultimo_nodo = NULL;
	lista->tamaño = 0;
	return lista;
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (!lista)
		return 0;
	return lista->tamaño;
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
	if (!lista)
		return false;
	Nodo *nuevo_nodo = malloc(sizeof(struct nodo));
	if (!nuevo_nodo) {
		return false;
	}

	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->elemento = cosa;
	lista->tamaño++;

	if (lista->primer_nodo == NULL) {
		lista->primer_nodo = nuevo_nodo;
		lista->ultimo_nodo = nuevo_nodo;
	} else {
		lista->ultimo_nodo->siguiente = nuevo_nodo;
		lista->ultimo_nodo = nuevo_nodo;
	}
	return true;
}

bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (!lista)
		return false;

	if (posicion > lista->tamaño)
		return false;
	lista->tamaño++;
	int contador = 0;
	Nodo *nuevo_nodo = NULL, *temporal = NULL, *temporal2 = NULL;
	nuevo_nodo = malloc(sizeof(struct nodo));
	if (!nuevo_nodo)
		return false;

	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->elemento = cosa;
	temporal = lista->primer_nodo;
	if (posicion == 0) {
		nuevo_nodo->siguiente = temporal;
		lista->primer_nodo = nuevo_nodo;
	} else {
		while ((temporal != NULL) && (contador < posicion)) {
			contador++;
			temporal2 = temporal;
			temporal = temporal->siguiente;
		}
		temporal2->siguiente = nuevo_nodo;
		nuevo_nodo->siguiente = temporal;
	}
	if (posicion == lista->tamaño)
		lista->ultimo_nodo = nuevo_nodo;
	return true;
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (!lista || !lista->primer_nodo || posicion > lista->tamaño - 1)
		return false;
	lista->tamaño -= 1;
	int contador = 0;
	Nodo *temporal = NULL, *temporal2 = NULL;
	temporal = lista->primer_nodo;
	if (posicion == 0) {
		lista->primer_nodo = lista->primer_nodo->siguiente;
		if (elemento_quitado && temporal->elemento)
			*elemento_quitado = temporal->elemento;
		free(temporal);
		return true;
	} else {
		while ((temporal != NULL) && (contador < posicion)) {
			contador++;
			temporal2 = temporal;
			temporal = temporal->siguiente;
		}
		if (posicion == lista->tamaño)
			lista->ultimo_nodo = temporal2;

		temporal2->siguiente = temporal->siguiente;
		if (elemento_quitado && temporal->elemento)
			*elemento_quitado = temporal->elemento;
		free(temporal);
	}
	return true;
}

void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
	if (!lista || !buscado || !comparador)
		return NULL;
	Nodo *actual = lista->primer_nodo;
	int es_igual = 1;
	int contador = 0;
	while (es_igual != 0 && contador < lista->tamaño) {
		es_igual = comparador(actual->elemento, buscado);
		if (es_igual != 0)
			actual = actual->siguiente;
		contador++;
	}
	if (es_igual != 0)
		return NULL;

	return actual->elemento;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	if (!lista || posicion >= lista->tamaño || !lista->primer_nodo)
		return false;
	Nodo *actual = lista->primer_nodo;
	if (posicion == 0) {
		if (elemento_encontrado)
			*elemento_encontrado = actual->elemento;

		return true;
	}
	if (posicion == lista->tamaño) {
		if (elemento_encontrado)
			*elemento_encontrado = lista->ultimo_nodo->elemento;
		return true;
	}

	for (size_t i = 0; i < posicion; i++) {
		actual = actual->siguiente;
	}
	if (elemento_encontrado)
		*elemento_encontrado = actual->elemento;
	return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (!lista || !f || !lista->primer_nodo)
		return 0;
	Nodo *actual = lista->primer_nodo;
	size_t contador = 1;
	while (f(actual->elemento, ctx) && actual->siguiente) {
		actual = actual->siguiente;
		contador++;
	}
	return contador;
}

Lista_iterador *lista_iterador_crear(Lista *lista)
{
	if (!lista)
		return NULL;
	Lista_iterador *lista_iterador = malloc(sizeof(struct lista_iterador));
	if (!lista_iterador)
		return NULL;

	lista_iterador->nodo = lista->primer_nodo;
	return lista_iterador;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador)
{
	if (!iterador)
		return false;
	if (iterador->nodo)
		return true;
	return false;
}

void lista_iterador_avanzar(Lista_iterador *iterador)
{
	if (!iterador)
		return;
	if (lista_iterador_hay_siguiente(iterador))
		iterador->nodo = iterador->nodo->siguiente;
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador)
{
	if (!iterador || !iterador->nodo)
		return NULL;
	return iterador->nodo->elemento;
}

void lista_iterador_destruir(Lista_iterador *iterador)
{
	if (!iterador)
		return;
	free(iterador);
}

void lista_destruir(Lista *lista)
{
	if (!lista)
		return;
	Nodo *temporal = NULL;
	for (size_t i = 0; i < lista->tamaño; i++) {
		temporal = NULL;
		temporal = lista->primer_nodo;
		lista->primer_nodo = lista->primer_nodo->siguiente;
		free(temporal);
	}
	free(lista);
}
void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (!lista)
		return;
	Nodo *actual = NULL;
	for (size_t i = 0; i < lista->tamaño; i++) {
		actual = lista->primer_nodo;
		if (destructor)
			destructor(actual->elemento);
		lista->primer_nodo = lista->primer_nodo->siguiente;
		free(actual);
	}
	free(lista);
}