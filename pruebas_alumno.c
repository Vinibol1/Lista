#include "pa2m.h"
#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
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
struct cola {
	Lista *lista;
};

struct lista_iterador {
	Nodo *nodo;
};

bool sumar_2(void *elemento, void *ctx)
{
	int *tmp = elemento;
	*tmp += 2;
	return true;
}
bool sumar_2_excepto_4(void *elemento, void *ctx)
{
	int *tmp = elemento;
	if (*tmp == 4)
		return false;

	*tmp += 2;
	return true;
}

int comparador(void *elem_actual, void *buscado)
{
	if (elem_actual == NULL) {
		return -1;
	}

	return strcmp(elem_actual, buscado);
}

void lista_crear_prueba()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "lista se creo correctamente");
	lista_destruir(lista);
}

void lista_cantidad_elem_vacio()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0,
		     "lista vacia devuelve 0");
	lista_destruir(lista);
}

void lista_cantidad_elem()
{
	Lista *lista = lista_crear();
	int num = 5;
	int num3 = 4;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num3);
	pa2m_afirmar(lista_cantidad_elementos(lista) == 2,
		     "lista con 2 nodos devuelve 2");
	lista_destruir(lista);
}

void lista_cantidad_NULL()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista_cantidad_elementos(NULL) == 0,
		     "lista NULL devuelve 0");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0,
		     "lista sin primer nodo devuelve 0");
	lista_destruir(lista);
}

void lista_agregar_elem_final()
{
	Lista *lista = lista_crear();
	int num2 = 7;
	lista_agregar_al_final(lista, &num2);
	int *tmp = lista->primer_nodo->elemento;
	pa2m_afirmar(*tmp == 7, "lista agregar 7 final agrega 7");
	pa2m_afirmar(lista_agregar_al_final(NULL, &num2) == false,
		     "lista NULL devuelve false");
	lista_destruir(lista);
}

void lista_agregar_elem()
{
	Lista *lista = lista_crear();

	int num = 5;
	int num2 = 7;
	lista_agregar_al_final(lista, &num);
	lista_agregar_elemento(lista, 0, &num2);

	int *tmp2 = lista->ultimo_nodo->elemento;
	void *elem_buscado = NULL;
	lista_obtener_elemento(lista, 0, &elem_buscado);
	int *ints = elem_buscado;
	pa2m_afirmar(ints == &num2,
		     "agregar en posicion 0 se obtiene en posicion 0");
	pa2m_afirmar(*tmp2 == 5, "el ultimo nodo apunta correctamente");
	lista_destruir(lista);
}

void lista_quitar_elem()
{
	Lista *lista = lista_crear();
	int num = 5;
	int num2 = 7;
	int num3 = 4;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	printf("%li", lista->tamaño);
	void *elem_quitado = NULL;
	lista_quitar_elemento(lista, 2, &elem_quitado);
	int *asd = lista->primer_nodo->siguiente->elemento;
	int *asd2 = elem_quitado;
	pa2m_afirmar(*asd == 7, "El elemento se quito correctamente");
	pa2m_afirmar(*asd2 == 4, "El elemento_quitado se guardo correctamente");
	pa2m_afirmar(lista_quitar_elemento(NULL, 3, &elem_quitado) == false,
		     "si paso lista NULL devuelve false");
	pa2m_afirmar(lista_quitar_elemento(lista, 7, &elem_quitado) == false,
		     "si paso posicion mas alta devuelve false");
	pa2m_afirmar(lista_quitar_elemento(lista, 0, NULL) == true,
		     "si paso void** NULL devuelve false");
	lista_destruir(lista);
}

void lista_vaciar_final()
{
	Lista *lista = lista_crear();
	int num = 5;
	int num2 = 7;
	int num3 = 4;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	void *elem_quitado = NULL;
	while (lista->tamaño > 0) {
		lista_quitar_elemento(lista, lista->tamaño - 1, &elem_quitado);
	}
	pa2m_afirmar(lista->primer_nodo == NULL,
		     "lista se vacio correctamente");

	lista_destruir(lista);
}

void lista_vaciar_principio()
{
	Lista *lista = lista_crear();
	int num = 5;
	int num2 = 7;
	int num3 = 4;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	void *elem_quitado = NULL;
	while (lista->tamaño > 0) {
		lista_quitar_elemento(lista, 0, &elem_quitado);
	}
	pa2m_afirmar(lista->primer_nodo == NULL,
		     "lista se vacio correctamente");

	lista_destruir(lista);
}

