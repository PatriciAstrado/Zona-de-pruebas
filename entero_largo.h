//
//  entero_largo.h
//  Taller 2 - EdD - 2024.1
//
//  Plantilla librería implementación EnteroLargo

#ifndef lista_enlazada_h
#define lista_enlazada_h
#include "lista_enlazada.h"
#endif /* lista_enlazada_h */

//Puede agregar otras librerías implementadas en su proyecto o
//de la librería estandar del lenguaje C.

//
//Definición estructura de datos
//

//
//Prototipos interfaz
//
EnteroLargo *creaEnteroLargoDesdeStr(char *numero);
char *creaStrDesdeEnteroLargo(EnteroLargo *numero);
void copiaEnteroLargo(EnteroLargo *destino, EnteroLargo *fuente);
void eliminaEnteroLargo(EnteroLargo *numero);
// !!!
//La siguiente función es necesaria para que funcionen las pruebas automáticas
//Abajo se porporciona una plantilla de implementación que DEBE modificar para
//que funcione: debe agregar las nombres de los campos de su estructura y la
//función que muestra el contenido de la lista enlazada de dígitos
void muestraEnteroLargo(EnteroLargo *numero);
// !!!
void escribeEnteroLargo(char *nombreArchivo, EnteroLargo *numero);
EnteroLargo *leeEnteroLargo(char *nombreArchivo);
int igualEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2);
int mayorMenorEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2);
EnteroLargo *sumaEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2);
EnteroLargo *restaEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2);
EnteroLargo *multiplicaEnteroLargo(EnteroLargo *multiplicando, EnteroLargo *multiplicador);
EnteroLargo *divideEnteroLargo(EnteroLargo *dividendo, EnteroLargo *divisor);

//
//Implememntaciones
//
EnteroLargo *creaEnteroLargoDesdeStr(char *numero){
    
    EnteroLargo *unEnteroLargo = (EnteroLargo*)malloc(sizeof(EnteroLargo));    //creamos y damos memoria
    unEnteroLargo->siguiente = NULL; //asignamos memoria al siguiente
    int valor,i=0;
    
    //unEnteroLargo ->cantidadDigitos = sizeof(numero)
    unEnteroLargo ->cantidadDigitos = strlen(numero);
        //guardamos la cantidad de digitos 
    
    if(numero[0] == '-'){//preguntamos si el primer dato en el str es - ; si es el caso avanzamos en 1 la lectura del str y asignamos guardamos el signo
        i++;
        unEnteroLargo->signo = '-';
    }else{
        unEnteroLargo->signo = '+';
    }
    
    while(i<(unEnteroLargo->cantidadDigitos)){ //mientras i sea menor o igual a la cantidad de digitos en el str
        valor = convertirCharInt(numero[i]); //convertimos el char en int
        agregarElemento(&(unEnteroLargo->siguiente),valor); //agregamos el int a la lista en la siguiente posicion
        i++;
    }
    
    return(unEnteroLargo);
}


void strToInt(char *num){
    
}

char *creaStrDesdeEnteroLargo(EnteroLargo *numero){
    int tamanoStr = numero->cantidadDigitos; 
    int valor, negativo = 0;
    char digito;
    
    char *auxStr = (char *)malloc((tamanoStr) * sizeof(char)); //espacio para el string satanico lo se

    if (numero->signo == '-') {//preguntamos si el signo es negativo para un int importante
        auxStr[0] = '-'; 
        negativo = 1;
    }else{
        auxStr[0] = '+'; 
    }
                    //NO SACAR, el negativo es importante como dije, si no esta , cuando se trabaje con el signo negativo, al final del string quedara un \ dependiendo de la cantidad de espacios vacios no asignados haya
    for (int i = 0; i < tamanoStr-negativo; i++) {      // mas '\' mas espacio extra tiene el string
        //buscamos el valor segun la posicion
        valor = leerNumeroLista(numero->siguiente, i);
        digito = convertirIntChar(valor);//convertimos el formato del valor a char
        
        auxStr[i + negativo] = digito; //acoplamos en la posicion el valor
    }
    
    auxStr[tamanoStr + negativo] = '\0';//aseguramos que el string termine en el formato correcto
    
    return auxStr;
    
}


