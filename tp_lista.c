#include <stdlib.h>
#include <string.h>
#include "src/lista.h"
#include "src/csv.h"
#include <stdio.h>

#define ERROR -1
#define VALOR_MAXIMO 300
#define COLUMNAS 5

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
	return strcmp(p1->nombre, p2->nombre);
}

struct pokemon *comparar_pokemones_en_lista(Lista *pokedex)
{
	Lista_iterador *iterador;
	char pokemon_buscado[VALOR_MAXIMO];
	printf("escribí el nombre del pokemon que vas a buscar: ");
	if (scanf("%s", pokemon_buscado) == EOF)
		return NULL;
	struct pokemon pokemon2;
	pokemon2.nombre = pokemon_buscado;
	struct pokemon *pokemon_actual;
	for (iterador = lista_iterador_crear(pokedex);
	     lista_iterador_hay_siguiente(iterador);
	     lista_iterador_avanzar(iterador)) {
		pokemon_actual =
			lista_iterador_obtener_elemento_actual(iterador);

		if (comparar_nombre_pokemon(pokemon_actual, &pokemon2) == 0) {
			lista_iterador_destruir(iterador);
			return pokemon_actual;
		}
	}
	pokemon_actual = lista_iterador_obtener_elemento_actual(iterador);
	lista_iterador_destruir(iterador);
	if (comparar_nombre_pokemon(pokemon_actual, &pokemon2) == 0)
		return pokemon_actual;
	return NULL;
}

void imprimir_pokemones_por_pantalla(Lista *pokedex)
{
	if (!pokedex)
		return;
	Lista_iterador *iterador;
	struct pokemon *pokemon_actual;
	for (iterador = lista_iterador_crear(pokedex);
	     lista_iterador_hay_siguiente(iterador);
	     lista_iterador_avanzar(iterador)) {
		pokemon_actual =
			lista_iterador_obtener_elemento_actual(iterador);

		printf("Nombre:%s, Tipo:%c, Fuerza:%i, Destreza:%i, Resistencia:%i\n",
		       pokemon_actual->nombre, pokemon_actual->tipo,
		       pokemon_actual->fuerza, pokemon_actual->destreza,
		       pokemon_actual->resistencia);
	}
	pokemon_actual = lista_iterador_obtener_elemento_actual(iterador);
	printf("Nombre:%s, Tipo:%c, Fuerza:%i, Destreza:%i, Resistencia:%i\n",
	       pokemon_actual->nombre, pokemon_actual->tipo,
	       pokemon_actual->fuerza, pokemon_actual->destreza,
	       pokemon_actual->resistencia);
	lista_iterador_destruir(iterador);
}

void destruir_pokemon(void *pokemon)
{
	struct pokemon *pokemon_actual = pokemon;
	free(pokemon_actual->nombre);
	free(pokemon_actual);
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
	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], ';');
	if (!archivo) {
		cerrar_archivo_csv(archivo);
		return ERROR;
	}

	struct pokemon *pokemon;

	Lista *pokedex = lista_crear();
	if (!pokedex) {
		cerrar_archivo_csv(archivo);
		return ERROR;
	}
	bool (*funciones[COLUMNAS])(const char *, void *) = {
		crear_string_nuevo, leer_caracter, leer_int, leer_int, leer_int
	};
	char *nombre = NULL;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
	void *punteros[COLUMNAS] = { &nombre, &tipo, &fuerza, &destreza,
				     &resistencia };
	while (leer_linea_csv(archivo, COLUMNAS, funciones, punteros) ==
	       COLUMNAS) {
		pokemon = malloc(sizeof(struct pokemon));
		if (!pokemon) {
			lista_destruir(pokedex);
			cerrar_archivo_csv(archivo);
			return ERROR;
		}
		pokemon->nombre = nombre;
		pokemon->tipo = tipo;
		pokemon->fuerza = fuerza;
		pokemon->destreza = destreza;
		pokemon->resistencia = resistencia;
		if (!lista_agregar_al_final(pokedex, pokemon)) {
			lista_destruir(pokedex);
			cerrar_archivo_csv(archivo);
			return ERROR;
		}
	}

	bool es_correcto = false;
	while (!es_correcto) {
		int opcion;
		printf("Escribe el numero de la opción que quieras\n1. Ingrear por teclado un nombre y el programa busca el pokemon en la lista \n2. Listar todos los pokemones de la pokedex\n");
		if (!scanf("%i", &opcion)) {
			printf("No se pudo leer el numero correctamente");
			cerrar_archivo_csv(archivo);
			lista_destruir_todo(pokedex, destruir_pokemon);
			return ERROR;
		}
		struct pokemon *pokemon_encontrado;
		switch (opcion) {
		case 1:
			pokemon_encontrado =
				comparar_pokemones_en_lista(pokedex);
			if (pokemon_encontrado == NULL) {
				printf("No se encontro el pokemon buscado");
				cerrar_archivo_csv(archivo);
				lista_destruir_todo(pokedex, destruir_pokemon);
				return ERROR;
			}
			printf("Nombre:%s, Tipo:%c, Fuerza:%i, Destreza:%i, Resistencia:%i\n",
			       pokemon_encontrado->nombre,
			       pokemon_encontrado->tipo,
			       pokemon_encontrado->fuerza,
			       pokemon_encontrado->destreza,
			       pokemon_encontrado->resistencia);
			es_correcto = true;
			break;
		case 2:
			imprimir_pokemones_por_pantalla(pokedex);
			es_correcto = true;
			break;

		default:
			printf("Numero no valido ingresado, por favor ingrese 1 o 2\n");
			break;
		}
	}
	cerrar_archivo_csv(archivo);
	lista_destruir_todo(pokedex, destruir_pokemon);
}
