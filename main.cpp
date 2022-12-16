#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Integrantes del grupo: Juan Hidalgo, Luis Daniel, Matias Silveira */


struct l_nodo {
    char Nom[9], Ext, Tip, fcm[20];
    int r, h;
    l_nodo* pUL /* hermanos*/, * pFA /* hijo direc*/, * pPA /* direc padre */;
};





int verificarExist(l_nodo* p, char x[]) {
    l_nodo* t = p;
    if (strcmp(t->Nom, x) == 0) 
        return 1;
    while (t != NULL) {
        if (strcmp(t->Nom, x) == 0) {
            return 1;
        }
        t = t->pUL;
    }
    ;
    return 0;
}

int ValidName(char veri[9]) {
    bool ok = true;
    for (int i = 0; i < strlen(veri); i++) {
        if (veri[i] < 48 || veri[i] > 122)
            ok = false;
        if (((veri[i] > 57) && (veri[i] < 65)) || ((veri[i] > 90) && (veri[i] < 97)))
            ok = false;
    }
    return ok;
}
void imprimirDir(l_nodo* p) {
    l_nodo* t = p;
    if (t == NULL)
        printf("Directorio actual -> [C:/");
    else {
        printf("Directorio actual -> [C:");
        while (t != NULL) {
            printf("/%8s", t->Nom, 9);
            t = t->pUL;
        }
    }
    printf("\n\n");
}

void fecha(char fcm[]) {
    time_t now = time(0);
    struct tm* actTime = localtime(&now);
    int d = actTime->tm_mday, m = actTime->tm_mon + 1, y = actTime->tm_year + 1900;
    sprintf(fcm, "%i%i%i", d, m, y);
}

void MKD(l_nodo** P, char Nombre[9], int h, int r) {
    l_nodo* t, * aux = *P, *bux;
	 if (*P == NULL){
		printf("ruta invalida  \n");
		return;
	}else if (ValidName(Nombre) == false ) {
	printf("ERROR, EL NOMBRE DEL DIRECTORIO NO ES ALFA NUMERICO \n");
	return;
	}
            t = new l_nodo;
            strcpy_s(t->Nom, Nombre);
            t->pUL = NULL;
            t->pFA = NULL;
            t->pPA = aux;
            t->h = h;
            t->r = r;
            fecha(t->fcm);
            t->Tip = 'D';
            if (aux->pFA) {
                bux = aux->pFA;
                aux = aux->pFA;  
               
                 do{
                    if (verificarExist(bux, Nombre) == 1) {
                       
                          
                            printf("-------------------------------------------------\n");
                            printf("Error, otro directorio ya tiene este nombre\n");
                            printf("-------------------------------------------------\n\n");
                            system("pause"); 
                            return;
                        
                    }
                    bux = bux->pUL;
                 } while (bux != NULL);
                 while (aux->pUL)
                     aux = aux->pUL;
                aux->pUL = t;
            
			}
            else {
                
                aux->pFA = t;
            
			}
}   



void CHD(l_nodo** p, int x) {
    l_nodo* aux = *p;
    char a[9];
    while (x != 0) {
        system("cls");
        printf("-----------------------------------\n");
        printf("Manejo Virtual de Archivos (MVA)\n");
        printf("[2.Cambiar directorio (CHD)]\n");
        printf("-----------------------------------\n\n");
        imprimirDir(*p);
        printf("1.\tSubir a directorio padre\n");
        printf("2.\tBajar a un subdirectorio (inmediato)\n");
        printf("0.\tSalir\n");
        printf("Su opcion [0-2]: ");
        scanf(" %i", &x);
        aux = *p;

        if (x == 1) {
            if ((*p)->pPA == NULL) { //evalua el caso en que el padre actual sea nulo (es decir, que stuviera parado en la unidad logica)
                printf("\n\nError, el padre del directorio actual es la unidad logica. No se puede subir mas.\n\n");
                system("pause");
            }
            else {
                *p = (*p)->pPA;
                printf("\n\nHa subido al director padre\n\n");
                system("pause");
            }
        }

        if (x == 2) {
            system("cls");
            printf("--------------------------------------------------------------\n");
            printf("Por favor ingrese el nombre del directorio al que desea bajar\n");
            printf("--------------------------------------------------------------\n\n");
            scanf(" %8s", a, 9);
            if ((*p)->pFA == NULL) { //evalua que exita un hijo primero
                printf("\n\nError, no existen hijos del directorio actual\n");
                printf("--------------------------------------------------------------\n\n");
            }
            else { //si el hijo existe, aux es igual al hijo de aux, lo busca y si lo encuentra entonces *p sera igual a aux
                aux = aux->pFA;
                if (verificarExist(aux, a) == 1) {
                    /*
                    while (strcmp(aux->Nom, a) == 0) {
                        printf("\n\nComparando  dentro %8s \n", aux->Nom, 9);
                        aux = aux->pUL;
                    }*/
                    do {
                        if (strcmp(aux->Nom, a) == 0) {
                            break;
                        }
                        aux = aux->pUL;
                    } while (aux != NULL);
                    *p = aux;
                    printf("\n\nHa bajado al subdirectorio inmediato al directorio %8s\n", (*p)->Nom,9);
                }
                else {
                    printf("Error, ese directorio no existe. No se puede bajar al directorio ingresado\n");
                }
            }
            system("pause");
        }
    }
}

void eliminarDirHermanos(l_nodo** p) {
    l_nodo* t = *p, * aux = t;
    while (t != NULL) {
        if (t->pFA != NULL) {
            eliminarDirHermanos(&(t->pFA));
        }
        (*p)->pFA = t->pUL;
        aux = t->pUL;
        delete t;
        t = aux;
    }
}

void eliminarDir(l_nodo** p, char txt[9]) {
    l_nodo* t = *p;
    while (t != NULL) {
        if (strcmp(t->Nom, txt) == 0) {
            if (t->pFA != NULL) {
                eliminarDirHermanos(&(t->pFA));
            }
            (*p) = t->pUL;            
            delete t;
            break;
        }
        else {
            t = t->pUL;
        }
    }
}