void copiaEnteroLargo(EnteroLargo *destino, EnteroLargo *fuente){
    int num,negativo=0;

    //printf("%c",fuente->signo);
    liberarDigitos(destino->siguiente);//eliminamos los digitos guardados dentro del entero largo via liberando la memoria
    destino->siguiente = NULL; //aseguramos que existe donde guardar dichos valores

    //cambiamos directamente los valores de destino por los de fuente
    destino->signo = fuente->signo;
    if(destino->signo == '-'){//preguntamos si hay negativo
        negativo = 1;
    }
//    destino->cantidadDigitos = fuente->cantidadDigitos;
    int i=0;
    Nodo *nodo1 = fuente->siguiente;
                        //NO SACAR ESTO, el negativo asegura que no haya datos fanatasma"" por decirlo de un modo. 
    while (nodo1 != NULL) { //si lo eliminan cuando se trabaje con negativos el enterolargo finalizara con un -1 , que es un valor de error dentro de lista_enlazada
        
        num = nodo1->digito; //buscamos el valor dentro de la fuente
        agregarElemento(&(destino->siguiente), num);//se lo pegamos al destion y fin
        i++;
        nodo1 = nodo1->siguiente;
    }
    destino->cantidadDigitos=i;
}


void eliminaEnteroLargo(EnteroLargo *numero){
    //...
}

//ESTA FUNCIÓN DEBE EXISTIR PARA QUE FUNCIONEN LAS PRUEBAS AUTOMÁTICAS
//PARA QUE FUNCIONE DEBE HACER LOS CAMBIOS INDICADOS EN LOS COMENTARIOS
void muestraEnteroLargo(EnteroLargo *numero){
    if(numero !=NULL){
        //reemplace <CANTIDAD_DIGITOS> por el campo de EnteroLargo que contiene
        //la cantidad de dígitos del número
        printf("[%d]",numero->cantidadDigitos);
        //reemplace <SIGNO> por el campo de EnteroLargo que contiene
        //el signo del número en su estructura
        printf("%c",numero->signo);
        //reemplace <muestraListaDigitos(<DIGITOS>)> por la función de la lista
        //enlazada que muestra el contenido de la lista de digitos (<DIGITOS>)
        //del EnteroLargo
        //<muestraListaDigitos(<DIGITOS>)>;
        imprimirLista(numero->siguiente);
    }else{
        printf("NULL");
    }
}


void escribeEnteroLargo(char *nombreArchivo, EnteroLargo *numero) {
    // Verificar que el número no sea nulo
    if (numero == NULL) {
        printf("El número proporcionado es nulo.\n");
        return;
    }

    // Abrir el archivo en modo binario para escritura
    FILE *archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s para escribir.\n", nombreArchivo);
        return;
    }

    // Escribir el signo en el archivo
    if (fwrite(&(numero->signo), sizeof(char), 1, archivo) != 1) {
        printf("Error al escribir el signo en el archivo.\n");
        fclose(archivo);
        return;
    }

    // Escribir la cantidad de dígitos en el archivo
    if (fwrite(&(numero->cantidadDigitos), sizeof(int), 1, archivo) != 1) {
        printf("Error al escribir la cantidad de dígitos en el archivo.\n");
        fclose(archivo);
        return;
    }

    // Escribir los dígitos en el archivo recorriendo la lista enlazada
    Nodo *actual = numero->siguiente;
    while (actual != NULL) {
        if (fwrite(&(actual->digito), sizeof(int), 1, archivo) != 1) {
            printf("Error al escribir un dígito en el archivo.\n");
            fclose(archivo);
            return;
        }
        actual = actual->siguiente;
    }

    // Cerrar el archivo y finalizar escritura
    fclose(archivo);
}


EnteroLargo *asignarMemoriaEnteroLargo();
int leerSigno(FILE *archivo, EnteroLargo *unEnteroLargo);
int leerCantidadDigitos(FILE *archivo, EnteroLargo *unEnteroLargo);
int construirListaDigitos(FILE *archivo, EnteroLargo *unEnteroLargo);

