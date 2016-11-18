#include "utils.h"

int copy_abo(void* dest, const void* source){


	ElemArbol *d, *s;

	if(dest == NULL || source == NULL){
		return ERROR_NULL_POINTER;
	}

	d = (ElemArbol*) dest;
	s = (ElemArbol*) source;
	
	strcpy(d->ip,s->ip);
	
	if(s->dominio != NULL){
		strcpy(d->dominio, s->dominio);
	}

	d->SubArbol=s->SubArbol;

	return OK;
}


void destroy_abo(void* data){

	return ;
}

int compare_abo(const void* a, const void* b){

	ElemArbol *aboA, *aboB;

	aboA = (ElemArbol*) a;
	aboB = (ElemArbol*) b;

	return (strcmp(aboA->dominio,aboB->dominio));
}

char* strdup(const char* s){ /*Copia string*/

	char* d;

	if((d = (char*) malloc (strlen(s)+1)) == NULL){
		return NULL;
	}

	strcpy(d,s);

	return d;
}

int dividir_dominio_string(char* str, char*** fieldv, int* fieldc, char ip[MAX_LONG_IP]){ 

	char *p, *q, *r, *s;
	int i;
	char dels[] = {DNS_DELIM, '\0'};

	
	if(str == NULL || fieldv == NULL || fieldc == NULL){
		return ERROR_NULL_POINTER;
	}

	(*fieldc) = 0;
	
	for(i = 0; str[i]!=' '; i++){
		if(str[i] == DNS_DELIM){
			if(str[i+1]!=' ')(*fieldc)++;
		}
	}
	
	(*fieldc)++;

	if(((*fieldv) = (char**) malloc ((*fieldc) * sizeof(char*))) == NULL){
		return ERROR_MEMORY_SHORTAGE;
	}

	q=str;

	r=strtok(q,' ');
	
	s=strtok(NULL,'\0');

	for(p = r, i = 0; (p = strtok(r,dels))!= NULL; r=NULL, i++){
		if(((*fieldv)[i] = strdup(p)) == NULL){
			destroy_string_array(*fieldv,i);
			free(*fieldv);
			(*fieldv) = NULL;
			return ERROR_MEMORY_SHORTAGE;
		}
	}
	
	strcpy(ip,s);

	return OK;
}



/*copia un arreglo de strings en un solo string*/
int concat_str_array(int len, const char** arr, char** dest){ 

	unsigned int i;


	if(arr == NULL){
		return ERROR_NULL_POINTER;
	}

	if((*dest = (char*) malloc (INIT_CHOP)) == NULL){ 
		return ERROR_MEMORY_SHORTAGE;
	}

	**dest = '\0';

	for (i = 0; i < len -1; i++){
			
		if((*dest = (char*) realloc (*dest,strlen(*dest)+strlen(arr[i])+1)) == NULL){
			return ERROR_MEMORY_SHORTAGE;
		}
		strcat(*dest,arr[i]);	
		strcat(*dest," ");
	}

	if((*dest = (char*) realloc (*dest,strlen(*dest)+strlen(arr[i])+1)) == NULL){
			return ERROR_MEMORY_SHORTAGE;
		}
	strcat(*dest,arr[i]);
	
	return OK;
}




void destroy_string_array(char** arr, int len){ /*destruye un arreglo de strings*/

	int i;

	if(arr == NULL){
		return;
	}

	for(i = 0; i < len; i++){
		free(arr[i]);
		arr[i] = NULL;
	}

	return;
}