void RMD(l_nodo** p, char txt[9], int O) {
    l_nodo* t = (*p)->pFA, * pux, * del;
    int x;
	if ( O == 1 ){ 
	pux = *p;
            if ((t == NULL) || (verificarExist(t, txt) == 0)) {
                printf("Error, ese directorio no existe en el directorio actual\n\n");
                system("pause");
                return;
            }
            else {
                if ((strcmp(pux->pFA->Nom, txt) == 0) && (pux->pFA->pUL == NULL)) {
                    if (t->pUL == NULL) {
                       
                        if (t->pFA == NULL) {
                            pux->pFA = NULL;
                            delete t;
							return;
                        }
                        else if ((t->pFA) || (t->r == 1)) {
						

                                    eliminarDir(&t, txt);
                                    pux->pFA = NULL;                          
                                    return;                                                         
						
                            }
                        
                       
                    }
                }
                else {
                    if ((strcmp(pux->pFA->Nom, txt) == 0) && (t->pUL)) {
                        
                        if (t->pFA == NULL) {
                            pux->pFA = t->pUL;
                            delete t;
                        }
                        else if ((t->pFA) || (t->r == 1)) {
                           
                            
                                    pux->pFA = t->pUL;
                                    eliminarDir(&t, txt);                                

                                    return;
									
                                
                            }
                        
                      
                    }
                }
                while (t) {

                    if (strcmp(t->pUL->Nom, txt) == 0) {
                        if (t->pUL->pUL == NULL) {

                            if (t->pUL->pFA == NULL) {
                                del = t->pUL;
                                t->pUL = NULL;
                                delete del;
                            }
                            else if ((t->pUL->pFA)  || (t->pUL->r == 1)) {
                             
                                
                                        del = t->pUL;
                                        t->pUL = NULL;
                                        eliminarDir(&del, txt);
                                        x = -1;
                                        return;
                                   
                                    
                                
                            }                                                     
                        }
                        else                                                
                        if (t->pUL->pUL) {
                            del = t->pUL;
                            if (t->pUL->pFA == NULL) {
                                t->pUL = del->pUL;
                                delete del;
                            }
                            else if ((t->pUL->pFA)  || (t->pUL->r == 1)) {

                                        t->pUL = del->pUL;
                                        eliminarDir(&del, txt);
                                       
                                        return;                                                           
                                
                            }
                        }
                            
                    }

                        t = t->pUL;
                        
                }


               
            }
	
	} 
	else ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (O == 0 ){
            pux = *p;
            if ((t == NULL) || (verificarExist(t, txt) == 0)) {
                printf("Error, ese directorio no existe en el directorio actual\n\n");
                system("pause");
                return;
            }
            else {
                if ((strcmp(pux->pFA->Nom, txt) == 0) && (pux->pFA->pUL == NULL)) {
                    if (t->pUL == NULL) {
                       
                        if (t->pFA == NULL) {
                            pux->pFA = NULL;
                            delete t;
							return;
                        }
                        else if ((t->pFA) || (t->r == 1)) {
						
                                printf(" el directorio selecionado tiene hijos o es solo lectura ,quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                scanf("%i", &x);
									if ( x == 1 ){
                                    eliminarDir(&t, txt);
                                    pux->pFA = NULL;                          
                                    return;                                                         
						}
                            }
                        
                       
                    }
                }
                else {
                    if ((strcmp(pux->pFA->Nom, txt) == 0) && (t->pUL)) {
                        
                        if (t->pFA == NULL) {
                            pux->pFA = t->pUL;
                            delete t;
                        }
                        else if ((t->pFA) || (t->r == 1)) {
                           
                                printf(" el directorio selecionado tiene hijos o es solo lectura, quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                scanf("%i", &x);
									if ( x == 1 ){                             
                                    pux->pFA = t->pUL;
                                    eliminarDir(&t, txt);                                

                                    return;
									}
                                
                            }
                        
                      
                    }
                }
                while (t) {

                    if (strcmp(t->pUL->Nom, txt) == 0) {
                        if (t->pUL->pUL == NULL) {

                            if (t->pUL->pFA == NULL) {
                                del = t->pUL;
                                t->pUL = NULL;
                                delete del;
                            }
                            else if ((t->pUL->pFA)  || (t->pUL->r == 1)) {
                             
                                    printf(" el directorio selecionado tiene hijos o es solo lectura, quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                    scanf("%i", &x);
                                   if (x = 1)  {                                    
                                        del = t->pUL;
                                        t->pUL = NULL;
                                        eliminarDir(&del, txt);
                                        x = -1;
                                        return;
                                   
                                    
                                }
                            }                                                     
                        }
                        else                                                
                        if (t->pUL->pUL) {
                            del = t->pUL;
                            if (t->pUL->pFA == NULL) {
                                t->pUL = del->pUL;
                                delete del;
                            }
                            else if ((t->pUL->pFA)  || (t->pUL->r == 1)) {
                              
                                    printf(" el directorio selecionado tiene hijos o es solo lectura, quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                    scanf("%i", &x);
										if (x == 1){
                                        t->pUL = del->pUL;
                                        eliminarDir(&del, txt);
                                       
                                        return;                                                           
                                }
                            }
                        }
                            
                    }

                        t = t->pUL;
                        
                }


               
            } 
 
        
		}
}

void verificarHijos(l_nodo** p, char txt[9]) {
    l_nodo* t = *p;
    while (t != NULL) {
        if (strcmp(t->Nom, txt) == 0) {
            break;
        }
        if (t->pFA != NULL) {
            verificarHijos(&(t->pFA), txt);
        }
        t = t->pUL;
    }                      //En este caso, verifica si existe la carpeta destino
                          //Pero en el caso de moverla, la movera al primero que encuentre
}

int validar(l_nodo *p, char Nombre[9]){
	if (p->pFA){
		if (strcmp (p->pFA->Nom,Nombre)== 0)return 1 ;
			else {p=p->pFA;
				while (p){
					if (strcmp (p->Nom,Nombre)== 0)return 1 ;
					else p = p->pUL;
				}

			}
	}else return 0;

} 

int verificarSoloR(l_nodo* p){
	int q = 0; 
	if (p){
		if (p->r == 1) return 1;
		q += verificarSoloR(p->pFA); 
		q += verificarSoloR (p->pUL);
	}else return 0;
	if (q > 0) return 1;
	else return 0;
}

				
void MVD(l_nodo** p,  l_nodo **j, int O) {
	l_nodo *AX , *elim;
	char hola[9];
	if 	(((*p == NULL) || (*j == NULL)) || (((*p)->pPA == NULL))){
	printf("ERROR EL DESTINO EL DIRECTORIO O ES UNA UNIDAD LOGICA A MOVER NO EXISTEN\n");
	system ("pause");
	return;
	}else if (O == 0 ){
		if (validar(*j,(*p)->Nom) == 1 ){
		printf("el destino ya contiene un directorio con ese mismo nombre\n");
	
	return;}
     	if ((verificarSoloR((*p)->pUL) == 1 ) || ((*p)->r)== 1){
			printf("el directorio a mover o sus hijos son solo lectura\n");
	
			return;
		}else if (verificarSoloR(*p) == 0 ){
			if ((strcmp ((*p)->Nom,(*p)->pPA->pFA->Nom )== 0 ) && ((*p)->pUL == NULL)){
				(*p)->pPA->pFA = NULL;
			}else 
			if ((strcmp ((*p)->Nom,(*p)->pPA->pFA->Nom )== 0 ) && ((*p)->pUL)){
				(*p)->pPA->pFA = (*p)->pUL;
				(*p)->pUL = NULL;
			}else if (strcmp ((*p)->Nom,(*p)->pPA->pFA->Nom )	!= 0 ){
				strcpy(hola,(*p)->Nom);
			AX = (*p)->pPA;
			AX = AX->pFA;
				while (AX->pUL){
					if (strcmp (hola,AX->pUL->Nom) == 0 ){
						AX->pUL = (*p)->pUL; ;
					    (*p)->pUL = NULL;
					}else AX->pUL; 
				}	
			}
		}
		(*p)->pPA = *j;
		if ((*j)->pFA == NULL) {
			(*j)->pFA = *p;
		}else if ((*j)->pFA ){
			AX = (*j)->pFA ;
			while (AX->pUL) AX = AX->pUL;
			AX->pUL = *p;
	}		
		}
	else if (O == 1){
		if ((*j)->pFA ){
			AX = (*j)->pFA;
			while (AX->pUL){
				if (strcmp(AX->pUL->Nom,(*p)->Nom)== 0 ){
				elim = AX->pUL;
				AX->pUL = elim->pUL;
					elim->pUL = NULL;
					eliminarDir(&elim, (*p)->Nom);
				}else AX->pUL;
			
		}
			
		}if ((strcmp ((*p)->Nom,(*p)->pPA->pFA->Nom )== 0 ) && ((*p)->pUL == NULL)){
				(*p)->pPA->pFA = NULL;
			}else
			if ((strcmp ((*p)->Nom,(*p)->pPA->pFA->Nom )== 0 ) && ((*p)->pUL)){
				(*p)->pPA->pFA = (*p)->pUL;
				(*p)->pUL = NULL;
			}else  if (strcmp ((*p)->Nom,(*p)->pPA->pFA->Nom )	!= 0 ){
				strcpy(hola,(*p)->Nom);
			AX = (*p)->pPA;
			AX = AX->pFA;
				while (AX->pUL){
					if (strcmp (hola,AX->pUL->Nom) == 0 ){
						AX->pUL = (*p)->pUL; ;
					    (*p)->pUL = NULL;
					}else AX->pUL; 
				}	
			}
				(*p)->pPA = *j;
		if ((*j)->pFA == NULL) {
			(*j)->pFA = *p;
		}else if ((*j)->pFA ){
			AX = (*j)->pFA ;
			while (AX->pUL) AX = AX->pUL;
			AX->pUL = *p;
		}		
	}
}   
l_nodo* copiar(l_nodo*p, l_nodo *t, bool comp) {
 l_nodo *AX = p, *k = new l_nodo;
	
	strcpy(k->Nom, AX->Nom);
	k->h = AX->h;
    k->r = AX->r;
    strcpy(k->fcm,AX->fcm);
    k->Tip = AX->Tip;

	if(AX->pFA){
		k->pFA = copiar(AX->pFA,k, false);
	}else {
		k->pFA = NULL;
	}
	if ((AX->pUL)&&(comp == false)){
		k->pUL = copiar(AX->pUL,t,false);
	}else {
		k->pUL = NULL;
	}
	k->pPA = t;
	return(k);
}
	
		 

void CPD(l_nodo** p,  l_nodo **j, int O) {
    l_nodo* t, *AX , *elim, *AUX;
	
    int i = 0, cont = 0;
   if 	(((*p == NULL) || (*j == NULL)) || (((*p)->pPA == NULL))){
	printf("ERROR EL DESTINO EL DIRECTORIO O ES UNA UNIDAD LOGICA A MOVER NO EXISTEN\n");

	return;
   }else if (O == 0 ){
	   if  (validar(*j,(*p)->Nom) == 1 ){
		printf("el destino ya contiene un directorio con ese mismo nombre\n");

	return;	
	   }
     	if((verificarSoloR((*p)->pUL) == 1 ) || ((*p)->r)== 1){
			printf("el directorio a mover o sus hijos son solo lectura\n");
			
			return;
		}else if (verificarSoloR(*p) == 0 ){
			 t = copiar(*p,*j,true);
			 if ((*j)->pFA == NULL) {
			(*j)->pFA = t;
		}else if ((*j)->pFA ){
			AX = (*j)->pFA ;
			while (AX->pUL) AX = AX->pUL;
			AX->pUL = t;
	}	

		}
   }if (O == 1){
	if ((*j)->pFA ){
			AX = (*j)->pFA;
			while (AX->pUL){
				if (strcmp(AX->pUL->Nom,(*p)->Nom)== 0 ){
				elim = AX->pUL;
				AX->pUL = elim->pUL;
					elim->pUL = NULL;
					eliminarDir(&elim, (*p)->Nom);
				}else AX->pUL;			
			}
			
	}
   t = copiar(*p,*j,true);
			 if ((*j)->pFA == NULL) {
			(*j)->pFA = t;
		}else if ((*j)->pFA ){
			AX = (*j)->pFA ;
			while (AX->pUL) AX = AX->pUL;
			AX->pUL = t;
	}	
   }
   else if (O == 2){
	   if (validar(*j,(*p)->Nom) == 1 ){
		t = copiar(*p,*j,true);
		t->pPA = NULL;
	   AX = (*j)->pFA;
		while (strcmp (AX->Nom,t->Nom )!=0){
			AX->pUL;
		}
			if (AX->pFA == NULL){
				elim = t; 
				t=t->pFA;
				while (t){
					t->pPA = AX;
					t = t->pUL;
				}
				eliminarDir(&elim,elim->Nom);
			} else{
			    elim = t; 
				t=t->pFA;
				AX = AX->pFA;
				while(AX->pUL){
					while(t){
						if (strcmp(AX->Nom,t->Nom)== 0 ){
							AUX = t; 
							t = t->pUL;
							elim->pFA = t;
							eliminarDir(&AUX,AUX->Nom);
						}else t->pUL;					
					}
					AX = AX->pUL;
				}
				AUX = elim->pFA;
				AX->pUL = AUX;
				AX = AX->pPA;
				while(AUX)	{
					AUX->pPA = AX;
					AUX = AUX->pUL;
				}
				eliminarDir(&elim,elim->Nom);
			}
			

	   }
	   else if (validar(*j,(*p)->Nom) == 0 ){
	    t = copiar(*p,*j,true);
			 if ((*j)->pFA == NULL) {
			(*j)->pFA = t;
		}else if ((*j)->pFA ){
			AX = (*j)->pFA ;
			while (AX->pUL) AX = AX->pUL;
			AX->pUL = t;
	   
	   }
   
	   }
	}
}



void bisiesto(int* y, int* m, int* d) {
    if (*y % 4 == 0 && *y % 100 != 0 || *y % 400 == 0) {
        printf("\nIngrese el valor del mes: ");
        scanf("%i", m);
        if (*m >= 1 || *m <= 12) {
            printf("\nIngrese el valor del dia: ");
            scanf("%i", d);
            if ((*m == 2) && (*d > 29 || *d < 1)) {
                do {
                    printf("\n\nError, ese valor no esta admitido para este mes, ingrese otro\n");
                    scanf("%i", d);
                } while (*d > 29 || *d < 1);
            }
        }
        else {
            if (*m == 1 || *m == 3 || *m == 5 || *m == 7 || *m == 8 || *m == 10 || *m == 12) {
                printf("\nIngrese el valor del dia: ");
                scanf("%i", d);
                if (*d > 31 || *d < 1) {
                    do {
                        printf("\n\nError, ese valor no esta admitido para este mes, ingrese otro\n");
                        scanf("%i", d);
                    } while (*d > 31 || *d < 1);
                }
            }
            if (*m == 4 || *m == 6 || *m == 7 || *m == 9 || *m == 11) {
                printf("\nIngrese el valor del dia: ");
                scanf("%i", d);
                if (*d > 30 || *d < 1) {
                    do {
                        printf("\n\nError, ese valor no esta admitido para este mes, ingrese otro\n");
                        scanf("%i", d);
                    } while (*d > 30 || *d < 1);
                }
            }
            printf("\n\nError, ese no es un mes valido\n");
            bisiesto(y, m, d);
        }
    }
    else {
        printf("\nIngrese el valor del mes: ");
        scanf("%i", m);
        if (*m >= 1 && *m <= 12) {
            printf("\nIngrese el valor del dia: ");
            scanf("%i", d);
            if ((*m == 2) && (*d > 28 || *d < 1)) {
                do {
                    printf("\n\nError, ese valor no esta admitido para este mes, ingrese otro\n");
                    scanf("%i", d);
                } while (*d > 28 || *d < 1);
            }
        }
        else {
            if (*m == 1 || *m == 3 || *m == 5 || *m == 7 || *m == 8 || *m == 10 || *m == 12) {
                printf("\nIngrese el valor del dia: ");
                scanf("%i", d);
                if (*d > 31 || *d < 1) {
                    do {
                        printf("\n\nError, ese valor no esta admitido para este mes, ingrese otro\n");
                        scanf("%i", d);
                    } while (*d > 31 || *d < 1);
                }
            }
            if (*m == 4 || *m == 6 || *m == 7 || *m == 9 || *m == 11) {
                printf("\nIngrese el valor del dia: ");
                scanf("%i", d);
                if (*d > 30 || *d < 1) {
                    do {
                        printf("\n\nError, ese valor no esta admitido para este mes, ingrese otro\n");
                        scanf("%i", d);
                    } while (*d > 30 || *d < 1);
                }
            }
            printf("\n\nError, ese no es un mes valido\n");
            bisiesto(y, m, d);
        }

    }
}

void modificarFecha(char fcm[], int d, int m, int y) {
    printf("Los valores ingresados son: %i/%i/%i", d, m, y);
    printf("\n\nSe ha modificado la fecha de forma satisfactoria\n\n");
    sprintf(fcm, "%i%i%i", d, m, y);
}

void MDD(l_nodo** p, int x) {
    l_nodo* t = *p,*aux, *pux;
    char txt[9];
    int d, m, y, r;

    while (x != 0) {
        system("cls");
        printf("-----------------------------------\n");
        printf("Manejo Virtual de Archivos (MVA)\n");
        printf("[6.Modificar directorio (MDD)]\n");
        printf("-----------------------------------\n\n");
        imprimirDir(*p);
        printf("1.\tNombre [%8s]\n", t->Nom,9);
        printf("2.\tFecha [%s]\n", t->fcm);
        printf("3.\tLectura [%i]\n", t->r);
        printf("4.\tEscondido [%i]\n", t->h);
        printf("0.\tSalir\n");
        printf("Su opcion [0-4]: ");
        scanf(" %i", &x);
        system("cls");

        switch (x) {
        case 1:
            printf("----------------------------------------------------\n");
            printf("Ingrese el nombre por el que desea cambiar el actual  ( %8s )\n\n", t->Nom);
            scanf(" %8s", txt, 9);
            aux = t;
            aux->pPA;
            aux->pFA;
            pux = aux->pPA;
            if (verificarExist(pux->pFA, txt) == 1) {
              
                        printf("Error nombre ya existe\n\n");
                        system("pause");
                        return;

               
            }
            strcpy_s(t->Nom, txt);
            printf("Se ha modificado el nombre del directorio a: %8s", t->Nom,9);
            printf("-----------------------------------------------------\n\n");
            break;

        case 2:
            printf("----------------------------------------------------\n");
            printf("Ingrese el valor del año: ");
            scanf("%i", &y);
            bisiesto(&y, &m, &d);
            
            modificarFecha(t->fcm, d, m, y);
            system("pause");
            break;

        case 3:
            printf("----------------------------------------------------------------------------\n");
            printf("Ingrese el tipo de directorio (lectura) que desea asignarle al actual");
            printf("\nConsidere que los unicos valores admitidos son 1 (lectura) y 0 (no lectura)\n\n");
            scanf("%i", &r);
            if (r > 1 || r < 0) {
                do {
                    printf("Error, ese valor no esta admitido para asignarlo al directorio\n");
                    printf("Ingrese otro valor\n");
                    scanf("%i", &r);
                } while (r > 1 || r < 0);
            }
            t->r = r;
            printf("Se ha modificado el directorio de forma satisfactoria\n");
            printf("--------------------------------------------------------------------------------\n\n");
            system("pause");
            break;

        case 4:
            printf("--------------------------------------------------------------------------------\n");
            printf("Ingrese el tipo de directorio (escondido) que desea asignarle al actual");
            printf("\nConsidere que los unicos valores admitidos son 1 (escondido) y 0 (no escondido)\n\n");
            scanf("%i", &r);
            if (r > 1 || r < 0) {
                do {
                    printf("Error, ese valor no esta admitido para asignarlo al directorio\n");
                    printf("Ingrese otro valor\n");
                    scanf("%i", &r);
                } while (r > 1 || r < 0);
            }
            t->h = r;
            printf("Se ha modificado el directorio de forma satisfactoria\n");
            printf("--------------------------------------------------------------------------------\n\n");
            system("pause");
            break;
        }
    }
}

void mostrarDir(l_nodo* p, int cont) {
    int contact = 0;
    while (p != NULL) {
        for (int i = 0; i < cont; i++)
            printf("  ");
        printf("%s     <%c>      %s       r(%i)\n", p->Nom, p->Tip, p->fcm, p->r);
        if (p->pFA != NULL) {
            contact = cont;
            cont++;
            mostrarDir(p->pFA, cont);
            cont = contact;
        }
        p = p->pUL;
    }
}

void mostrarArchivos(l_nodo* p, int cont, int op) {
    int contact = 0;
    if (op == 0) {
        while (p != NULL) {
            for (int i = 0; i < cont; i++)
                printf("  ");
            if (p->h == 0)
                printf("|%s     <%c>      %s       r(%i)   h-\n", p->Nom, p->Tip, p->fcm, p->r, p->h);
            else
                printf("");
            p = p->pUL;
        }
    }
    else {
        while (p != NULL) {
            for (int i = 0; i < cont; i++)
                printf("  ");
            if (p->h == 1)
                printf("|%8s     <%c>      %s       r(%i)   h+\n", p->Nom, p->Tip, p->fcm, p->r, p->h);
            else
                printf("|%8s     <%c>      %s       r(%i)   h-\n", p->Nom, p->Tip, p->fcm, p->r, p->h);
            p = p->pUL;
        }
    }
}

void SHD(l_nodo* p, int x) {
    l_nodo* t = p;
    int cont = 0, op = 0;
    while (x != 0) {
        t = p->pFA;
        system("cls");
        printf("----------------------------------------------------\n");
        printf("Manejo Virtual de Archivos (MVA)\n");
        printf("[7.Mostrar directorio (SHD)]\n");
        printf("----------------------------------------------------\n\n");
        imprimirDir(p);
        printf("1.\tContenidos del directorio actual\n");
        printf("2.\tContenidos del directorio actual con subcarpetas\n");
        printf("3.\tArchivos escondidos\n");
        printf("0.\tSalir\n");
        printf("Su opcion [0-3]: ");
        scanf(" %i", &x);
        system("cls");

        switch (x) {
        case 1:
            printf("-----------------------------------------\n");
            printf("C:/\n");
            while (t != NULL) {
                printf("|%8s     <%c>      %s       r(%i)\n", t->Nom, t->Tip, t->fcm, t->r);
                t = t->pUL;
            }
            printf("-----------------------------------------\n\n");
            system("pause");
            break;
        case 2:
            printf("-----------------------------------------\n");
            printf("C:/\n");
            mostrarDir(t, cont);
            printf("-----------------------------------------\n\n");
            system("pause");
            break;
        case 3:
            printf("-------------------------------------------------------------\n");
            printf("Desea mostrar los archivos escondidos?\n");
            printf("escriba uno (1) para mostrarlos o cero (0) para no mostrarlos\n");
            printf("-------------------------------------------------------------\n\n");
            scanf(" %i", &op);
            if (op > 1 || op < 0) {
                do {
                    printf("\n\nError, ese respuesta no es valida\n");
                    printf("\nIngrese otra respuesta: ");
                    scanf("%i", &op);
                } while (op > 1 || op < 0);
            }
            system("cls");
            printf("C:/\n");
            mostrarArchivos(t, cont, op);
            printf("-------------------------------------------------------------\n\n");
            system("pause");
        case 0:
            break;
        }
    }
}
int CompUNIDAD( l_nodo* l ,char dest[100]){
l_nodo *AX = l;
	while (AX){
		if( strcmp(AX->Nom,dest)== 0){
			return 1;
		}else AX->pUL;

	}

	return 0;
}

void morfosis(char *token, l_nodo **p){
	char *parametro=strtok(token,":"),*valor=parametro;
	valor=strtok(NULL,":");
	printf("parametro: %s | valor: %s\n\n",parametro,valor);
	system("pause");

	if(valor==NULL){
		printf("Error, el valor introducido no es valido. Intentelo de nuevo\n\n");
		system("pause");
	}else{

	if((strcmp(parametro,"n")==0) || (strcmp(parametro,"N")==0)){
		if((strlen(valor)<0)||(strlen(valor)>9)){
			printf("Error, el nombre ingresado excede el limite de longitud. Intente nuevamente\n\n");
			system("pause");
		}else if(verificarExist((*p),valor)==1){
			printf("Error, ya existe un directorio con ese nombre. Intente de nuevo.\n\n");
			system("pause");
		}else{
		strcpy((*p)->Nom,valor);
		printf("\n\nAhora el nombre del directorio es: %s\n\n",(*p)->Nom);
		system("pause");
		}
	}
	else if((strcmp(parametro,"r")==0) || (strcmp(parametro,"R")==0)){
		if(strcmp(valor,"1")==0)
			(*p)->r=1;
		else
			(*p)->r=0;
	}else if((strcmp(parametro,"h")==0) || (strcmp(parametro,"H")==0)){
		if(strcmp(valor,"1")==0)
			(*p)->h=1;
		else
			(*p)->h=0;
	} 
	else{
		printf("Error, el parametro introducido no es valido. Intentelo de nuevo");
		system("pause");
	}
	}
}

void separarD(l_nodo* p, l_nodo* l , l_nodo **AX,l_nodo **posicion,char dest[100], char Nom[9]){
	l_nodo *ANT = NULL;
	*AX = l ;
	char *ruta;
	int contador = 0, fix = 0;

	ruta = strtok (dest,"/ \n");
	
	while (ruta != NULL){		
		
		if (AX != NULL) 
			 if (strcmp (ruta, ".") == 0){
			//	 ANT = (*AX);   cod original

				 	if ((*AX)->pPA != NULL) {
						ANT = (*AX)->pPA;
					}else{
						ANT = (*AX);
					}

				 *AX = p->pFA;
					
				}else if (strcmp (ruta, "..") == 0){

					if (p->pPA != NULL){
						*AX = p->pPA->pFA;	
					}else{
						*AX = p->pFA;	
					}

					if ((*AX)->pPA != NULL) {
						ANT = (*AX)->pPA;
					}else{
						ANT = (*AX);
					}
					
				}else 
			if(strcmp (ruta, (*AX)->Nom) == 0){
									ANT = *AX;
				if ((*AX)->pFA != NULL){
					*AX = (*AX)->pFA;
				}

				printf	("son iguales toke=%s \n" , ruta);
			}else if ((*AX)->pUL) {
				if ((strcmp (ruta, ".") != 0) || (strcmp (ruta, "..") != 0)){
					while (AX){
						if(strcmp (ruta, (*AX)->Nom) == 0){
							printf	("son iguales , en hermanos \n");
							if ((*AX)->pFA != NULL) {
								ANT = *AX;
								*AX = (*AX)->pFA;
							}else{
								ANT = (*AX);
							}
							break;
						}
						else {
							if ((*AX)->pUL != NULL) {
								*AX = (*AX)->pUL;
								//ANT = *AX;
							}else{
								printf	("no son iguales , no tengo mas hermanos \n");
								contador++;
								break;
							}
						}
						}
					}
			}else{
				contador++;
			}
 
		strcpy(Nom, ruta);
		ruta = strtok(NULL, "/ \n");
		printf("token: %s\n", ruta);
		if(ruta == NULL){
			if (contador < 2){
				if ((strcmp (Nom, (*AX)->Nom)==0)){
					ANT = ANT->pPA;
					*AX =  ANT;
				}else{
					if ((strcmp (Nom, ANT->Nom)==0) && (*AX)->pPA != NULL) {
						ANT = (*AX)->pPA->pPA;
						//(*AX) = (*AX)->pPA;
					}
				}
				}else{
					ANT = NULL;
				}

			}
	}
	(*AX) = ANT;

	// si contador es 0 significa que toda la ruta existe
	if (contador == 0){
		if (ANT != NULL){
			if ( ANT->pFA != NULL)
				(*posicion) = ANT->pFA;
			else
				(*posicion) = ANT;
			while (*posicion){
				if(strcmp (Nom, (*posicion)->Nom) == 0){
					break;
				}else  if (strcmp (Nom, ".") == 0){     //cod nuevo
					(*posicion) = ANT;
					break;
				}else if (strcmp (Nom, "..") == 0){
					if ( ANT->pPA != NULL) 
						(*posicion) = ANT->pPA;
					else{
						(*posicion) = ANT;
						break;
					}
				}                                      //fin cod nuevo
				if ((*posicion)->pUL) 
					(*posicion) = (*posicion)->pUL;
				else
					(*posicion) = NULL;
			}
		}else{
			(*posicion) = l;
		}

	}



}
	



void tokenR(l_nodo **p, l_nodo *l, int v){
	int op1 = 0, op2 = 0 ;
	char str[100], *Comando,*pos1,*pos2,*pos3,*pos4,fuente[100],*unidad,destino[100], strAX[9];
l_nodo *respuesta = NULL, *posicion = NULL, *inicio = NULL, *pregunta  = NULL;
	
	fflush(stdin);

	
	fgets(str,100,stdin);
	//strcpy( str,  "MDD C:/temp/datos /n:info" );

//strcpy( str,  " MKD  ./" );

//strcpy( str,  "MKD C:/temp/datos " );
//strcpy( str,  "MKD C:/temp1/datos /r /h" ); // arreglado
//strcpy( str,  "MKD C:/temp2/datos /h" );
//strcpy( str,  "MKD ./../temp/hijo /h" );  
//strcpy( str,  "MKD ./../temp1/hijo1/subhijo1 /h" );
//strcpy( str,  "MKD ./../temp1/hijo1/subhijo1/subsubhijo1 /h" );
//strcpy( str,  "MKD C:/temp1" );  // arreglado
//strcpy( str,  "MKD ./../temp3 /h" );  // arreglado
//strcpy( str,  "MKD ./../temp/datos /h" );
//strcpy( str,  "MKD ./temp /h" ); //arreglado
//strcpy( str,  "MKD C:/temp /h" ); //arreglado
//strcpy( str,  "RMD C:/temp1 " );
//strcpy( str,  " RMD ./.." );
//strcpy( str,  "CHD C:/ ");  //explota
//strcpy( str,  "CHD ./ ");	
//strcpy( str,  "CHD ../ ");  //me deberia dejar en el padre si tiene uno
//strcpy( str,  "CHD ../. ");  //ERROR me deberia dejar en el padre si tiene uno
//strcpy( str,  "CRU C:/" );  
//strcpy( str,  "MVD C:/temp C:/temp1 /o" );  


	fflush(stdin);


	Comando = strtok(str, " \n");
	pos1 = strtok(NULL, "  \n");
	pos2 = strtok(NULL, " \n");
	pos3 = strtok(NULL, " \n");
	pos4 = strtok(NULL, " \n");

	


	printf(" comando = %s\n", Comando );
	printf(" ruta = %s\n", pos1 );
	printf(" opacion1  = %s\n", pos2);
	printf(" opcion2 = %s\n", pos3 );
	printf(" opcion3 = %s\n", pos4 );

	// validacion cantidad de parametros dependiendo del comando
	//if (strcmp(Comando,"MKD") == 0 ) {
			
		//strcpy_s(destino,pos1);	
		/*if (pos1 != NULL ) 
			//unidad = strtok(pos1 , " /");
				if ((unidad != NULL) && (strcmp(unidad,"") != 0 ))
				strcpy_s(destino,pos1);	
				else
				{
					printf ("ERROR, FORMATO INVALIDO DE RUTA ");
					system("pause");
					return;
				}*/
				
			/*else{
				printf ("ERROR FALTAN PARAMETROS");
				system("pause");
				return;
			}*/
			/*if (pos2 != NULL){
				strcpy(op1,pos2);
			}else if (pos3 != NULL){
				strcpy(op2,pos3);
			}*/

if (( strcmp(Comando,"MKD") == 0 ) || ( strcmp(Comando,"mkd") == 0 )){
	if (pos1 == NULL) {
			printf("ERROR , RUTA INVALIDA");
			system("pause");
			return;
		}else{
	strcpy_s(destino,pos1);	
			if (pos3 == NULL){
				op2 = 0;
				op1 = 0;}
			else{
				if ((strcmp (pos3,"/h") == 0) ||(strcmp (pos3,"/H") == 0)){
				op1 = 1;
				}else
				{op1 = 0; 
				}
				if ((strcmp (pos3,"/R") == 0) ||(strcmp (pos3,"/r") == 0)){
				op2 = 1;
				}
				else {op2 = 0;
				} 
			}
			if (pos2 == NULL) {
				op2 = 0;
				op1 = 0;
			}
			else{
				if ((strcmp (pos2,"/h") == 0) || (strcmp (pos2,"/H") == 0)){
				op1 = 1;
				}else
				{op1 = 0; 
				}

				if ((strcmp (pos2,"/R") == 0) ||(strcmp (pos2,"/r") == 0)){
				op2 = 1;
				}
				else {op2 = 0;
				} 
			
			}
			printf ( "opcion1  = %i \n" , op1);
			printf ( "opcion2  = %i \n" , op2);

	 

			separarD(*p,l,&respuesta,&posicion,destino,strAX);
			printf (" NOMBRE DEL DIR = %s \n" , respuesta->Nom);
			printf (" NOMBRE DEL nuevo DIR = %s \n" , strAX);
		
			MKD (&respuesta,strAX , op1, op2);
			
	}	
}
	else
if (( strcmp(Comando,"CHD") == 0 ) || ( strcmp(Comando,"chd") == 0 )){
		if (pos1 == NULL) {
			printf("ERROR , RUTA INVALIDA");
			system("pause");
			return;
		}else{
		strcpy_s(destino,pos1);	
		separarD(*p,l,&respuesta,&posicion,destino,strAX);
		if (posicion == NULL){
		printf("la ruta no es valida\n");
			
			return;
		}
		printf("posicion = %s \n" , posicion  );
		
		*p = posicion;
	}
}
	else
if (( strcmp(Comando,"RMD") == 0 ) || ( strcmp(Comando,"rmd") == 0 )){
	if (pos1 == NULL) {
			printf("ERROR , RUTA INVALIDA");
			system("pause");
			return;
		}
		else{	
	if (pos2 == NULL) {
		op1 = 0;
	}
	else  {
		if ((strcmp (pos2,"/o") == 0) || (strcmp (pos2,"/O") == 0)){
		op1 = 1;
		}else
		{op1 = 0; 
		}
	}
	strcpy_s(destino,pos1);	
	printf ("destino = %s \n",destino);
	system("pause");
	separarD(*p,l,&respuesta,&posicion,destino,strAX);
	*p = l;
	RMD(&respuesta,strAX,op1);
		}
}else
	if (( strcmp(Comando,"CPD") == 0 ) || ( strcmp(Comando,"CPD") == 0 )){
		if (((pos1 == NULL) || (pos2 == NULL)) || (pos4)){
			printf("ERROR , RUTA INVALIDA");
			system("pause");
			return;
		}
		else{	
		if (pos3 == NULL) {
		op1 = 0;
	}
	else {
		if ((strcmp (pos3,"/o") == 0) || (strcmp (pos3,"/O") == 0)){
		op1 = 1;
		}else if ((strcmp (pos3,"/m") == 0) || (strcmp (pos3,"/M") == 0)){
			op1 = 2; 
		}else op1 = 0;
	}
		}
		strcpy_s(fuente,pos1);	
		strcpy_s(destino,pos2);	
	separarD(*p,l,&pregunta,&inicio,fuente,strAX);
	separarD(*p,l,&respuesta,&posicion,destino,strAX);
	CPD (&inicio,&posicion, op1);

	}
	else
	if (( strcmp(Comando,"MVD") == 0 ) || ( strcmp(Comando,"mvd") == 0 )){
		if ((pos1 == NULL) || (pos2 == NULL)){
			printf("ERROR , RUTA INVALIDA");
			system("pause");
			return;
		}
		else{

	if (pos3 == NULL) {
		op1 = 0;
	}
	else{
		if ((strcmp (pos3,"/o") == 0) || (strcmp (pos3,"/O") == 0)){
		op1 = 1;
		}else{
			op1 = 0; 
		}
	}
		strcpy_s(fuente,pos1);	
		strcpy_s(destino,pos2);	
	separarD(*p,l,&pregunta,&inicio,fuente,strAX);
	separarD(*p,l,&respuesta,&posicion,destino,strAX);

	MVD (&inicio,&posicion, op1);

		}
				
	}else
	if ((strcmp(Comando,"MDD") == 0 ) || (strcmp(Comando,"mdd") == 0 )){
		strcpy_s(destino,pos1); 
		if(pos2==NULL){
			printf("Error, no se han introducido los parametros a modificar. Intentar de nuevo");
			system("pause");
		}else{
		delim=strtok(pos2,"/");
		separarD(*p,l,&respuesta,&posicion,destino,strAX);
		morfosis(delim,&posicion);
		}
		strcpy_s(destino,pos1); 
		if(pos3==NULL){
			return;
		}else{
		delim=strtok(pos3,"/");
		separarD(*p,l,&respuesta,&posicion,destino,strAX);
		morfosis(delim,&posicion);
		}
		strcpy_s(destino,pos1); 
		if(pos4==NULL){
			return;
		}else{
		delim=strtok(pos4,"/");
		separarD(*p,l,&respuesta,&posicion,destino,strAX);
		morfosis(delim,&posicion);
		}
	}
	else
	if ( strcmp(Comando,"SHD") == 0 ){
	
	}
	else
	if ( strcmp(Comando,"CSC") == 0 ){
	system("cls");
	}
	else
	if ( strcmp(Comando,"CRU") == 0 ){
			strcpy_s(destino,pos1);	
			unidad = pos1;
			printf (" pos = %s \n" , pos1 );
			unidad = strtok(pos1, "/");
			printf ("  unidad = %s\n", unidad );
			printf ("  pos = %s\n", pos1 );
			printf ("  destino = %s\n", unidad );
			system ("pause");
	}
	else
	if ( strcmp(Comando,"SRU") == 0 ){
	
	}
	else
	if ( strcmp(Comando,"LRU") == 0 ){
	
	}
	else
	if ( strcmp(Comando,"FRU") == 0 ){
	
	}
	else
	if ( strcmp(Comando,"ERU") == 0 ){
	
	}
	else
	if ( strcmp(Comando,"EXIT") == 0 ){
	
	}



	
}




int main() {

	//pUL /* hermanos*/, * pFA /* hijo direc*/, * pPA /* direc padre */;
	int v = 0;
    l_nodo* Root = NULL;
    l_nodo* l = new l_nodo;
    strcpy_s(l->Nom, "C:");
    l->pPA = NULL;
    l->pUL = NULL;
    l->h = 0;
    l->r = 0;
    l->Tip = 'U';
    

	l_nodo* h = new l_nodo;
    strcpy_s(h->Nom, "temp2");
    h->pFA = NULL;
    h->pPA = l;
    h->pUL = NULL;
    h->h = 0;
    h->r = 0;
    h->Tip = 'U';

	l_nodo* t = new l_nodo;
    strcpy_s(t->Nom, "temp1");
   
    t->pPA = l;
    t->pUL = h;
    t->h = 0;
    t->r = 0;
    t->Tip = 'U';

	l_nodo* j = new l_nodo;
    strcpy_s(j->Nom, "hijo");
    j->pFA = NULL;
    j->pUL = NULL;
    j->h = 0;
    j->r = 0;
    j->Tip = 'U';

	

	l_nodo* k = new l_nodo;
    strcpy_s(k->Nom, "hijo1");
    k->pFA = NULL;
    k->pUL = NULL;
    k->h = 0;
    k->r = 0;
    k->Tip = 'U';
	k->pPA = t;

	l_nodo* p = new l_nodo;
    strcpy_s(p->Nom, "temp");
    p->pFA = j;
    p->pPA = l;
    p->pUL = t;
    p->h = 0;
    p->r = 0;
    p->Tip = 'U';
	 j->pPA = p;
	  t->pFA = k;
	     	 l->pFA = p;

	 Root = l;

    time_t now = time(0);
    struct tm* actTime = localtime(&now);

    int op = -1;

    while (op != 0) {
        system("cls");
        printf("-------------------------------------\n");
        printf("Manejo Virtual de Archivos (MVA)\n");
        printf("-------------------------------------\n\n\n");
        imprimirDir(Root);

       printf("%d/%d/%d\n\n", actTime->tm_mday, actTime->tm_mon + 1, actTime->tm_year + 1900);

        printf("Manejo de directorios\n\n");
        printf("1.\tCrear directorio (MKD)\n");
        printf("2.\tCambiar de directorio (CHD)\n");
        printf("3.\tBorrar directorio (RMD)\n");
        printf("4.\tMover directorio (CPD)\n");
        printf("5.\tCopiar directorio (MVD)\n");
        printf("6.\tModificar directorio (MDD)\n");
        printf("7.\tMostrar directorio (SHD)\n");
        printf("0.\tSalir y guardar datos\n");
        printf("-------------------------------------\n\n");
        printf("Su opcion [0-7]: ");

		 scanf(" %i", &op);
		//op = 8;

        system("cls");
        switch (op) {
        case 1:
           // MKD(&Root, op);
            break;
        case 2:
            CHD(&Root, op);
            break;
        case 3:
            //RMD(&Root, op);
            break;
        case 4:
            printf("esta funcion solo acepta caracteres y esta desabilitada \n");
            system("pause");
            break;
        case 5:
			
            printf("esta funcion solo acepta caracteres y esta desabilitada \n");
            system("pause");
          //  CPD(&Root, op);
            break;
        case 6:
            MDD(&Root, op);
            break;
        case 7:
            SHD(Root, op);
            break;
		case 8:
            tokenR(&Root,l,v);
            break;
        }
    }
    system("pause");
    return 0;
}
