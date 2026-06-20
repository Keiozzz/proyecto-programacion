#include <stdio.h>
#include <stdlib.h>

#define MAX 30
#define MAX_MOV 41
#define VACIO 0
#define NAVE 1
#define ESTRELLA 2
#define DESTRUCTOR 3
#define PLANETA 4

int interpretacion_datos(int mapa[][MAX], int *filas, int *columnas, int *naveX, int *naveY, int *planetaX, int *planetaY, int i, char *orientacion, char ordenes[MAX_MOV], int *num_ordenes) {
    FILE *archivo_entrada = fopen("situacion_inicial.txt", "r");
    if (archivo_entrada == NULL) {
        exit(-1);    
    }
    fscanf(archivo_entrada, "%d %d", filas, columnas);
    int F = 0;
    int C = 0;
    int estrellaX;
    int estrellaY;
    int cantidad_destructores = 0;
    int cantidad_estrellas = 0;
    int destructorX, destructorY;
    while (F < *filas){
        C = 0;
        while (C < *columnas){
            mapa[F][C] = VACIO;
            C++;
        }
        F++;
    }
    fscanf(archivo_entrada, "%d %d", naveX, naveY);
    fscanf(archivo_entrada, "%d %d", planetaX, planetaY);
    fscanf(archivo_entrada, "%d", &cantidad_estrellas);
    i = 0;
    while( i < cantidad_estrellas){
        fscanf(archivo_entrada, "%d" "%d", &estrellaX, &estrellaY);
        mapa[estrellaX][estrellaY] = ESTRELLA;
        i++;
    }
    i = 0;
    fscanf(archivo_entrada, "%d", &cantidad_destructores);
    while( i < cantidad_destructores){
        fscanf(archivo_entrada, "%d %d", &destructorX, &destructorY);
        mapa[destructorX][destructorY] = DESTRUCTOR;
        i++;
    }
    fscanf(archivo_entrada," %c", orientacion);
    fscanf(archivo_entrada,"%d", num_ordenes);
    i = 0;
    while(i < *num_ordenes){
        fscanf(archivo_entrada," %c", &ordenes[i]);
        i++;
    }
    mapa[*planetaX][*planetaY] = PLANETA;
    fclose(archivo_entrada);
    return 0;
}

int ruta_nave(int *naveX, int *naveY, char *orientacion, char ordenes[], int *num_ordenes, int mapa[][MAX], int *filas, int *columnas, int *i) {
    while (*i < *num_ordenes){
        if(ordenes[*i] == 'A'){
            if (*orientacion == 'N'){
                (*naveX)--;
            }
            else if (*orientacion == 'S'){
                (*naveX)++;
            }
            else if (*orientacion == 'E'){
                (*naveY)++;
            }
            else if (*orientacion == 'O'){
                (*naveY)--;
            }
        } 
        if (ordenes[*i] == 'I'){
            if (*orientacion == 'N'){
                *orientacion = 'O';
            }
            else if (*orientacion == 'O'){
                *orientacion = 'S';
            }
            else if(*orientacion == 'S'){
                *orientacion = 'E';
            }
            else if(*orientacion == 'E'){
                *orientacion = 'N';
            }
        } 
        if (ordenes[*i] == 'D'){
            if (*orientacion == 'N'){
                *orientacion = 'E';
            }
            else if (*orientacion =='E'){
                *orientacion = 'S';
            }
            else if(*orientacion == 'S'){
                *orientacion = 'O';
            }
            else if(*orientacion == 'O'){
                *orientacion = 'N';
            }
        }
        if (*naveX < 0 || *naveX >= *filas || *naveY < 0 || *naveY >= *columnas){
            return 1;
        }
        if (mapa[*naveX][*naveY] == DESTRUCTOR){
            return 2;
        }
        if (mapa[*naveX][*naveY] == ESTRELLA){
            return 2;
        }
        if (mapa[*naveX][*naveY] == PLANETA){
            return 3;
        }
        (*i)++;
    }
    return 1;
}

void resultado_final(int ruta_nave){
    FILE*archivo_salida = fopen("situacion_final.txt", "w");
    if (ruta_nave == 1){
        fprintf(archivo_salida,"Nave perdida");
    }
    if (ruta_nave == 2){
        fprintf(archivo_salida,"Nave destruida");
    }
    if (ruta_nave == 3){
        fprintf(archivo_salida,"Llegamos a salvo");
    }
    fclose(archivo_salida);
}

int main() {
int mapa[MAX][MAX];
int filas, i=0;
int columnas;
int destructor;
char orientacion;
int planetaX, planetaY;
char ordenes[MAX_MOV];
int naveX, naveY;
int num_ordenes;
   int resultado_datos = interpretacion_datos(mapa, &filas,&columnas,&naveX,&naveY,&planetaX,&planetaY, i, &orientacion, ordenes, &num_ordenes);
   int resultado_nave = ruta_nave(&naveX,&naveY, &orientacion, ordenes, &num_ordenes, mapa, &filas, &columnas, &i);
   resultado_final(resultado_nave);
   return 0;
}