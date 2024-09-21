#include "split.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Devuelve un Struct Partes con la informacion de un string nulo
 */
struct Partes *string_nulo(struct Partes *partes)
{
	partes->cantidad = 0;
	partes->string = NULL;
	return partes;
}

/**
 * Devuelve un Struct Partes con la informacion de un string vacio
 */
struct Partes *string_vacio(struct Partes *partes, char **str_dividido)
{
	int cantidad = 0;
	str_dividido[0] = "";
	cantidad++;
	partes->cantidad = (size_t)cantidad;
	partes->string = str_dividido;
	return partes;
}

/**
 * Separa un string que esta separado por comas
 */
void string_separado(const char *string, int i, int *contador, int *cantidad,
		     char **str_dividido, char separador)
{
	if (i == 0 || string[i - 1] == separador) {
		str_dividido[i] = "";
		*contador = i + 1;
		*cantidad += 1;
	} else {
		char *parte_de_str_dividido = malloc(sizeof(char));
		int j;
		for (j = 0; j < (i - *contador); j++) {
			char *temp =
				(char *)realloc(parte_de_str_dividido,
						sizeof(char) * ((size_t)j + 1));
			if (temp == NULL) {
				perror("no se pudo asignar la memoria");
				return;
			}
			parte_de_str_dividido = temp;
			parte_de_str_dividido[j] = string[j + *contador];
		}
		parte_de_str_dividido = (char *)realloc(
			parte_de_str_dividido, sizeof(char) * ((size_t)j + 1));
		parte_de_str_dividido[j] = 0;
		str_dividido[*cantidad] = parte_de_str_dividido;
		*contador = i + 1;
		*cantidad += 1;
	}
}

/**
 * Recibe un string y un separador y devuelve un struct con la informacion de los strings separados.
 */
struct Partes *dividir_string(const char *string, char separador)
{
	int contador = 0;
	int cantidad = 0;
	struct Partes *partes = (struct Partes *)malloc(sizeof(struct Partes));
	char **str_dividido = (char **)malloc(sizeof(char *));
	if (string == NULL) {
		free(str_dividido);
		return string_nulo(partes);
	} else if (string[0] == 0) {
		return string_vacio(partes, str_dividido);
	}

	for (int i = 0; i <= strlen(string); i++) {
		if (string[i] == separador || string[i] == 0) {
			string_separado(string, i, &contador, &cantidad,
					str_dividido, separador);

			str_dividido = (char **)realloc(
				str_dividido,
				sizeof(char *) * ((size_t)cantidad + 1));
		}
	}
	partes->string = str_dividido;
	partes->cantidad = (size_t)cantidad;
	return partes;
}

/**
 * Libera TODA la memoria utilizada por el struct Partes.
 */
void liberar_partes(struct Partes *partes)
{
	if (partes->cantidad > 0 && partes->string[0][0] != 0) {
		for (size_t i = 0; i < partes->cantidad; i++) {
			free(partes->string[i]);
		}
	}
	free(partes->string);
	free(partes);
}