EnteroLargo *leeEnteroLargo(char *nombreArchivo) {
    // Asignar memoria para EnteroLargo
    EnteroLargo *unEnteroLargo = asignarMemoriaEnteroLargo();
    if (unEnteroLargo == NULL) return NULL;

    // Abrir el archivo en modo binario para lectura
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo %s para leer.\n", nombreArchivo);
        free(unEnteroLargo);
        return NULL;
    }

    // Leer el signo del número
    if (leerSigno(archivo, unEnteroLargo) == -1) {
        free(unEnteroLargo);
        fclose(archivo);
        return NULL;
    }

    // Leer la cantidad de dígitos
    if (leerCantidadDigitos(archivo, unEnteroLargo) == -1) {
        free(unEnteroLargo);
        fclose(archivo);
        return NULL;
    }

    // Ajustar la cantidad de dígitos para números negativos
    if (unEnteroLargo->signo == '-') {
        unEnteroLargo->cantidadDigitos--; 
    }

    // Construir la lista enlazada de dígitos
    if (construirListaDigitos(archivo, unEnteroLargo) == -1) {
        Nodo *temp = unEnteroLargo->siguiente;
        while (temp != NULL) {
            Nodo *siguiente = temp->siguiente;
            free(temp);
            temp = siguiente;
        }
        free(unEnteroLargo);
        fclose(archivo);
        return NULL;
    }

    // Cerrar el archivo
    fclose(archivo);
    return unEnteroLargo;
}

EnteroLargo *asignarMemoriaEnteroLargo() {
    EnteroLargo *unEnteroLargo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    if (unEnteroLargo == NULL) {
        printf("No se pudo asignar memoria para EnteroLargo.\n");
    } else {
        unEnteroLargo->siguiente = NULL;
    }
    return unEnteroLargo;
}

int leerSigno(FILE *archivo, EnteroLargo *unEnteroLargo) {
    if (fread(&(unEnteroLargo->signo), sizeof(char), 1, archivo) != 1) {
        printf("Error al leer el signo del archivo.\n");
        return -1;
    }
    // printf("Leyendo signo: %c\n", unEnteroLargo->signo);
    return 0;
}

int leerCantidadDigitos(FILE *archivo, EnteroLargo *unEnteroLargo) {
    if (fread(&(unEnteroLargo->cantidadDigitos), sizeof(int), 1, archivo) != 1) {
        printf("Error al leer la cantidad de dígitos del archivo.\n");
        return -1;
    }
    // printf("Cantidad de dígitos leída: %d\n", unEnteroLargo->cantidadDigitos);
    return 0;
}

int construirListaDigitos(FILE *archivo, EnteroLargo *unEnteroLargo) {
    int cantidadDigitos = unEnteroLargo->cantidadDigitos;
    Nodo *anterior = NULL;
    for (int i = 0; i < cantidadDigitos; i++) {
        Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
        if (nuevoNodo == NULL) {
            printf("No se pudo asignar memoria para Nodo.\n");
            return -1;
        }

        if (fread(&(nuevoNodo->digito), sizeof(int), 1, archivo) != 1) {
            printf("Error al leer un dígito del archivo.\n");
            free(nuevoNodo);
            return -1;
        }
        // Debug
        // printf("Dígito leído: %d\n", nuevoNodo->digito);

        nuevoNodo->siguiente = NULL;
        if (anterior == NULL) {
            unEnteroLargo->siguiente = nuevoNodo;
        } else {
            anterior->siguiente = nuevoNodo;
        }
        anterior = nuevoNodo;
    }

    return 0;
}


int igualEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2){
    //...
    return(0);
}

