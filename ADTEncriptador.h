#ifndef ADTEncriptador__H__
#define ADTEncriptador__H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utils.h"

typedef struct{
	TAB diccionarios;
}ADTEncriptador;

typedef struct{
	char ip[MAX_LONG_IP];
	char Diccionario[DICCIONARIO];
}Diccionario_t;



int ADTEncriptador_create(ADTEncriptador*, int);
int ADTEncriptador_destroy(ADTEncriptador* );
int ADTEncriptador_establecer_mensaje(ADTEncriptador, const char**);
int ADTEncriptador_agregar_diccionario(ADTEncriptador*, char*);
void ADTEncriptador_eliminar_diccionario(ADTEncriptador*, char*);




int get_local_time(char**);
#endif
