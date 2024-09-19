#include "pa2m.h"
#include "src/lista.h"
#include "string.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} Nodo;
struct lista {
	Nodo *primer_nodo;
};

struct lista_iterador {
	Lista *lista;
	Nodo *nodo;
};

bool sumar_2(void *elemento, void *ctx){
	int *tmp = elemento;
	*tmp += 2;
	return true;
}
bool sumar_2_excepto_4(void *elemento, void *ctx){
	int *tmp = elemento;
	if (*tmp == 4)
		return false;
	
	
	*tmp += 2;
	return true;
}

int comparador(void *elem_actual, void *buscado){

	if (elem_actual == NULL)
	{
		return -1;
	}
	
	return strcmp(elem_actual,buscado);
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
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0, "lista vacia devuelve 0");
	lista_destruir(lista);
}

void lista_cantidad_elem()
{
	Lista *lista = lista_crear();
	Nodo nodo;
	Nodo nodo2;
	Nodo nodo3;
	nodo.siguiente = &nodo2;
	nodo2.siguiente = &nodo3;
	nodo3.siguiente = NULL;
	lista->primer_nodo = &nodo;
	pa2m_afirmar(lista_cantidad_elementos(lista) == 3, "lista con 3 nodos devuelve 3");
	lista_destruir(lista);
}

void lista_cantidad_NULL()
{
	Lista *lista = lista_crear();
	pa2m_afirmar(lista_cantidad_elementos(NULL) == 0, "lista NULL devuelve 0");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0, "lista sin primer nodo devuelve 0");
	lista_destruir(lista);
}

void lista_agregar_elem_final()
{
	Lista *lista = lista_crear();
	int num2 = 7;
	lista_agregar_al_final(lista,&num2);
	int *tmp = lista->primer_nodo->elemento;
	pa2m_afirmar(*tmp == 7, "lista agregar 7 final agrega 7");
	pa2m_afirmar(lista_agregar_al_final(NULL,&num2) == false, "lista NULL devuelve false");
	pa2m_afirmar(lista_agregar_al_final(lista,NULL) == false, "cosa NULL devuelve false");
	lista_destruir(lista);
}

void lista_agregar_elem()
{
	Lista *lista = lista_crear();

	int num = 5;
	int num2 = 7;
	int num3 = 4;
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num3);
	lista_agregar_elemento(lista,2,&num2);
	int *tmp = lista->primer_nodo->siguiente->elemento;
	pa2m_afirmar(*tmp == 7, "lista agregar 7 en segunda posicion agrega 7");
	lista_destruir(lista);
}

void lista_quitar_elem()
{
	Lista *lista = lista_crear();
	int num = 5;
	int num2 = 7;
	int num3 = 4;
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num2);
	lista_agregar_al_final(lista,&num3);
	void *elem_quitado = NULL;
	lista_quitar_elemento(lista,2,&elem_quitado);
	int *asd = lista->primer_nodo->siguiente->elemento;
	Nodo *nodo_quitado = elem_quitado;
	int *asd2 = nodo_quitado->elemento;
	pa2m_afirmar(*asd == 4, "El elemento se quito correctamente");
	pa2m_afirmar(*asd2 == 7, "El elemento_quitado se guardo correctamente");
	pa2m_afirmar(lista_quitar_elemento(NULL,3,&elem_quitado) == false, "si paso lista NULL devuelve false");
	pa2m_afirmar(lista_quitar_elemento(lista,7,&elem_quitado) == false, "si paso posicion mas alta devuelve false");
	pa2m_afirmar(lista_quitar_elemento(lista,3,NULL) == false, "si paso void** NULL devuelve false");
	free(elem_quitado);
	lista_destruir(lista);
}

void lista_buscar_elem()
{
	Lista *lista = lista_crear();
	char num[4] = "asd";
	char num2[3] = "as";
	char num3[4] = "dsa";
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num2);
	lista_agregar_al_final(lista,&num3);
	char *busc = "asd";
	char *busc2 = "ads";
	
	char *encontro = lista_buscar_elemento(lista,busc,comparador);
	pa2m_afirmar(strcmp(encontro,busc) == 0, "El elemento se encontro correctamente");
	pa2m_afirmar(lista_buscar_elemento(lista,busc2,comparador) == NULL, "si elemento no existe devuelve NULL");
	pa2m_afirmar(lista_buscar_elemento(lista,busc,NULL) == NULL, "si comparador NUll devuelve NULL");
	lista_destruir(lista);
}