// Función para comparar la magnitud de dos números
int compararMagnitud(EnteroLargo *numero1, EnteroLargo *numero2) {
    if (numero1->cantidadDigitos > numero2->cantidadDigitos) {
        return 1;
    } else if (numero1->cantidadDigitos < numero2->cantidadDigitos) {
        return -1;
    } else {
        Nodo *puntero1 = numero1->siguiente;
        Nodo *puntero2 = numero2->siguiente;
        while (puntero1 != NULL && puntero2 != NULL) {
            if (puntero1->digito > puntero2->digito) {
                return 1;
            } else if (puntero1->digito < puntero2->digito) {
                return -1;
            }
            puntero1 = puntero1->siguiente;
            puntero2 = puntero2->siguiente;
        }
        return 0; // Son iguales en valor absoluto
    }
}
/* 
// Nueva función para verificar signos y realizar conversiones necesarias
EnteroLargo *verificarSignos(EnteroLargo *numero1, EnteroLargo *numero2, char operacion) {
    if (operacion == '+') {
        if (numero1->signo != numero2->signo) {
            EnteroLargo *numeroPositivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
            if (compararMagnitud(numero1, numero2) >= 0) {
                copiaEnteroLargo(numeroPositivo, numero1);
                numeroPositivo->signo = '+';
                EnteroLargo *resultado = restaEnteroLargo(numeroPositivo, numero2);
                liberarDigitos(numeroPositivo->siguiente);
                free(numeroPositivo);
                resultado->signo = numero1->signo;
                return resultado;
            } else {
                copiaEnteroLargo(numeroPositivo, numero2);
                numeroPositivo->signo = '+';
                EnteroLargo *resultado = restaEnteroLargo(numeroPositivo, numero1);
                liberarDigitos(numeroPositivo->siguiente);
                free(numeroPositivo);
                resultado->signo = numero2->signo;
                return resultado;
            }
        }
    } else if (operacion == '-') {
        if (numero1->signo == '+' && numero2->signo == '+') {
            return NULL; // Caso estándar: ambos positivos
        } else if (numero1->signo == '-' && numero2->signo == '+') {
            EnteroLargo *numero1Positivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
            copiaEnteroLargo(numero1Positivo, numero1);
            numero1Positivo->signo = '+';
            EnteroLargo *resultado = sumaEnteroLargo(numero1Positivo, numero2);
            resultado->signo = '-';
            liberarDigitos(numero1Positivo->siguiente);
            free(numero1Positivo);
            return resultado;
        } else if (numero1->signo == '+' && numero2->signo == '-') {
            EnteroLargo *numero2Positivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
            copiaEnteroLargo(numero2Positivo, numero2);
            numero2Positivo->signo = '+';
            EnteroLargo *resultado = sumaEnteroLargo(numero1, numero2Positivo);
            liberarDigitos(numero2Positivo->siguiente);
            free(numero2Positivo);
            return resultado;
        } else if (numero1->signo == '-' && numero2->signo == '-') {
            EnteroLargo *numero2Positivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
            copiaEnteroLargo(numero2Positivo, numero2);
            numero2Positivo->signo = '+';
            EnteroLargo *resultado = restaEnteroLargo(numero2Positivo, numero1);
            resultado->signo = '+';
            liberarDigitos(numero2Positivo->siguiente);
            free(numero2Positivo);
            return resultado;
        }
    }
    return NULL; // Si no se requiere ninguna conversión
}
*/

void eliminarCerosIzquierda(EnteroLargo *numero) {
    if (numero == NULL || numero->siguiente == NULL) {
        return; // Nada que hacer si el número es nulo o no tiene dígitos
    }

    Nodo *actual = numero->siguiente;

    // Avanzar el puntero mientras los dígitos sean ceros
    while (actual != NULL && actual->digito == 0) {
        Nodo *nodoAEliminar = actual;
        actual = actual->siguiente;
        free(nodoAEliminar);
    }

    // Actualizar el puntero inicial de la lista
    numero->siguiente = actual;

    // Si todos los dígitos eran ceros, asegurar un único dígito cero
    if (actual == NULL) {
        numero->siguiente = crearNodo(0);
        numero->cantidadDigitos = 1;
        numero->signo = '+';
        return;
    }

    // Contar los dígitos restantes
    int contador = 0;
    Nodo *temp = actual;
    while (temp != NULL) {
        contador++;
        temp = temp->siguiente;
    }

    numero->cantidadDigitos = contador;
}

int mayorMenorEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2){
    if(numero1->signo != numero2->signo){
        if(numero1->signo == '-'){
            return 2 ;// numero 2 es positivo ende mas grande
        }else{
            return 1; // de otro modo numero 1 es mas grande por ser positivo
        }
                
    }
    if(numero1->cantidadDigitos > numero2->cantidadDigitos){
        return 1; //1 es mas grande 
    }else if(numero1->cantidadDigitos < numero2->cantidadDigitos){
        return 2; //2 es mas grande
    }

    return mayorMenorLista(numero1->siguiente,numero2->siguiente);
}

