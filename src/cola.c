#include "cola.h"
#include "lista.h"

struct cola {
	Lista *lista;
};

Cola *cola_crear()
{
	Cola *cola = malloc(sizeof(struct cola));
	cola->lista = lista_crear();
	return cola;
}

size_t cola_cantidad(Cola *cola)
{
	if (!cola)
		return 0;
	return lista_cantidad_elementos(cola->lista);
}

void *cola_frente(Cola *cola)
{
	if (!cola)
		return NULL;
	void *elemento_tope = NULL;
	if (lista_obtener_elemento(cola->lista, 1, &elemento_tope))
		return elemento_tope;
	else
		return NULL;
}

bool cola_encolar(Cola *cola, void *cosa)
{
	if (!cola || !cosa)
		return false;
	if (lista_agregar_al_final(cola->lista, cosa))
		return true;
	else
		return false;
}

void *cola_desencolar(Cola *cola)
{
	if (!cola)
		return NULL;
	void *elemento_desapilado = NULL;
	if (lista_quitar_elemento(cola->lista, 1, &elemento_desapilado))
		return elemento_desapilado;
	else
		return NULL;
}

bool cola_esta_vacía(Cola *cola)
{
	if (!cola)
		return true;
	if (lista_cantidad_elementos(cola->lista) == 0)
		return true;
	else
		return false;
}

void cola_destruir_todo(Cola *cola, void (*f)(void *)){
	lista_destruir_todo(cola->lista,f);
	free(cola);
}

void cola_destruir(Cola *cola)
{
	lista_destruir(cola->lista);
	free(cola);
}