void lista_obtener_elem()
{
	Lista *lista = lista_crear();
	int num = 5;
	int num2 = 7;
	int num3 = 4;
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num2);
	lista_agregar_al_final(lista,&num3);
	void *elem_buscado = NULL;
	lista_obtener_elemento(lista,3,&elem_buscado);
	int *asd = elem_buscado;
	pa2m_afirmar(*asd == 4, "El elemento se guardo correctamente");
	pa2m_afirmar(lista_obtener_elemento(NULL,3,&elem_buscado) == false, "si paso lista NULL devuelve false");
	pa2m_afirmar(lista_obtener_elemento(lista,7,&elem_buscado) == false, "si paso posicion mas alta devuelve false");
	pa2m_afirmar(lista_obtener_elemento(lista,3,NULL) == false, "si paso void** NULL devuelve false");
	lista_destruir(lista);
}

void lista_iterar_elem()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num2);
	lista_agregar_al_final(lista,&num3);

	pa2m_afirmar(lista_iterar_elementos(lista,sumar_2,NULL) == 3, "itero 3 veces devuelve 3");
	pa2m_afirmar(num2 == 8, "se sumo 2 correctamente a nodo medio");
	pa2m_afirmar(num3 == 9, "se sumo 2 correctamente a nodo final");
	pa2m_afirmar(lista_iterar_elementos(lista,sumar_2_excepto_4,NULL) == 1, "itero 1 veces devuelve 1");
	lista_destruir(lista);
}

void lista_iterador_crear_prueba()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num2);
	lista_agregar_al_final(lista,&num3);
	Lista_iterador *lista_iterador = lista_iterador_crear(lista);
	pa2m_afirmar(lista_iterador != NULL, "iterador se creo correctamente");
	pa2m_afirmar(lista_iterador->lista != NULL, "iterador.lista se creo correctamente");
	lista_destruir(lista);
	lista_iterador_destruir(lista_iterador);
}

void lista_iterador_avanzar_prueba()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num2);
	lista_agregar_al_final(lista,&num3);
	Lista_iterador *lista_iterador = lista_iterador_crear(lista);
	lista_iterador_avanzar(lista_iterador);
	pa2m_afirmar(lista_iterador->nodo == lista->primer_nodo->siguiente, "iterador avanzo correctamente");
	pa2m_afirmar(lista_iterador->lista != NULL, "iterador.lista se creo correctamente");
	lista_destruir(lista);
	lista_iterador_destruir(lista_iterador);
}

void lista_iterador_hay_siguiente_prueba()
{
	Lista *lista = lista_crear();
	int num = 2;
	int num2 = 6;
	int num3 = 7;
	lista_agregar_al_final(lista,&num);
	lista_agregar_al_final(lista,&num2);
	lista_agregar_al_final(lista,&num3);
	Lista_iterador *lista_iterador = lista_iterador_crear(lista);
	lista_iterador_hay_siguiente(lista_iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(lista_iterador) == true, "en posicion 1 de 3 hay siguiente y devuelve true");
	lista_iterador_avanzar(lista_iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(lista_iterador) == true, "en posicion 2 de 3 hay siguiente y devuelve true");
	lista_iterador_avanzar(lista_iterador);
	pa2m_afirmar(lista_iterador_hay_siguiente(lista_iterador) == false, "en posicion 3 de 3 no hay siguiente y devuelve false");
	lista_destruir(lista);
	lista_iterador_destruir(lista_iterador);
}


int main()
{
	pa2m_nuevo_grupo("Lista");
	lista_crear_prueba();
	lista_cantidad_elem_vacio();
	lista_cantidad_elem();
	lista_cantidad_NULL();
	lista_agregar_elem_final();
	lista_agregar_elem();
	lista_quitar_elem();
	lista_buscar_elem();
	lista_obtener_elem();
	lista_iterar_elem();
	lista_iterador_crear_prueba();
	lista_iterador_avanzar_prueba();
	lista_iterador_hay_siguiente_prueba();

	return pa2m_mostrar_reporte();
}
