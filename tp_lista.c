#include <stdlib.h>
#include <string.h>
#include "src/lista.h"
#include "src/csv.h"
#include <stdio.h>

#define ERROR -1

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};



int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;
	if (!p1->nombre || !p2->nombre) {
		printf("error");
	}

	return strcmp(p1->nombre, p2->nombre);
}

bool leer_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool leer_caracter(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}

int main(int argc, char *argv[])
{
	struct archivo_csv *archivo = abrir_archivo_csv("pokedex.csv", ';');
	struct pokemon *pokemon;

	Lista *pokedex = lista_crear();
	if (!archivo)
		return ERROR;

	bool (*funciones[5])(const char *, void *) = { crear_string_nuevo,
						       leer_caracter, leer_int,
						       leer_int, leer_int };
	char *nombre = NULL;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
	void *punteros[5] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };
	int contador = 0;
	while (leer_linea_csv(archivo, 5, funciones, punteros) == 5) {
		pokemon = malloc(sizeof(struct pokemon));
		pokemon->nombre = nombre;
		pokemon->tipo = tipo;
		pokemon->fuerza = fuerza;
		pokemon->destreza = destreza;
		pokemon->resistencia = resistencia;
		lista_agregar_al_final(pokedex, pokemon);
		contador++;
	}

	int opcion;
	bool es_correcto = false;
	while (!es_correcto) {
		printf("Elegir una opcion\n. Ingrear por teclado un nombre y el programa busca el pokemon en la lista \n2. Listar todos los pokemones de la pokedex\n");
		scanf("%i", &opcion);
		Lista_iterador *iterador;
		switch (opcion) {
		case 1:
			char pokemon_buscado;
			printf("escribí el nombre del pokemon que vas a buscar: ");
			scanf("%s", &pokemon_buscado);
			struct pokemon pokemon2;
			pokemon2.nombre = &pokemon_buscado;

			for (iterador = lista_iterador_crear(pokedex);
			     lista_iterador_hay_siguiente(iterador);
			     lista_iterador_avanzar(iterador)) {
				struct pokemon *pokemon_actual =
					lista_iterador_obtener_elemento_actual(
						iterador);

				if (comparar_nombre_pokemon(pokemon_actual,
							    &pokemon2) == 0)
					printf("Nombre:%s, Tipo:%c, Fuerza:%i, Destreza:%i, Resistencia:%i\n",
					       pokemon_actual->nombre,
					       pokemon_actual->tipo,
					       pokemon_actual->fuerza,
					       pokemon_actual->destreza,
					       pokemon_actual->resistencia);
			}
			es_correcto = true;
			break;
		case 2:
			for (iterador = lista_iterador_crear(pokedex);
			     lista_iterador_hay_siguiente(iterador);
			     lista_iterador_avanzar(iterador)) {
				struct pokemon *pokemon_actual;
				pokemon_actual =
					lista_iterador_obtener_elemento_actual(
						iterador);
				printf("%s\n", pokemon_actual->nombre);
			}
			es_correcto = true;
			break;

		default:
			printf("Numero no valido ingresado, por favor ingrese 1 o 2\n");
			break;
		}
	}
}
// 	scanf("%i")
// 		//recibir un archivo por linea de comandos
// 		//abrir el archivo csv y parsear pokemones
// 		//agregar los pokemones a una lista
// 		//
// 		//El usuario puede elegir una de dos opciones
// 		//
// 		//1. Ingrear por teclado un nombre y el programa busca el pokemon en la lista
// 		//2. Listar todos los pokemones de la pokedex
// 		//
// 		//
// 		struct pokemon p1;
// 	struct pokemon p2;
// 	//obvio que los inicializo

// 	Lista *pokedex = lista_crear();

// 	//agregar_pokemon_desde_archivo(pokedex, "poke.csv");

// 	lista_agregar_al_final(pokedex, &p1);
// 	lista_agregar_al_final(pokedex, &p2);

// 	struct pokemon buscado = { .nombre = "Pikachu" };
// 	struct pokemon *encontrado = lista_buscar_elemento(
// 		pokedex, &buscado, comparar_nombre_pokemon);

// 	//struct pokemon *quitado;
// 	//lista_quitar_elemento(pokedex, 1 , (void**)&quitado);

// 	struct pokemon *en_posicion;
// 	lista_obtener_elemento(pokedex, 1, (void **)&en_posicion);

// 	//Recorrer lista
// 	//Posibilidad 1
// 	//1+2+3+4+5+6.....+n-1+n
// 	//puede ser O(n), O(n²) para enlazada
// 	for (size_t i = 0; //O(1)
// 	     i < lista_cantidad_elementos(pokedex); //O(1)
// 	     i++) { //O(1)
// 		struct pokemon *p;
// 		lista_obtener_elemento(pokedex, i, (void **)&p); //O(n)
// 		///hacer algo
// 	}

// 	//Recorrer lista
// 	//Posibilidad 2
// 	void *ctx = NULL;
// 	//O(n)
// 	lista_iterar_elementos(pokedex, hacer_algo, ctx);

// 	//Recorrer lista
// 	//Posibilidad 3
// 	//TDA iterador externo
// 	Lista_iterador *i;
// 	for (i = lista_iterador_crear(pokedex); //O(1)
// 	     lista_iterador_hay_siguiente(i); //O(1)
// 	     lista_iterador_avanzar(i)) { //O(1)
// 		struct pokemon *p;
// 		p = lista_iterador_obtener_elemento_actual(i); //O(1)
// 		///hacer algo
// 	}

// 	//lista_iterar_elementos(pokedex, liberar_pokemon, NULL);
// 	//lista_destruir(pokedex);
// 	lista_destruir_todo(pokedex, liberar_pokemon);
// 	return 0;
// }