EnteroLargo *sumaEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2) {
   /* printf("SUMA: \n");
    printf("num 1 :");muestraEnteroLargo(numero1);printf("\n");
    printf("num 2 :");muestraEnteroLargo(numero2);printf("\n");
    printf("\nTTTT\n");*/
    // Validación de entrada
    if (numero1 == NULL || numero2 == NULL) return NULL;

    // Si los signos son diferentes, realizamos una resta en su lugar
    if (numero1->signo != numero2->signo) {
        if (numero1->signo == '-') {
            EnteroLargo *numero1Positivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
            copiaEnteroLargo(numero1Positivo, numero1);
            numero1Positivo->signo = '+';
            EnteroLargo *resultado = restaEnteroLargo(numero2, numero1Positivo);
            eliminaEnteroLargo(numero1Positivo);
            return resultado;
        } else {
            EnteroLargo *numero2Positivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
            copiaEnteroLargo(numero2Positivo, numero2);
            numero2Positivo->signo = '+';
            EnteroLargo *resultado = restaEnteroLargo(numero1, numero2Positivo);
            eliminaEnteroLargo(numero2Positivo);
            return resultado;
        }
    }

    // Código original de suma cuando los signos son iguales
    EnteroLargo *resultado = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    resultado->siguiente = NULL;
    resultado->cantidadDigitos = 0;
    resultado->signo = numero1->signo;

    // Invertir listas para facilitar la suma dígito a dígito
    invertirLista(&(numero1->siguiente));
    invertirLista(&(numero2->siguiente));

    Nodo *nodo1 = numero1->siguiente;
    Nodo *nodo2 = numero2->siguiente;
    Nodo *ultimoNodoResultado = NULL;

    int acarreo = 0;
    while (nodo1 != NULL || nodo2 != NULL || acarreo != 0) {
        int digito1 = nodo1 ? nodo1->digito : 0;
        int digito2 = nodo2 ? nodo2->digito : 0;

        int digitoResultado = digito1 + digito2 + acarreo;
        acarreo = digitoResultado / 10;
        digitoResultado %= 10;

        Nodo *nuevoNodo = crearNodo(digitoResultado);
        if (resultado->siguiente == NULL) {
            resultado->siguiente = nuevoNodo;
        } else {
            ultimoNodoResultado->siguiente = nuevoNodo;
        }
        ultimoNodoResultado = nuevoNodo;

        if (nodo1) nodo1 = nodo1->siguiente;
        if (nodo2) nodo2 = nodo2->siguiente;

        resultado->cantidadDigitos++;
    }

    // Invertir la lista del resultado y eliminar ceros a la izquierda
    invertirLista(&(resultado->siguiente));
    eliminarCerosIzquierda(resultado);

    // Restaurar las listas originales
    invertirLista(&(numero1->siguiente));
    invertirLista(&(numero2->siguiente));
    
    return resultado;
}

EnteroLargo *restaEnteroLargo(EnteroLargo *numero1, EnteroLargo *numero2) {
   /* printf("RESTA: \n");
    printf("num 1 :");muestraEnteroLargo(numero1);printf("\n");
    printf("num 2 :");muestraEnteroLargo(numero2);printf("\n");
    printf("\nTTTT\n");*/
    // Validación de entrada
    if (numero1 == NULL || numero2 == NULL) return NULL;

    // Si el numero2 es negativo, convierte la resta en una suma
    if (numero2->signo == '-' ) {
        EnteroLargo *numero2Positivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
        copiaEnteroLargo(numero2Positivo, numero2);
        numero2Positivo->signo = '+';
        EnteroLargo *resultado = sumaEnteroLargo(numero1, numero2Positivo);
        eliminaEnteroLargo(numero2Positivo);
        return resultado;
    }

    // Si el numero1 es negativo, convierte la resta en una suma negativa
    
    if (numero1->signo == '-') {
        EnteroLargo *numero1Positivo = (EnteroLargo *)malloc(sizeof(EnteroLargo));
        copiaEnteroLargo(numero1Positivo, numero1);
        numero1Positivo->signo = '+';
        EnteroLargo *resultado = sumaEnteroLargo(numero1Positivo, numero2);
        resultado->signo = '-';
        eliminaEnteroLargo(numero1Positivo);
        return resultado;
    }

    // Código original de resta cuando ambos signos son positivos
    EnteroLargo *resultado = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    resultado->siguiente = NULL;
    resultado->cantidadDigitos = 0;

    // Determinar cuál es mayor en valor absoluto
    int comparacion = compararMagnitud(numero1, numero2);
    EnteroLargo *mayor, *menor;
    if (comparacion >= 0) {
        mayor = numero1;
        menor = numero2;
    } else {
        mayor = numero2;
        menor = numero1;
    }

    // Invertir listas para facilitar la resta dígito a dígito
    invertirLista(&(mayor->siguiente));
    invertirLista(&(menor->siguiente));

    Nodo *nodoMayor = mayor->siguiente;
    Nodo *nodoMenor = menor->siguiente;
    Nodo *ultimoNodoResultado = NULL;

    int acarreo = 0;
    while (nodoMayor != NULL) {
        int digitoMayor = nodoMayor->digito;
        int digitoMenor = nodoMenor ? nodoMenor->digito : 0;

        int digitoResultado = digitoMayor - digitoMenor - acarreo;
        if (digitoResultado < 0) {
            digitoResultado += 10;
            acarreo = 1;
        } else {
            acarreo = 0;
        }

        Nodo *nuevoNodo = crearNodo(digitoResultado);
        if (resultado->siguiente == NULL) {
            resultado->siguiente = nuevoNodo;
        } else {
            ultimoNodoResultado->siguiente = nuevoNodo;
        }
        ultimoNodoResultado = nuevoNodo;

        nodoMayor = nodoMayor->siguiente;
        if (nodoMenor != NULL) nodoMenor = nodoMenor->siguiente;

        resultado->cantidadDigitos++;
    }
    //resultado->cantidadDigitos++;
    // Invertir la lista del resultado y eliminar ceros a la izquierda
    invertirLista(&(resultado->siguiente));
    eliminarCerosIzquierda(resultado);

    // Ajustar el signo del resultado
    resultado->signo = (comparacion >= 0) ? numero1->signo : (numero1->signo == '+' ? '-' : '+');

    // Restaurar las listas originales
    invertirLista(&(mayor->siguiente));
    invertirLista(&(menor->siguiente));
    eliminaEnteroLargo(mayor);
    eliminaEnteroLargo(menor);
    return resultado;
}


