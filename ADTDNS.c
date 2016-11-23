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
	char * aux, * tag, delim='.'; 
	int cmp;
	Domain_t dom;

	aux=strdup(dominio);
	
	invertir(aux);

	if(AB_MoverCte(&arbol,RAIZ))==FALSE){
		return FALSE;	
	}
	
	AB_ElemCte(arbol,(void *)&dom);

	while(tag=(strtok(aux,delim)){

		while((cmp=strcmp(tag,dom.tag) != 0)){
			if(cmp>0){
				if(AB_MoverCte(&dom,DER)==FALSE){
					return FALSE;
				}else{
					AB_ElemCte(dom,(void *)&dom);
				}
			}
			else{
			}
				if(AB_MoverCte(&dom,IZQ)==FALSE){
					return FALSE;
				}else{
					AB_ElemCte(dom,(void *)&dom);
				}
		}		
		
		if(AB_MoverCte(&(dom.SubArbol),RAIZ))==FALSE){
			return FALSE;	
		}
	
		AB_ElemCte(dom.SubArbol,(void *)&dom);	
	
	}

	return TRUE;

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