void lista_buscar_elem()
{
	Lista *lista = lista_crear();
	char num[4] = "asd";
	char num2[3] = "as";
	char num3[4] = "dsa";
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	char *busc = "dsa";
	char *busc2 = "ads";
	char *busc3 = "asd";

	char *encontro = lista_buscar_elemento(lista, busc, comparador);
	char *encontro1 = lista_buscar_elemento(lista, busc3, comparador);
	pa2m_afirmar(strcmp(encontro, busc) == 0,
		     "El ultimo elemento se encontro correctamente");
	pa2m_afirmar(strcmp(encontro1, busc3) == 0,
		     "El primer elemento se encontro correctamente");
	pa2m_afirmar(lista_buscar_elemento(lista, busc2, comparador) == NULL,
		     "si elemento no existe devuelve NULL");
	pa2m_afirmar(lista_buscar_elemento(lista, busc, NULL) == NULL,
		     "si comparador NUll devuelve NULL");
	lista_destruir(lista);
}

void lista_obtener_elem()
{
	Lista *lista = lista_crear();
	int num = 5;
	int num2 = 7;
	int num3 = 4;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	void *elem_buscado = NULL;
	lista_obtener_elemento(lista, 2, &elem_buscado);
	int *asd = elem_buscado;
	pa2m_afirmar(asd == &num3, "El elemento se guardo correctamente");
	pa2m_afirmar(lista_obtener_elemento(NULL, 3, &elem_buscado) == false,
		     "si paso lista NULL devuelve false");
	pa2m_afirmar(lista_obtener_elemento(lista, 7, &elem_buscado) == false,
		     "si paso posicion mas alta devuelve false");
	pa2m_afirmar(lista_obtener_elemento(lista, 2, NULL) == true,
		     "si paso void** NULL devuelve true");
	lista_destruir(lista);
}

void lista_iterar_elem()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);

	pa2m_afirmar(lista_iterar_elementos(lista, sumar_2, NULL) == 3,
		     "itero 3 veces devuelve 3");
	pa2m_afirmar(num2 == 8, "se sumo 2 correctamente a nodo medio");
	pa2m_afirmar(num3 == 9, "se sumo 2 correctamente a nodo final");
	pa2m_afirmar(lista_iterar_elementos(lista, sumar_2_excepto_4, NULL) ==
			     1,
		     "itero 1 veces devuelve 1");
	lista_destruir(lista);
}

void agregar_quitar_iterar()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	void *elem_quitado1 = NULL;
	void *elem_quitado2 = NULL;
	void *elem_quitado3 = NULL;
	lista_quitar_elemento(lista, lista->tamaño - 1, &elem_quitado1);
	pa2m_afirmar(elem_quitado1 == &num3,
		     "elemento quitado es igual elemennto agregador");
	lista_quitar_elemento(lista, lista->tamaño - 1, &elem_quitado2);
	pa2m_afirmar(elem_quitado2 == &num2,
		     "elemento quitado es igual elemennto agregador");
	lista_quitar_elemento(lista, lista->tamaño - 1, &elem_quitado3);
	pa2m_afirmar(elem_quitado3 == &num,
		     "elemento quitado es igual elemennto agregador");
	lista_agregar_al_final(lista, elem_quitado3);
	lista_agregar_al_final(lista, elem_quitado2);
	lista_agregar_al_final(lista, elem_quitado1);
	pa2m_afirmar(lista_iterar_elementos(lista, sumar_2, NULL) == 3,
		     "itero 3 veces devuelve 3");
	pa2m_afirmar(num2 == 8, "se sumo 2 correctamente a nodo medio");
	pa2m_afirmar(num3 == 9, "se sumo 2 correctamente a nodo final");
	pa2m_afirmar(lista_iterar_elementos(lista, sumar_2_excepto_4, NULL) ==
			     1,
		     "itero 1 veces devuelve 1");
	lista_destruir(lista);
}

void lista_iterador_crear_prueba()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	Lista_iterador *lista_iterador = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador != NULL, "iterador se creo correctamente");
	lista_destruir(lista);
	lista_iterador_destruir(lista_iterador);
}

void lista_iterador_avanzar_prueba()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	Lista_iterador *lista_iterador = lista_iterador_crear(lista);
	lista_iterador_avanzar(lista_iterador);
	pa2m_afirmar(lista_iterador->nodo == lista->primer_nodo->siguiente,
		     "iterador avanzo correctamente");
	lista_destruir(lista);
	lista_iterador_destruir(lista_iterador);
}

void lista_iterador_hay_siguiente_prueba()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista, &num);
	lista_agregar_al_final(lista, &num2);
	lista_agregar_al_final(lista, &num3);
	Lista_iterador *lista_iterador = lista_iterador_crear(lista);
	lista_iterador_hay_siguiente(lista_iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(lista_iterador) == true,
		     "en posicion 1 de 3 hay siguiente y devuelve true");
	lista_iterador_avanzar(lista_iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(lista_iterador) == true,
		     "en posicion 2 de 3 hay siguiente y devuelve true");
	lista_iterador_avanzar(lista_iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(lista_iterador) == true,
		     "en posicion 3 de 3 hay siguiente y devuelve true");
	lista_destruir(lista);
	lista_iterador_destruir(lista_iterador);
}

