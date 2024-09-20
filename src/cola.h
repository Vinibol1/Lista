#ifndef COLA_H_
#define COLA_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct cola Cola;

Cola *cola_crear();
void cola_destruir(Cola *);
void cola_destruir_todo(Cola *, void (*f)(void *));

/**
 * devuelve la cantidad de elementos en la cola
 * si la cola recibida no existe devuelve 0
*/
size_t cola_cantidad(Cola *);
/**
 * devuelve el elementos de enfrente de la cola
 * si falla devuelve NULL
*/
void *cola_frente(Cola *);
/**
 * encola un elemento al final
 * devuelve true si todo salió bien o false si falló
*/
bool cola_encolar(Cola *, void *);
/**
 * desencola el elemento del principio
 * devuelve el elemento desencolado
 * si falló devuelve NULL
*/
void *cola_desencolar(Cola *);
/**
 * devuelve true si la cola esta vacia o si esta no existe y devuelve
 * false si no lo esta
*/
bool cola_esta_vacía(Cola *);

#endif // COLA_H_
