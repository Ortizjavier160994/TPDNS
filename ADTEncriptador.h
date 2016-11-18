#ifndef ADTWS_OP__H__
#define ADTWS_OP__H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "utils.h"


typedef struct{
	t_list diccionarios;
	char * mensaje;
	
}ADTEncriptador;






int ADTEncriptador_create(ADTEncriptador*,const char **);
int ADTEncriptador_destroy(ADTWS_Op*);
int ADTEncriptador_establecer_mensaje(ADTWS_Op*,const char**);
int ADTWS_Op_set_format(ADTWS_Op*);
int ADTWS_Op_set_operation_time(ADTWS_Op*);
int ADTWS_Op_set_response(ADTWS_Op*, char*);

char* ADTWS_Op_get_operation(ADTWS_Op);
char* ADTWS_Op_get_operation_time(ADTWS_Op);
char* ADTWS_Op_get_request(ADTWS_Op);
char* ADTWS_Op_get_format(ADTWS_Op);
char* ADTWS_Op_get_response(ADTWS_Op);


int ADTWS_Op_get_data(char**, const char*, ADTWS_Op);
int ADTWS_Op_get_method(char**, ADTWS_Op);
int ADTWS_Op_get_host(char**, ADTWS_Op);


int get_local_time(char**);
#endif
