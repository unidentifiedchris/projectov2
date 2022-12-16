#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* Integrantes del grupo: Juan Hidalgo, Luis Daniel, Matias Silveira */


struct l_nodo {
    char Nom[9], Ext, fcm[11];
    int r, h, Tip;
    l_nodo* pUL /* hermanos*/, * pFA /* hijo direc*/, * pPA /* direc padre */;
};

/*TOOLS*/

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
 
void elimino (l_nodo *p){
	if (p){
		elimino(p->pFA);
		elimino(p->pUL);
		delete p;
	}

}
			
int verificarExist(l_nodo* p, char x[]) {
    l_nodo* t = p;
    if (strcmp(t->Nom, x) == 0) 
        return 1;
    while (t != NULL) {
        if (strcmp(t->Nom, x) == 0) {
            return 1;
        }
        t = t->pUL;
    };
    return 0;
}

void imprimirDir(l_nodo* p) {
    l_nodo* t = p;
    if (t->pPA) {
        imprimirDir(t->pPA);
        printf("%s/",t->Nom);
    }
    else printf("%s/",t->Nom);
}

void fecha(char fcm[]) {
    time_t now = time(0);
    struct tm* actTime = localtime(&now);
    int d = actTime->tm_mday, m = actTime->tm_mon + 1, y = actTime->tm_year + 1900;
    sprintf(fcm, "%i%i%i", d, m, y);
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

void mostrarDir(l_nodo* p, int cont) {
    int contact = 0;
    while (p != NULL) {
        for (int i = 0; i < cont; i++)
            printf("  ");
        printf("|%c", p->Nom);
        if (Tip == 1) printf("     <D>      %s       r(%i)\n", p->Nom, p->fcm, p->r);
        else printf("      %s       r(%i)\n", p->fcm, p->r);
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
                printf("|%c", p->Nom);
                if (Tip == 1) printf("     <D>      %s       r(%i)   h-\n", p->fcm, p->r,p->h);
                else printf("      %s       r(%i)   h-\n", p->fcm, p->r,p->h);
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
                printf("|%c", p->Nom);
                if (Tip == 1) printf("     <D>      %s       r(%i)   h+\n", p->fcm, p->r,p->h);
                else printf("      %s       r(%i)   h+\n", p->fcm, p->r,p->h);
            else
                printf("|%c", p->Nom);
                if (Tip == 1) printf("     <D>      %s       r(%i)   h+\n", p->fcm, p->r,p->h);
                else printf("      %s       r(%i)   h+\n", p->fcm, p->r,p->h);
            p = p->pUL;
        }
    }
}

void creararchivo(FILE **main, char name[]) {
    *main = fopen(name,"w");
    if (fopen(name,"rb")) {
        printf("Archivo %s fue creado.\n",name);
    } else {
        printf("Archvio %s no se pudo crear.\n",name);
    }
   fclose(*main);
}

void amayus(char a[]) {
    for (int i = 0; a[i]!='\0'; i++) {
        if(a[i] >= 'a' && a[i] <= 'z') {
            a[i] = a[i] -32;
        }
    }
}

void escribir(l_nodo *t,FILE *archivo) {
    fprintf(archivo,"%s ",t->pPA->Nom);
    fprintf(archivo,"%s,%i,%s",t->Nom,t->Tip,t->fcm);
    if (t->r) fprintf(archivo,",r");
    if (t->h) fprintf(archivo,",h"); 
}

