#ifndef ADTDNS__H__
#define ADTDNS__H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"
#include "errors.h"
#include "utils.h"

typedef struct{
	ADTEncriptador encriptador;
	TABO ArbolDNS;
	char * urlOrigen;
	char * ipOringen;
	char * urlDestino;
	char * ipDestino;
	char * mensaje;
}ADTDNS;

typedef struct{
	char * dominio;
	char ip[MAX_LONG_IP];
	TABO SubArbolDNS;
}ElemArbol;

int log_operation(ADTWS);

int ADTDNS_crear(ADTDNS*, int ,int ,const char **);
int ADTDNS_destruir(ADTDNS*);
int ADTDNS_agregar_dominio(ADTDNS*,char*,void *);
int ADTDNS_obtener_valor(ADTDNS,char*,void *);
int ADTDNS_existe_dominio(ADTDNS ,char *);
int ADTDNS_eliminar_dominio(ADTDNS* ,char*);

int log_operation(ADTWS);

#endif
