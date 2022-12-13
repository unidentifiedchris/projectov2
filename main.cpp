#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Integrantes del grupo: Juan Hidalgo, Luis Daniel, Matias Silveira */


struct l_nodo {
    char Nom[9], Ext, Tip, fcm[11];
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
                       
                            system("cls");
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


void RMD(l_nodo** p, int x) {
    l_nodo* t = (*p)->pFA, * pux, * del;
    char txt[9];
    while (x != 0) {
        system("cls");
        printf("-----------------------------------\n");
        printf("Manejo Virtual de Archivos (MVA)\n");
        printf("[3.Eliminar directorio (RMD)]\n");
        printf("-----------------------------------\n\n");
        imprimirDir(*p);
        printf("1.\tNombre del directorio a borrar\n");
        printf("0.\tSalir\n");
        printf("Su opcion [0-2]: ");
        scanf(" %i", &x);
        t = (*p)->pFA;

        switch (x) {
        case 1:
            system("cls");
            printf("-----------------------------------\n");
            printf("Indique el nombre del directorio\n");
            printf("-----------------------------------\n\n");
            scanf(" %8s", txt, 9);
            pux = *p;
            if ((t == NULL) || (verificarExist(t, txt) == 0)) {
                printf("Error, ese directorio no existe en el directorio actual\n\n");
                system("pause");
                return;
            }
            else {
                if ((strcmp(pux->pFA->Nom, txt) == 0) && (pux->pFA->pUL == NULL)) {
                    if (t->pUL == NULL) {
                        if ((strcmp(pux->pFA->Nom, txt) == 0) && (t->r == 1)) {
                            printf("El directorio que quieres borrar esta como solo lectura");
                            system("pause");
                            return;
                        }
                        if (t->pFA == NULL) {
                            pux->pFA = NULL;
                            delete t;
                        }
                        else if (t->pFA) {
                            while (x != 0) {
                                printf(" el directorio selecionado tiene hijos quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                scanf("%i", &x);
                                switch (x)
                                {
                                case 1:
                                    eliminarDir(&t, txt);
                                    pux->pFA = NULL;
                                    x = -1;

                                    return;
                                default:
                                    break;
                                }
                            }
                        }
                        // eliminar
                        printf("elimine el unico  nodo");
                        system("pause");
                        break;
                    }
                }
                else {
                    if ((strcmp(pux->pFA->Nom, txt) == 0) && (t->pUL)) {
                        if ((strcmp(pux->pFA->Nom, txt) == 0) && (pux->pFA->r == 1)) {
                            printf("El directorio que quieres borrar esta como solo lectura");
                            system("pause");
                            return;
                        }
                        if (t->pFA == NULL) {
                            pux->pFA = t->pUL;
                            delete t;
                        }
                        else if (t->pFA) {
                            while (x != 0) {
                                printf(" el directorio selecionado tiene hijos quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                scanf("%i", &x);
                                switch (x)
                                {
                                case 1:
                                    pux->pFA = t->pUL;
                                    eliminarDir(&t, txt);
                                    x = -1;

                                    return;
                                default:
                                    break;
                                }
                            }
                        }
                        //eliminar 
                        printf("elimine el primer  nodo");
                        system("pause");
                        break;

                    }
                }
                while (t->pUL) {

                    if ((strcmp(t->pUL->Nom, txt) == 0) && (t->pUL->r == 1)) {
                        printf("El directorio que quieres borrar esta como solo lectura");
                        system("pause");
                        return;
                    }
                    if (strcmp(t->pUL->Nom, txt) == 0) {
                        if (t->pUL->pUL == NULL) {

                            if (t->pUL->pFA == NULL) {
                                del = t->pUL;
                                t->pUL = NULL;
                                delete del;
                            }
                            else if (t->pUL->pFA) {
                                while (x != 0) {
                                    printf(" el directorio selecionado tiene hijos quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                    scanf("%i", &x);
                                    switch (x)
                                    {
                                    case 1:
                                        del = t->pUL;
                                        t->pUL = NULL;
                                        eliminarDir(&del, txt);
                                        x = -1;
                                        return;
                                    default:
                                        break;
                                    }
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
                            else if (t->pUL->pFA) {
                                while (x != 0) {
                                    printf(" el directorio selecionado tiene hijos quieres eliminarlo con sus subdirectorios ((0)para no y (1)para si)  \n");
                                    scanf("%i", &x);
                                    switch (x)
                                    {
                                    case 1:
                                        t->pUL = del->pUL;
                                        eliminarDir(&del, txt);
                                        x = -1;
                                        return;
                                    default:
                                        break;
                                    }
                                }
                            }
                        }
                            system("pause");
                            break;
                    }

                        t = t->pUL;
                        printf("me movi");
                        system("pause");

                }


               
            } 
            break;
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

void buscarToken(l_nodo** p, char cad[], int cont) {
    int i = cont;
    while (cad[i] != '\0') {
        if ((*p)->Nom == cad[i]) {
            break;
        }
        else {
            while ((*p)->Nom != cad[i]) {
                *p = (*p)->pUL;
            }
            if (cad[i + 2] = '/0')
                break;
            else if (((*p)->pFA != NULL) && (cad[i + 2] != '/0')) {
                cont += 2;
                buscarToken(&((*p)->pFA), cad, cont);
            }
            else
                break;
        }
    }
}

/void MVD(l_nodo* p, int x) {
    l_nodo* t = *p, * u = *p, * aux = new l_nodo;
    char txt[100];
    int i = 0, cont = 0;
    printf("-----------------------------------\n");
    printf("Manejo Virtual de Archivos (MVA)\n");
    printf("[4.Mover directorio (MVD)]\n");
    printf("-----------------------------------\n\n");
    imprimirDir(*p);
    printf("1.\tNombre del directorio\n");
    printf("0.\tSalir\n");
    printf("Su opcion [0-1]: ");
    scanf("%i", &x);

    switch (x) {
    case 1:
        if (t->pPA == NULL) {
            system("cls");
            printf("------------------------------------------------------------\n");
            printf("Error, se encuentra actualmente en la unidad logica\n");
            printf("La unidad logica no se puede mover a un directorio\n");
            printf("------------------------------------------------------------\n\n");
            system("pause");
        }
        else if (u->r == 1) {
            printf("------------------------------------------------------------\n");
            printf("Error, se encuentra actualmente en un archivo de\n");
            printf("solo lectura, este archivo no se puede mover\n");
            printf("------------------------------------------------------------\n\n");
        }
        else {
            system("cls");
            printf("------------------------------------------------------------\n");
            printf("El directorio actual se movera a otra locacion en el sistema\n");
            printf("Ingrese la direccion del directorio al que movera el actual:\n");
            printf("------------------------------------------------------------\n\n");
            printf("C:/");
            fflush(stdin);
            gets_s(txt);
            strcpy_s(aux->Nom, u->Nom);
            aux->pUL = NULL;
            aux->pFA = u->pFA;
            aux->h = u->h;
            aux->r = u->r;
            aux->Tip = u->Tip;
            //fecha(aux->fcm);

            while (t->pPA->pPA != NULL) {
                t = t->pPA;
            }

            buscarToken(&t, txt, cont);
            aux->pPA = t;

            if (verificarExist(t->pFA, u->Nom) == 1) {
                printf("------------------------------------------------------------\n");
                printf("El directorio a donde se movera el actual ya contiene un\n");
                printf("directorio de nombre %c\n\n", u->Nom);
                printf("Desea omitirlo (1) o sobreescribirlo (2)?\n");
                printf("------------------------------------------------------------\n\n");
                scanf("%i", &x);
                if (x < 1 || x>2) {
                    do {
                        system("cls");
                        printf("Error, esa no es una respuesta valida\n");
                        printf("Ingrese otra respuesta [1-2]\n\n");
                        scanf("%i", &x);
                    } while (x < 1 || x>2);
                }
                if (x == 1) {
                    t = t->pFA;
                    while (t->pUL != NULL) {
                        t = t->pUL;
                    }
                    strcpy_s(aux->Nom, u->Nom);           
                    aux->pUL = NULL;
                    aux->pFA = u->pFA;
                    aux->pPA = t->pPA;
                    aux->h = u->h;
                    aux->r = u->r;
                    aux->Tip = u->Tip;
                    //fecha(aux->fcm);
                    t->pUL = aux;
                    if ((*p)->pUL == NULL)
                        *p = (*p)->pPA;
                    else
                        *p = (*p)->pUL;
                    delete u;
                    printf("\n\n");
                    system("pause");
                }
                else if (x == 2) {
                    t = t->pFA;
                    while (t->pUL != NULL) {
                        t = t->pUL;
                        if (t->Nom == u->Nom) {
                            t = u;
                            if ((*p)->pUL == NULL)
                                *p = (*p)->pPA;
                            else
                                *p = (*p)->pUL;
                            *p = (*p)->pUL;
                            delete u;
                            printf("\n\n");
                            system("pause");
                        }
                    }
                }
            }
            else if (t->pFA == NULL) {
                t->pFA = aux;
                if ((*p)->pUL == NULL)
                    *p = (*p)->pPA;
                else
                    *p = (*p)->pUL;
                delete u;
                printf("\n\n");
                system("pause");
            }
            else if (t->pFA != NULL) {
                t = t->pFA;
                while (t->pUL != NULL) {
                    t = t->pUL;
                }
                t->pUL = aux;
                if ((*p)->pUL == NULL)
                    *p = (*p)->pPA;
                else
                    *p = (*p)->pUL;
                delete u;
                printf("\n\n");
                system("pause");
            }
        }
        break;
    case 0:
        break;                      //Problema actual: si mueve el directorio pero a la hora de ejecutar el imprimir todo del 7 explota
    }
}


void CPD(l_nodo** p, int x) {
    l_nodo* t = *p, * u = *p, * aux = new l_nodo;
    char txt[100];
    int i = 0, cont = 0;
    printf("-----------------------------------\n");
    printf("Manejo Virtual de Archivos (MVA)\n");
    printf("[5.Copiar directorio (CPD)]\n");
    printf("-----------------------------------\n\n");
    imprimirDir(*p);
    printf("1.\tNombre del directorio\n");
    printf("0.\tSalir\n");
    printf("Su opcion [0-1]: ");
    scanf("%i", &x);

    switch (x) {
    case 1:
        if (t->pPA == NULL) {
            system("cls");
            printf("------------------------------------------------------------\n");
            printf("Error, se encuentra actualmente en la unidad logica\n");
            printf("La unidad logica no se puede copiar a un directorio\n");
            printf("------------------------------------------------------------\n\n");
            system("pause");
        }
        else {
            system("cls");
            printf("------------------------------------------------------------\n");
            printf("El directorio actual se copiara a otra locacion en el sistema\n");
            printf("Ingrese la direccion del directorio al que movera el actual:\n");
            printf("------------------------------------------------------------\n\n");
            printf("C:/");
            fflush(stdin);
            gets_s(txt);
            strcpy_s(aux->Nom, u->Nom);     
            aux->pUL = NULL;
            aux->pFA = u->pFA;
            aux->h = u->h;
            aux->r = u->r;
            aux->Tip = u->Tip;
            //fecha(aux->fcm);

            while (t->pPA->pPA != NULL) {
                t = t->pPA;
            }

            buscarToken(&t, txt, cont);
            aux->pPA = t;

            if (verificarExist(t->pFA, u->Nom) == 1) {
                printf("------------------------------------------------------------\n");
                printf("El directorio a donde se copiara el actual ya contiene un\n");
                printf("directorio de nombre %c\n\n", u->Nom);
                printf("Desea omitirlo (1) o sobreescribirlo (2)?\n");
                printf("------------------------------------------------------------\n\n");
                scanf("%i", &x);
                if (x < 1 || x>2) {
                    do {
                        system("cls");
                        printf("Error, esa no es una respuesta valida\n");
                        printf("Ingrese otra respuesta [1-2]\n\n");
                        scanf("%i", &x);
                    } while (x < 1 || x>2);
                }
                if (x == 1) {
                    t = t->pFA;
                    while (t->pUL != NULL) {
                        t = t->pUL;
                    }
                    strcpy_s(aux->Nom, u->Nom);
                    aux->pUL = NULL;
                    aux->pFA = u->pFA;
                    aux->pPA = t->pPA;
                    aux->h = u->h;
                    aux->r = u->r;
                    aux->Tip = u->Tip;
                    //fecha(aux->fcm);
                    t->pUL = aux;
                }
                else if (x == 2) {
                    t = t->pFA;
                    while (t->pUL != NULL) {
                        t = t->pUL;
                        if (t->Nom == u->Nom) {
                            t = u;
                        }
                    }
                }
            }
            else if (t->pFA == NULL) {
                t->pFA = aux;
            }
            else if (t->pFA != NULL) {
                t = t->pFA;
                while (t->pUL != NULL) {
                    t = t->pUL;
                }
                t->pUL = aux;
            }
            printf("Se ha copiado el directorio de forma exitosa\n");
            system("pause");
        }
        break;
    case 0:
        break;
    }
}*/


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
        printf("|%c     <%c>      %s       r(%i)\n", p->Nom, p->Tip, p->fcm, p->r);
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
                printf("|%c     <%c>      %s       r(%i)   h-\n", p->Nom, p->Tip, p->fcm, p->r, p->h);
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

void separarD(l_nodo* p, l_nodo* l ,l_nodo **AX,char dest[100], char Nom[9]){
	l_nodo *ANT = NULL;
	*AX = l ;
	char *ruta;
	int contador = 0;
	ruta = strtok (dest,"/");
	
	while (ruta != NULL){		
		
		if (AX != NULL) 
			 if (strcmp (ruta, ".") == 0){
					*AX = p;
				}else if (strcmp (ruta, "..") == 0){	
					*AX = p->pPA->pFA;
					ANT = (*AX)->pPA;
				}else 
			if(strcmp (ruta, (*AX)->Nom) == 0){
				ANT = *AX;
				if ((*AX)->pFA != NULL) *AX = (*AX)->pFA;
				printf	("son iguales toke=%s \n" , ruta);
			}else if ((*AX)->pUL) {
				if ((strcmp (ruta, ".") != 0) || (strcmp (ruta, "..") != 0)){
					while (AX){
						if(strcmp (ruta, (*AX)->Nom) == 0){
							printf	("son iguales , en hermanos \n");
							if ((*AX)->pFA != NULL) 
								*AX = (*AX)->pFA;
							ANT = *AX;
							break;
						}
						else {
							if ((*AX)->pUL != NULL) {
								*AX = (*AX)->pUL;
								//ANT = *AX;
							}else{
								printf	("no son iguales , no tengo mas hermanos \n");
								break;
							}
						}
						}
					}
			}else
			{

			}
 
		strcpy(Nom, ruta);
		ruta = strtok(NULL, "/ ");
		printf("token: %s\n", ruta);
		if(ruta == NULL){
			if ((strcmp (Nom, (*AX)->Nom)==0)){
				ANT = ANT->pPA;
				*AX =  ANT;
			}
		}
/*		else{
			if ((*AX)->pFA == NULL){
				strcpy(Nom, ruta);
				break;
			}
		}
		*/
	}
	(*AX) = ANT;

	printf	("saliendo  ANT NOM = %s \n" ,ANT->Nom);
	printf("directorio: %s\n", Nom);

}
	
	




void tokenR(l_nodo **p, l_nodo* l){
	int op1, op2;
	char str[100], *Comando,*pos1,*pos2,*pos3,*pos4,*fuente,*unidad,destino[100], strAX[9];
l_nodo *respuesta = NULL;
	fflush(stdin);

	
	fgets(str,100,stdin);
	//strcpy( str,  "MDD C:/temp/datos /n:info" );

//strcpy( str,  " MKD  ./" );

//strcpy( str,  "MKD C:/temp/datos " );
//strcpy( str,  "MKD C:/temp1/datos /r /h" );
//strcpy( str,  "MKD C:/temp2/datos /h" );
//strcpy( str,  "MKD ./../temp/hijo /h" );
//strcpy( str,  "MKD ./../temp3 /h" );   
//strcpy( str,  "MKD ./../temp/datos /h" );
//strcpy( str,  "MKD C:/temp1 /h" );


	fflush(stdin);
	printf("%s\n", str);

	Comando = strtok(str, " ");
	pos1 = strtok(NULL, " ");
	pos2 = strtok(NULL, " ");
	pos3 = strtok(NULL, " ");
	pos4 = strtok(NULL, " ");



	printf(" comando = %s\n", Comando );
	printf(" ruta = %s\n", pos1 );
	printf(" opacion1  = %s\n", pos2);
	printf(" opcion2 = %s\n", pos3 );
	printf(" opcion3 = %s\n", pos4 );

	// validacion cantidad de parametros dependiendo del comando
	if (strcmp(Comando,"MKD") == 0 ) {
			
		strcpy_s(destino,pos1);	
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
				
			}else{
				printf ("ERROR FALTAN PARAMETROS");
				system("pause");
				return;
			}
			/*if (pos2 != NULL){
				strcpy(op1,pos2);
			}else if (pos3 != NULL){
				strcpy(op2,pos3);
			}*/

	if ( strcmp(Comando,"MKD") == 0 ){
	printf("entre\n");
	

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
	system("pause");
	 

	separarD(*p,l,&respuesta,destino,strAX);
	printf (" NOMBRE DEL DIR = %s \n" , respuesta->Nom);
	printf (" NOMBRE DEL nuevo DIR = %s \n" , strAX);

	MKD (&respuesta,strAX , op1, op2);

	}	system("pause");

	//else
	/*if ( strcmp(token,"CHD") == 1 ) {
		while (token != NULL){
		strcpy(strAX, token);
		printf("token: %s\n", token);
		token = strtok(NULL, "/ ");
		}
	}
	else
	 if ( strcmp(token,"RMD") == 1 ){
	
	}
	else
	if ( strcmp(token,"CPD") == 1 ){
	
	}
	else
	if ( strcmp(token,"MVD") == 1 ){
	
	}
	else
	if ( strcmp(token,"SHD") == 1 ){
	
	}
	else
	if ( strcmp(token,"CSC") == 1 ){
	
	}
	else
	if ( strcmp(token,"CRU") == 1 ){
	
	}
	else
	if ( strcmp(token,"SRU") == 1 ){
	
	}
	else
	if ( strcmp(token,"LRU") == 1 ){
	
	}
	else
	if ( strcmp(token,"FRU") == 1 ){
	
	}
	else
	if ( strcmp(token,"ERU") == 1 ){
	
	}
	else
	if ( strcmp(token,"EXIT") == 1 ){
	
	};*/



	
}


int main() {
    l_nodo* Root = NULL;
    l_nodo* l = new l_nodo;
    strcpy_s(l->Nom, "C:");
    l->pFA = NULL;
    l->pPA = NULL;
    l->pUL = NULL;
    l->h = 0;
    l->r = 0;
    l->Tip = 'U';
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
        system("cls");
        switch (op) {
        case 1:
            MKD(&Root, op);
            break;
        case 2:
            CHD(&Root, op);
            break;
        case 3:
            RMD(&Root, op);
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
            tokenR(&Root,l);
            break;
        }
    }
    system("pause");
    return 0;
}