void pila_Crear_prueba()
{
	Pila *pila = pila_crear();
	pa2m_afirmar(pila != NULL, "pila se creo correctamente");
	pila_destruir(pila);
}
void pila_apilar_prueba()
{
	Pila *pila = pila_crear();
	int num = 5;
	pa2m_afirmar(pila_apilar(pila, &num) == true,
		     "pila apilo correctamente y devuelve true");
	int *num2 = pila_tope(pila);
	pa2m_afirmar(*num2 == num, "pila apilo correctamente el elemento num");
	pila_destruir(pila);
}

void pila_desapilar_prueba()
{
	Pila *pila = pila_crear();
	int num = 5;
	int num2 = 7;
	pila_apilar(pila, &num);
	pila_apilar(pila, &num2);
	int *desapilado = pila_desapilar(pila);
	int *num3 = pila_tope(pila);
	pa2m_afirmar(*num3 = num,
		     "pila desapilo correctamente el elemento num2");
	pa2m_afirmar(*desapilado = num2, "el elemento desapilado es el pedido");
	pila_destruir(pila);
}

void pila_vacia_prueba()
{
	Pila *pila = pila_crear();
	int num = 3;
	pa2m_afirmar(pila_esta_vacía(pila) == true, "pila vacia devuelve true");
	pila_apilar(pila, &num);
	pa2m_afirmar(pila_esta_vacía(pila) == false,
		     "pila no vacia devuelve false");
	pila_destruir(pila);
}

void cola_crear_prueba()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola != NULL, "Cola se creo correctamente");
	cola_destruir(cola);
}

void cola_encolar_prueba()
{
	Cola *cola = cola_crear();
	int num = 5;
	pa2m_afirmar(cola_encolar(cola, &num) == true,
		     "Cola se enolo correctamente");
	int *num2 = cola_frente(cola);
	pa2m_afirmar(*num2 = 5, "Cola se posiciono elemento correctamente");
	cola_destruir(cola);
}
void cola_desencolar_prueba()
{
	Cola *cola = cola_crear();
	int num = 5;
	cola_encolar(cola, &num);
	int *num2 = cola_desencolar(cola);
	pa2m_afirmar(cola_cantidad(cola) == 0, "Cola desencolo correctamente");
	pa2m_afirmar(*num2 = 5,
		     "Cola guardo elemento desencolado correctamente");
	cola_destruir(cola);
}

void cola_frente_prueba()
{
	Cola *cola = cola_crear();
	int num = 5;
	int num2 = 7;
	int num3 = 10;
	cola_encolar(cola, &num);
	cola_encolar(cola, &num2);
	cola_encolar(cola, &num3);
	int *num4 = cola_frente(cola);
	pa2m_afirmar(*num4 = 5, "Cola frente devuelve 5");

	cola_destruir(cola);
}

void cola_vacia_prueba()
{
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_esta_vacía(cola) == true, "Cola vacia devuelve true");
	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("Lista crear");
	lista_crear_prueba();
	pa2m_nuevo_grupo("Lista cantidad");
	lista_cantidad_elem_vacio();
	lista_cantidad_elem();
	lista_cantidad_NULL();
	pa2m_nuevo_grupo("Lista agregar");
	lista_agregar_elem_final();
	lista_agregar_elem();
	pa2m_nuevo_grupo("Lista quitar");
	lista_quitar_elem();
	pa2m_nuevo_grupo("Lista buscar");
	lista_buscar_elem();
	pa2m_nuevo_grupo("Lista obtener");
	lista_obtener_elem();
	pa2m_nuevo_grupo("Lista vaciar");
	lista_vaciar_principio();
	lista_vaciar_final();
	pa2m_nuevo_grupo("Lista iterar inter");
	lista_iterar_elem();
	pa2m_nuevo_grupo("Lista iterar externo");
	lista_iterador_crear_prueba();
	lista_iterador_avanzar_prueba();
	lista_iterador_hay_siguiente_prueba();
	pa2m_nuevo_grupo("Pila");
	pila_Crear_prueba();
	pila_apilar_prueba();
	pila_desapilar_prueba();
	pila_vacia_prueba();
	pa2m_nuevo_grupo("Cola");
	cola_crear_prueba();
	cola_encolar_prueba();
	cola_desencolar_prueba();
	cola_vacia_prueba();
	cola_frente_prueba();
	agregar_quitar_iterar();

	return pa2m_mostrar_reporte();
}
