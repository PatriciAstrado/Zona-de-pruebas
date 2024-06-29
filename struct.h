#ifndef stdlib_h
#define stdlib_h
#include <stdlib.h>
#endif /* stdlid_h */

#ifndef stdio_h
#define stdio_h
#include <stdio.h>
#endif /* stdio_h */

#ifndef string_h
#define string_h
#include <string.h>
#endif /* string_h */

typedef struct _enterolargo{    //lista para numeros en formato int
    int cantidadDigitos;//cantidad de dígitos
    char signo;//signo 0=menos, 1 = mas   
    struct Nodo *siguiente;//direccion a digitos empezando la lista 
}EnteroLargo;

typedef struct Nodo{
    int digito;
    struct Nodo *siguiente;
}Nodo;
