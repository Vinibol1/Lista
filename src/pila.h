#ifndef PILA_H_
#define PILA_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct pila Pila;

/**
 * 
*/
Pila *pila_crear();
void pila_destruir(Pila *);
void pila_destruir_todo(Pila *, void (*f)(void *));


/**
 * Recibe la pila y devuelve la cantidad de elementos en la pila
 * si la pila recibida no existe devuelve 0
*/
size_t pila_cantidad(Pila *);
/**
 * devuelve un puntero al elemento en el tope si todo sale correctamente,
 * caso contrario devuelve NULL
*/
void *pila_tope(Pila *);
/**
 * recibe el elemento que se desea apilar.
 * devuelve true si todo salio correctamente y devuelve false si el elemento es NULL
 * o si algo salio mal
*/
bool pila_apilar(Pila *, void *);
/**
 * devuelve un puntero al elemento desapilado si todo sale correctamente,
 * caso contrario devuelve NULL
*/
void *pila_desapilar(Pila *);
/**
 * devuelve true si la lista esta vacia
 * caso contrario devuelve false
*/
bool pila_esta_vacía(Pila *);

#endif // PILA_H_
