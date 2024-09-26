#include "pila.h"
#include "lista.h"
struct pila {
	Lista *lista;
};

Pila *pila_crear()
{
	Pila *pila = malloc(sizeof(pila));
	if (!pila)
		return NULL;
	pila->lista = lista_crear();
	if (!pila->lista) {
		free(pila);
		return NULL;
	}

	return pila;
}

void pila_destruir(Pila *pila)
{
	if (!pila)
		return;

	lista_destruir(pila->lista);
	free(pila);
}

size_t pila_cantidad(Pila *pila)
{
	if (!pila)
		return 0;
	return lista_cantidad_elementos(pila->lista);
}

void *pila_tope(Pila *pila)
{
	if (!pila)
		return NULL;
	void *elemento_tope = NULL;
	if (lista_obtener_elemento(pila->lista, 1, &elemento_tope))
		return elemento_tope;
	else
		return NULL;
}

bool pila_apilar(Pila *pila, void *cosa)
{
	if (!pila || !cosa)
		return false;
	return lista_agregar_elemento(pila->lista, 1, cosa);
}

void *pila_desapilar(Pila *pila)
{
	if (!pila)
		return NULL;
	void *elemento_desapilado = NULL;
	if (lista_quitar_elemento(pila->lista, 1, &elemento_desapilado))
		return elemento_desapilado;
	else
		return NULL;
}

bool pila_esta_vacía(Pila *pila)
{
	if (!pila)
		return true;
	if (lista_cantidad_elementos(pila->lista) == 0)
		return true;
	else
		return false;
}

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	if (!pila || !f)
		return;

	lista_destruir_todo(pila->lista, f);
	free(pila);
}