char multiSignos(char signo1, char signo2) {
    
    if(signo1 != signo2) {
        return '-';
    } else if (signo1== signo2) {
        return '+';
    } else {
        return 'e'; // Error
    }
}


EnteroLargo *multiplicaEnteroLargo(EnteroLargo *multiplicando, EnteroLargo *multiplicador){ //WIP PV
    //EnteroLargo *resultado = NULL;
    EnteroLargo *resultado = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    
    // X * 0    caso multiplicador = 0          
    //si caulquiera de los multiplos es 0 devolvemos = [1]+0
    if((leerNumeroLista(multiplicador->siguiente,0)==0) || (leerNumeroLista(multiplicando->siguiente,0)==0)){
        //liberarDigitos(resultado->siguiente);   //de-comentar si caso da error de memoria
        resultado->cantidadDigitos=1;
        resultado->siguiente = crearNodo(0);
        resultado->signo = '+';
        
        return resultado;
    }
    //copiamos el multiplicando en el resultado = multiplicando *1
    copiaEnteroLargo(resultado,multiplicando);

    //enterolargo para ir sumando el contador y comparar para caso 1*x
    EnteroLargo *uno = (EnteroLargo *)malloc(sizeof(EnteroLargo)); // = [1]+1
    uno->signo='+'; uno->cantidadDigitos=1; uno->siguiente = crearNodo(1);

    //caso multiplicador = -1;
    if(igualLista(multiplicador->siguiente,uno->siguiente) && multiplicador->signo == '-'){
        resultado->signo = multiSignos(multiplicador->signo,uno->signo);
        eliminaEnteroLargo(uno);
        return resultado;
    }
    
    //caso multiplicador = 1;
    if( igualLista(multiplicador->siguiente,uno->siguiente)){//si el multiplicador es igual a 1
        eliminaEnteroLargo(uno);                                //devolvemos el multiplicado copiado solo 
        return resultado;
        
    }else if(igualLista(multiplicando->siguiente,uno->siguiente)){   ///caso multiplicando = 1  || comparamos con 1 (uno)
            //si el primer valor es el 1, copiamos el multiplicador por si es distinto y lo devolvemos
        copiaEnteroLargo(resultado,multiplicador);//pegamos el multiplicador en el resultado
        resultado->signo = multiSignos(multiplicador->signo,multiplicando->signo);//calculamos nuevamente los signos
        eliminaEnteroLargo(uno);//limpiamos la memoria de variables fantasma
        return resultado;
    } // caso x/x
    

    //contador con que el comparar el divisor
    EnteroLargo *contador = (EnteroLargo *)malloc(sizeof(EnteroLargo));// = [1]+1
    contador->signo='+'; contador->cantidadDigitos=1; contador->siguiente=crearNodo(1);
    
    resultado->signo = multiSignos(multiplicador->signo,multiplicando->signo);//calculamos los signos del resultado
    
    multiplicando->signo='+'; // pasamos el multiplicando como valor obsoluto para sumar correctamente
    while((igualLista(contador->siguiente,multiplicador->siguiente)==0)){
        contador = sumaEnteroLargo(contador,uno);//avanzamos contador en 1 hasta llegar al mismo numero de multiplicador
        
        resultado = sumaEnteroLargo(resultado,multiplicando);//sumamos cada paso
    }
   
    
    eliminaEnteroLargo(uno); // limpiamos memoria de memoria de variables enterolargo usados en la funcion
    eliminaEnteroLargo(contador);
    
    return (resultado);
}


