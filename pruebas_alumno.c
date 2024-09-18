#include "pa2m.h"
#include "src/lista.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} Nodo;
struct lista {
	Nodo *primer_nodo;
};


void lista_crear_prueba()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "lista se creo correctamente");
	lista_destruir(lista);
}

void lista_cantidad_elem_vacio()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0, "lista vacia devuelve 0");
	lista_destruir(lista);
}

void lista_cantidad_elem()
{
	Lista *lista = lista_crear();
	Nodo nodo;
	Nodo nodo2;
	nodo.siguiente = &nodo2;
	nodo2.siguiente = NULL;
	lista->primer_nodo = &nodo;
	pa2m_afirmar(lista_cantidad_elementos(lista) == 2, "lista con 2 nodos devuelve 2");
	lista_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo("Lista");
	lista_crear_prueba();
	lista_cantidad_elem_vacio();
	lista_cantidad_elem();

	return pa2m_mostrar_reporte();
}
