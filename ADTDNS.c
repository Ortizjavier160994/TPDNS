#include "ADTWS.h"


/*------------FUNCIONES PRIVADAS------------*/

int fill_operation_list(list_t*, const char*);
int fill_client_list(list_t*, const char*);
int get_file_path(char**, const char*, int);

/*------------------------------------------*/


int ADTDNS_crear(ADTDNS* dns, int tamanio){
	int st;
	TABO abodns;

	if(dns == NULL){
		return ERROR_NULL_POINTER;
	}

	if((st = ADTDNS_establecer_operacion(dns,op))!= OK){
		return st;
	}

	
	if((st = ABO_Crear(&abodns,sizeof(TABO), ))!= RES_OK){
		ADTDNS_destruir(ws);
		return st;
	}
	
	if((st = rellenar_abo(&abodns,DNSTXT))!= OK){
		ADTWS_destruir(ws);
		return st;
	}






}

int ADTDNS_existe_dominio(ADTDNS arbol,char * dominio){
	char * aux;

	aux=strdup(dominio);
	
	invertir(aux);

	if(buscar_dominio(arbol.ArbolDNS,aux) == FALSE){
		return FALSE;
	}

	return TRUE;

}

/* Falta cortar el string dominio y mandarlo por recursión. */
int buscar_dominio(TAB Arbol, char * dominio){
	char * tag, delim= '.', * aux;
	Domain_t dom;

	if(!dominio){
		return TRUE;
	}	

	tag=strtok(dominio,delim);

	AB_MoverCte(&Arbol,RAIZ);
	
	AB_ElemCte(Arbol,(void *)&dom);	

	if(buscar_tag(Arbol, dom, tag) == FALSE){
		return FALSE;
	}
	
	buscar_dominio(dom.Subarbol, )
}

/* Busca en Arbol el tag (TRUE si existe y FALSE si no). Si es TRUE devuelve el dom donde se encuentra el tag. */
int buscar_tag(TAB Arbol, Domain_t dom, char * tag){
	int cmp;

	if((cmp=strcmp(tag,dom.tag) != 0)){
		if(cmp>0){
			if(AB_MoverCte(&Arbol,DER)==FALSE){
				return FALSE;
			}		
		}
		else{	
			if(AB_MoverCte(&Arbol,IZQ)==FALSE){
				return FALSE;
			}
		}
		AB_ElemCte(Arbol,(void *)&dom);
		return buscar_tag(arbol,dom,tag);

	}
	
	return TRUE;
	
}


int ADTDNS_eliminar_dominio(ADTDNS* ,char*){
	









}



/*--------------------------------------------FUNCIONES PRIVADAS--------------------------------------------*/





/*-----------------MANEJO DEL TDA TABO-----------------*/





int rellenar_abo(TABO* abodns, const char* dnstxt){

	ElemArbol abo;
	FILE* fp;
	char ip[MAX_LONG_IP]; 
	char str[MAX_LINEA], *temp, **fieldv;
	int fieldc,st;


	if(abodns == NULL){
		return ERROR_NULL_POINTER;
	}
	
	
	if((fp = fopen(dnstxt,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while((fgets(str,MAX_LINEA,fp))!= NULL){
		if(!strcmp(str,"\n")) break;
		str[strcspn(str,"\n")] = 0;
		if((st = dividir_dominio_string(str,&fieldv,&fieldc,ip))!= OK){		
			fclose(fp);
			return st;
		}
		for((i=fieldc);i>0;i--){
			strcpy(abo.dominio,fieldc[i]);
			if(i==1) strcpy(abo.ip,ip);
			if((st = ABO_insertar(abodns,(void*)abo))!= TRUE){
				destroy_string_array(fieldv,fieldc);
				free(fieldv);
				fieldv = NULL;
				fclose(fp);
				return st;
			}		
			if((st = ABO_Crear(&abo.SubArbol,(void *) !=
		}
	}

	destroy_string_array(fieldv,fieldc); 
	free(fieldv);
	fieldv = NULL;
	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}
	
	return OK;
}
/*----------------------------------------------------------*/





/*--------------------MANEJO DE ARCHIVOS--------------------*/


int get_file_path(char** path, const char* config, int file_pos){

	FILE* fp;
	char str[STR_LEN];
	int i = 0;

	if (config == NULL){
		return ERROR_NULL_POINTER;
	}

	if((fp = fopen(config,"rt")) == NULL){
		return ERROR_OPENING_FILE;
	}

	while(fgets(str,sizeof(str),fp)!= NULL){
		if(!strcmp(str,"\n")) break;
		if(i == file_pos){
			if((*path = strdup(str)) == NULL){
				fclose(fp);
				return ERROR_MEMORY_SHORTAGE;
			}
			(*path)[strcspn(*path,"\n")] = 0; /*le saco el \n al string para poder usar fopen()*/
			fclose(fp);
			return OK;
		} 
		i++;
	}
	fclose(fp);
	return ERROR_MISSING_FILE;
}


int log_operation(ADTWS ws){

	FILE* fp;
	char* path;
	int st;

	if((st = get_file_path(&path,ws.config_file,LOG_PATH_POSITION))!=OK){
		return st;
	}

	if((fp = fopen(path,"a")) == NULL){
		return ERROR_OPENING_FILE;
	}

	printf("this is to be printed :%s\n",ADTWS_Op_get_response(ws.operation_t));

	fprintf(fp,"%s;%s;\n%s;\n%s\n",ADTWS_Op_get_operation_time(ws.operation_t),ADTWS_Op_get_operation(ws.operation_t),ADTWS_Op_get_request(ws.operation_t),ADTWS_Op_get_response(ws.operation_t));

	if(fclose(fp) == EOF){
		return ERROR_DISK_SPACE;
	}

	return OK;
}


/*----------------------------------------------------*/