EnteroLargo *divideEnteroLargo(EnteroLargo *dividendo, EnteroLargo *divisor){
    EnteroLargo *resultado = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    char sg = multiSignos(divisor->signo,dividendo->signo);
    if((leerNumeroLista(dividendo->siguiente,0)==0) ||(leerNumeroLista(divisor->siguiente,0)==0)){
        resultado->siguiente = crearNodo(0);
        resultado->cantidadDigitos=1;
        resultado->signo='+';
        return resultado;
    }
    EnteroLargo *uno = (EnteroLargo *)malloc(sizeof(EnteroLargo)); // = [1]+1
    uno->signo='+'; uno->cantidadDigitos=1; uno->siguiente = crearNodo(1);
    //caso 1/x
    if(mayorMenorLista(dividendo->siguiente,divisor->siguiente)==1){
        resultado->siguiente = crearNodo(0);
        resultado->cantidadDigitos=1;
        resultado->signo='+';
        return resultado;
    }
    //caso X/1
    if(igualLista(divisor->siguiente,uno->siguiente)){
        copiaEnteroLargo(resultado,dividendo);
        resultado->signo = multiSignos(divisor->signo,dividendo->signo);
        return resultado;
    }
    if(igualLista(dividendo->siguiente,divisor->siguiente)){
        resultado->siguiente = crearNodo(1);
        resultado->cantidadDigitos =1;
        resultado->signo = multiSignos(dividendo->signo,divisor->signo);
        return resultado;
    }
    
   
    EnteroLargo *contador = (EnteroLargo *)malloc(sizeof(EnteroLargo));// = [1]+1
    contador->signo='+'; contador->cantidadDigitos=1; contador->siguiente=crearNodo(0);
    
    resultado->signo='+'; resultado->cantidadDigitos=1; resultado->siguiente=crearNodo(1);
    
    EnteroLargo *numeroAnterior = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    numeroAnterior->signo = '+';numeroAnterior->cantidadDigitos = 1;numeroAnterior->siguiente=crearNodo(1);
    divisor->signo = '+';dividendo->signo='+';    //en absoluto para trabajar mejor    
    EnteroLargo *divisort = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    EnteroLargo *dividendot = (EnteroLargo *)malloc(sizeof(EnteroLargo));
    copiaEnteroLargo(divisort,divisor);
    copiaEnteroLargo(dividendot,dividendo);
    while(1){        
        //muestraEnteroLargo(contador);    
        if(igualEnteroLargo(resultado,dividendot)==1){ //caso division redonda
            copiaEnteroLargo(resultado,contador);
            break;
        }
        else if(mayorMenorEnteroLargo(resultado,dividendot)==1){           
            copiaEnteroLargo(resultado,numeroAnterior);
            break;
        }else{
            copiaEnteroLargo(numeroAnterior,contador);            
            contador = sumaEnteroLargo(contador,uno);
            resultado = multiplicaEnteroLargo(contador,divisort);
            
            //muestraEnteroLargo(resultado);
        }       
    }
    
    //copiaEnteroLargo(resultado,contador);
    eliminaEnteroLargo(contador);
    eliminaEnteroLargo(uno);
    eliminaEnteroLargo(numeroAnterior);
    eliminaEnteroLargo(divisort);
    eliminaEnteroLargo(dividendot);
    resultado->signo = sg;
    return resultado;
}