void viaje(l_nodo *p, l_nodo **flag, FILE **archivo) {
	l_nodo* t = p, *aux;
    if(t != NULL) {
        fprintf(*archivo,"\n"); escribir(t,*archivo); 
        if (t->pFA != NULL) {
			viaje(p->pFA,flag,archivo);
        } else if (t->pUL != NULL) {
			if (t->pUL != *flag) {
				*flag = t;
                fprintf(*archivo,"\n");
				viaje(p->pUL,flag,archivo);
			}
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
	
/*COMANDOS*/
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
            strcpy(t->Nom, Nombre);
            t->pUL = NULL;
            t->pFA = NULL;
            t->pPA = aux;
            t->h = h;
            t->r = r;
            fecha(t->fcm);
            t->Tip = 1;
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

void SHD(l_nodo* p, char nombre[], int s, int h) {
    l_nodo* t = p;
    l_nodo* c = p;
    while (c && c->pPA!=NULL) c=c->pPA;
/*    if (nombre == NULL)
        t = c;
    else if (!(strcmp(p->Nom,nombre))) {
        //BUSCAR
    } 
    else printf("Archivo no existe.\n"); */

    if (s && h) {
        printf("-----------------------------------------\n");
        printf("%c:/\n",c->Nom);
        mostrarDir(t, 0);
        mostrarArchivos(t, 0, 1);
        printf("-----------------------------------------\n\n");
        system("pause");
    } else if (h) {
        system("cls");
        printf("%c:/\n",t->Nom);
        mostrarArchivos(t, 0, 1);
        printf("-------------------------------------------------------------\n\n");
        system("pause");
    } else if (s) {
        printf("-----------------------------------------\n");
        printf("%c:/\n",c->Nom);
        mostrarDir(t, 0);
        printf("-----------------------------------------\n\n");
        system("pause");
    } else {
         printf("-----------------------------------------\n");
        printf("%c:/\n",c->Nom);
        mostrarDir(t, 0);
        mostrarArchivos(t, 0, 1);
        printf("-----------------------------------------\n\n");
        system("pause");
    }
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
            strcpy(t->Nom, txt);
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

void CRU(l_nodo **p, char und[]) {
	FILE *archivo;
    l_nodo *t = *p;
    l_nodo *aux = new l_nodo;

	while (t && t->pPA != NULL)
		t=t->pPA;
	amayus(und);
    strtok(und,":");
    strcpy(t->Nom,und);
    strcat(t->Nom,":");
    char archnom[] = ".txt";
    strcat(und,archnom);
    creararchivo(&archivo,und);

	aux->pPA = NULL;
	aux->pUL = t;
	aux->pFA = NULL;
	aux->Tip = 1;
}

void FRU(l_nodo **p, char txt[]) { 
    char op;
    l_nodo* t = *p;
    
    while (t != NULL) {
        if (strcmp(t->Nom,txt) == 0) {
            printf("Estas seguro que quieres formatear la unidad logica %s? (S/N)",(*p)->Nom);
            scanf("%c",&op);
            if (op == 'S' || op == 's') {
                eliminarDirHermanos(&(t->pFA));
                printf("Unidad logica %s formateada.",(*p)->Nom);
            }
            else if (op == 'N' || op == 'n')
                printf("Operacion cancelada.\n");
        } else {
            t=t->pUL;
        }
    }
}

void ERU(l_nodo **p, char txt[]) {
    char op;
    char nom[100]; 
    l_nodo *ax = *p;
    while (ax && ax->pPA !=  NULL) {
        ax= ax->pPA;
    }
    printf("Estas seguro que quieres formatear la unidad logica %s? (S/N)",(*p)->Nom);
    scanf("%c",&op);
    if (op == 'S' || op == 's') {
        l_nodo *t = *p;
        strcpy(nom,t->Nom);
        FRU(&t,nom);
        *p = ax->pUL;
        delete(t);
    }
    else if (op == 'N' || op == 'n')
        printf("Operacion cancelada.\n");
}

void SRU(l_nodo *p,char nombre[]) {
    char ext[] = ".txt";
    char nom[100];
    strcpy(nom,p->Nom);
    strcat(nom,ext);
    FILE *archivo;
    archivo = fopen(nombre,"w");
    l_nodo *t = p->pFA;
    while(t != NULL) {
		viaje(t,&t,&archivo);
		t=t->pUL;
    }
    fclose(archivo);
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

l_nodo crearnodo(l_nodo **p, char a[]) {
    char *padre,*pos1,*pos2,*pos3,*pos4,*pos5;
    char tip[2];

    padre = strtok(a,",\n");
    pos1 = strtok(NULL,",\n");
    pos2 = strtok(NULL,",\n");
    pos3 = strtok(NULL,",\n");
    pos4 = strtok(NULL,",\n");
    pos5 = strtok(NULL,",\n");

    l_nodo *t = new l_nodo;
    strcpy(t->Nom,pos1);
    strcpy(tip,pos2);
    if (tip == 1) t->Tip = 1;
    strcpy(t->fcm,pos3);
    if (strcmp(pos4,"r") == 0 || strcmp(pos4,"h") == 0) {
        if (strcmp(pos4,"r") == 0)  t->r=1;
        if (strcmp(pos4,"h") == 0) t->h=1;
    } else if (strcmp(pos4,"r") == 0 && strcmp(pos5,"h") == 0 ) {
        t->r=1;
        t->h=1;
    } else {
        t->r=0;
        t->h=0;
    }
    t->pPA = *p;
    t->pFA = NULL;
    t->pUL = NULL;

    return *t;
}

void LRU(l_nodo **p, char *archnom, char nombre[]) {
    FILE *main;
    char a[100];
    char *pos1;
    main = fopen(archnom,"r");
    // Crear unidad logica
    CRU(p,nombre);
    l_nodo *t = *p;
    while(!(feof(main))) {
        fscanf(main,"%s",a);
        pos1 = strtok(a," ");
        if (strcmp(pos1,t->Nom) == 0)
            crearnodo(&t,a);
    /*
        
        l_nodo *t = new l_nodo;
        if (strtok(a," ") == "pFA")
            (*p)->pFA = t;
        else if (strtok(a," ") == " ") {
            //Crear hijo, recursivamente
        }
        fflush(stdin);
        fscanf(main,"%s %c %s %i %i",t->Nom,t->Tip,t->fcm,t->r,t->h);
        */
    }

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

void EXIT(l_nodo *p) {
	l_nodo *t = p;
	if (t->pUL && t) {
		EXIT(t->pUL);
		SRU(t,t->Nom);
	}
}

/*PRINCIPALES*/

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

		
			}else if ((*AX)->pUL) {
				if ((strcmp (ruta, ".") != 0) || (strcmp (ruta, "..") != 0)){
					while (AX){
						if(strcmp (ruta, (*AX)->Nom) == 0){
					
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
	
int tokenR(l_nodo **p, l_nodo *l){
	int op1 = 0, op2 = 0 ;
	char str[100], *Comando,*pos1,*pos2,*pos3,*pos4,fuente[100],*unidad,destino[100], strAX[9];
l_nodo *respuesta = NULL, *posicion = NULL, *inicio = NULL, *pregunta  = NULL;
	
	fflush(stdin);

	
	fgets(str,100,stdin);

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
			
		//strcpy(destino,pos1);	
		/*if (pos1 != NULL ) 
			//unidad = strtok(pos1 , " /");
				if ((unidad != NULL) && (strcmp(unidad,"") != 0 ))
				strcpy(destino,pos1);	
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
		}else{
	strcpy(destino,pos1);	
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
			else{if (op1 == 0) {
				if ((strcmp (pos2,"/h") == 0) || (strcmp (pos2,"/H") == 0)){
				op1 = 1;
				}else
				{op1 = 0; 
				}
			}
				if (op2 == 0) {
				if ((strcmp (pos2,"/R") == 0) ||(strcmp (pos2,"/r") == 0)){
				op2 = 1;
				}
				else {op2 = 0;
				} 
			}
			}
			printf ( "opcion1  = %i \n" , op1);
			printf ( "opcion2  = %i \n" , op2);

	 

			separarD(*p,l,&respuesta,&posicion,destino,strAX);
			printf (" NOMBRE DEL DIR = %s \n" , respuesta->Nom);
			printf (" NOMBRE DEL nuevo DIR = %s \n" , strAX);

			MKD (&respuesta,strAX , op1, op2);
			system("pause");
	}	
}
	else
if (( strcmp(Comando,"CHD") == 0 ) || ( strcmp(Comando,"chd") == 0 )){
		if (pos1 == NULL) {
			printf("ERROR , RUTA INVALIDA");
			system("pause");
		}else{
		strcpy(destino,pos1);	
		separarD(*p,l,&respuesta,&posicion,destino,strAX);
		if (posicion == NULL){
		printf("la ruta no es valida\n");
			system("pause");
		}
		printf("posicion = %s \n" , posicion  );
			system("pause");
		*p = posicion;
	}
}
	else
if (( strcmp(Comando,"RMD") == 0 ) || ( strcmp(Comando,"rmd") == 0 )){
	if (pos1 == NULL) {
			printf("ERROR , RUTA INVALIDA");
			system("pause");
		}
		else{	
	if (pos2 == NULL) {
		op1 = 0;
	}
	else if (op1 == 0) {
		if ((strcmp (pos2,"/o") == 0) || (strcmp (pos2,"/O") == 0)){
		op1 = 1;
		}else
		{op1 = 0; 
		}
	}
	strcpy(destino,pos1);	
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
		strcpy(fuente,pos1);	
		strcpy(destino,pos2);	
	separarD(*p,l,&pregunta,&inicio,fuente,strAX);
	separarD(*p,l,&respuesta,&posicion,destino,strAX);
	//CPD (&inicio,&posicion, op1);

	}
	else
	if (( strcmp(Comando,"MVD") == 0 ) || ( strcmp(Comando,"mvd") == 0 )){
		if ((pos1 == NULL) || (pos2 == NULL)){
			printf("ERROR , RUTA INVALIDA");
			system("pause");
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
		strcpy(fuente,pos1);	
		strcpy(destino,pos2);	
	separarD(*p,l,&pregunta,&inicio,fuente,strAX);
	separarD(*p,l,&respuesta,&posicion,destino,strAX);

	MVD(&inicio,&posicion, op1);

		}
				
	}else
	if ((strcmp(Comando,"MDD") == 0 ) || (strcmp(Comando,"mdd") == 0 )){
		strcpy(destino,pos1); 
		Comando = strtok(pos2, ":");
		if (strcmp (Comando,"/h")){
			printf("ERROR FALTAN PARAMETROS \n");
			system("pause");
		}
			printf("%s \n", Comando);
			system("pause");
		
		separarD(*p,l,&respuesta,&posicion,destino,strAX);
	}
	else
	if ( strcmp(Comando,"SHD") == 0 ){
        strcpy(destino,pos1);
        if (pos2 == "/s" && pos3 == "/h") SHD(*p,destino,1,1);
        else if (pos2 == "/h") SHD(*p,destino,0,1);
        else if (pos2 == "/s") SHD(*p,destino,1,0);
        else SHD(*p,destino,0,0);
	}
	else
	if ( strcmp(Comando,"CSC") == 0 ){
	system("cls");
	}
	else
	if (( strcmp(Comando,"CRU") == 0 ) || ( strcmp(Comando,"cru") == 0 )){
			strcpy(destino,pos1);	
			unidad = pos1;
			printf (" pos = %s \n" , pos1 );
			unidad = strtok(pos1, "/");
			printf ("  unidad = %s\n", unidad );
			printf ("  pos = %s\n", pos1 );
			printf ("  destino = %s\n", unidad );
            CRU(p,pos1);
			system ("pause");
	}
	else
	if ( strcmp(Comando,"SRU") == 0 ){
        strcpy(destino,pos1);	
			unidad = pos1;
			printf (" pos = %s \n" , pos1 );
			unidad = strtok(pos1, ":/");
			printf ("  unidad = %s\n", unidad );
			printf ("  pos = %s\n", pos1 );
			printf ("  destino = %s\n", unidad );
            SRU(*p,pos1);
			system ("pause");
	}
	else
	if (( strcmp(Comando,"LRU") == 0 ) || ( strcmp(Comando,"lru") == 0 )){
        strcpy(fuente,pos1);	
        strcpy(destino,pos2);
        unidad = strtok(pos2, "/");
        printf ("  unidad = %s\n", unidad );
        printf ("  pos = %s\n", pos1 );
        printf ("  destino = %s\n", unidad );
       // LRU(p,fuente,destino);
        system ("pause");
	}
	else
	if (( strcmp(Comando,"FRU") == 0 ) || ( strcmp(Comando,"fru") == 0 )){
        strcpy(destino,pos1);
        FRU(p,destino);
	}
	else
	if (( strcmp(Comando,"ERU") == 0 ) || ( strcmp(Comando,"eru") == 0 )){
        strcpy(destino,pos1);
        ERU(p,destino);
	}
	else
	if (( strcmp(Comando,"EXIT") == 0 ) || ( strcmp(Comando,"exit") == 0 )){
        EXIT(*p);
        return 0;
	}
    return -1;
}


int main() {
    l_nodo* Root = NULL;
    l_nodo* l = new l_nodo;
    l_nodo* t = new l_nodo;
    l->pFA = NULL;
    l->pPA = NULL;
    l->pUL = NULL;
    l->h = 0;
    l->r = 0;
    l->Tip = 0;
    strcpy(l->Nom, "C:");
    
    Root = l;
    FILE *main;
    time_t now = time(0);
    char archnom[] = "C.txt";
    struct tm* actTime = localtime(&now);
    int op = -1;
    char randoma[100];

    if (main = fopen("C.txt","rb")) {
        if (!(feof(main))) {
            fscanf(main,"%s\n",randoma);
            Root->pFA = t;
            *t = crearnodo(&Root,randoma);
            //LRU(&Root,archnom,Root->Nom);
        }
        while(op != 0) {
            printf("\t");
            imprimirDir(Root);
            printf("> ");
            op = tokenR(&Root,l);
        }
        system("pause");
        return 0;
    }
    else return 0;
}
