#ifndef ADTWS_OP__H__
#define ADTWS_OP__H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utils.h"

typedef struct{
	t_list diccionarios;
}ADTEncriptador;

typedef struct{
	char ip[MAX_LONG_IP];
	char Diccionario[DICCIONARIO];
}Diccionario_t;



int ADTEncriptador_create(ADTEncriptador*,const char **);
int ADTEncriptador_destroy(ADTWS_Op*);
int ADTEncriptador_establecer_mensaje(ADTWS_Op*,const char**);
int ADTWS_Op_set_format(ADTWS_Op*);
int ADTWS_Op_set_operation_time(ADTWS_Op*);
int ADTWS_Op_set_response(ADTWS_Op*, char*);



int get_local_time(char**);
#endif
