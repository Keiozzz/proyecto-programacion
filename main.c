#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 30
#define MAX_MOV 41
#define VACIO 0
#define NAVE 1
#define ESTRELLA 2
#define DESTRUCTOR 3
#define PLANETA 4

/* ==========================================
   FUNCION 1: ENTRADA DE ARCHIVO
   ========================================== */
int interpretacion_datos(int mapa[][MAX], int *filas, int *columnas, int *naveX, int *naveY, int *planetaX, int *planetaY, int estrellaX, int estrellaY) {
    
   FILE *archivo_entrada = fopen("situacion_inicial.txt", "r");
   if (archivo_entrada == NULL) {
        exit(-1);    
   }
    
   // 1. Leer dimensiones del mapa
   fscanf(archivo_entrada, "%d %d", filas, columnas);

   // 2. Inicializar todo el mapa en VACIO
   int F = 0; 
   int C = 0;
   int cantidad_destructores = 0;
   while (F < *filas) {
      C = 0;
      while (C < *columnas) {
         mapa[F][C] = VACIO;
         C++;
      }
      F++;
   }
    
   // 3. Leer posición de la nave H
   fscanf(archivo_entrada, "%d %d", naveX, naveY);

   // 4. Leer posición del planeta T
   fscanf(archivo_entrada, "%d %d", planetaX, planetaY);
   fscanf(archivo_entrada, "%d %d", estrellaX, estrellaY)
   fscanf(archivo_entrada, "%d", &cantidad_destructores)

   // 5. Colocar el planeta en el mapa
   mapa[*planetaX][*planetaY] = PLANETA;

   // Recordar cerrar el archivo al terminar esta función más adelante
    / fclose(archivo_entrada); 
    
   return 0;
   fclose(archivo_entrada);
} 


/* ==========================================
   FUNCION 2: SIMULACION DE LA NAVE
   ========================================== */
int ruta_avion(int *naveX, int *naveY, char *orientacion, char ordenes[], int num_ordenes, int mapa[][MAX], int filas, int columnas) {
   int i = 0; 
    
   while (i < num_ordenes) {
      // Corregido: se agregó la 'i' dentro de ordenes[i]
      if (mapa[naveX][naveY] == DESTRUCTOR) {
         printf("nave destruida\n"); 
      }
      if (mapa[naveX][naveY] == ESTRELLA) {
         printf("nave destruida\n");
      }
      if (mapa[naveY][naveY] == PLANETA) {
         printf("llegamos a salvo\n");
      }
      i = i + 1; 
   }
   return 0;
}


/* ==========================================
   CODIGO BASE (MAIN)
   ========================================== */
int main() {
   int mapa[MAX][MAX];
   int filas;
   int columnas;
   int num_Estrellas, num_Destructores;
   char orientacion;
   char max_mov;
   int avionX, avion