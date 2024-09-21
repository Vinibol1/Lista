#include "csv.h"
#include "split.h"
#include <stdio.h>
#include <string.h>

struct archivo_csv {
	char nombre_archivo;
	FILE *abierto;
	char separador;
};

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	struct archivo_csv *archivo = malloc(sizeof(struct archivo_csv));
	if (archivo == NULL || nombre_archivo == NULL) {
		free(archivo);
		return NULL;
	}
	archivo->abierto = fopen(nombre_archivo, "r");
	if (archivo->abierto == NULL) {
		free(archivo);
		return NULL;
	}
	archivo->nombre_archivo = *nombre_archivo;
	archivo->separador = separador;
	return archivo;
}
/** 
 * la funcion necesita que haya la misma cantidad de funciones que 
 * de columnas que se quieran leer
 * esta devuelve la cantidad de columnas leídas correctamente.
*/
size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	if (archivo == NULL || columnas == 0)
		return 0;
	struct Partes *archivo_divido;
	char texto[300];
	char *linea_archivo = fgets(texto, 300, archivo->abierto);
	if (linea_archivo == NULL)
		return 0;
	archivo_divido = dividir_string(linea_archivo, archivo->separador);
	size_t contador = 0;
	for (size_t i = 0; i < columnas; i++)
		if (funciones[i] == NULL) {
			i = columnas;
		} else if (funciones[i](archivo_divido->string[i], ctx[i]))
			contador++;
	liberar_partes(archivo_divido);
	return contador;
}

void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	if (archivo == NULL)
		return;
	fclose(archivo->abierto);
	free(archivo);
}
