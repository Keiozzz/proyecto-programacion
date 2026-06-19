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
   int cantidad_estrellas = 0;
   int estrellaX, estrellaY;
   char orientacion;
   char ordenes[40];
   int destructorX, destructorY;

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
   fscanf(archivo_entrada, "%d %d", &cantidad_estrellas);
    
   //crear funcion que ponga estrellas en el mapa
   int i=0;
   while(F < cantidad_estrellas){
      fscanf(archivo_entrada, "%d" "%d", &estrellaX, &estrellaY);
      while (i == estrellaX){
      C = 0;
      while (C == estrellaY){
         mapa[F][C] = ESTRELLA;
         C++;
      }
      F++;
   }
   }
    
   fscanf(archivo_entrada, "%d %d", estrellaX, estrellaY);
   fscanf(archivo_entrada, "%d", &cantidad_destructores);
   fscanf(archivo_entrada, "%d %d", destructorX, destructorY);
   fscanf(archivo_entrada,"%c", orientacion);

   // 5. Colocar el planeta en el mapa
   mapa[*planetaX][*planetaY] = PLANETA;

   // Recordar cerrar el archivo al terminar esta función más adelante
   fclose(archivo_entrada); 
    
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
      if (mapa[*naveX][*naveY] == DESTRUCTOR){
         return 1; 
      }
      if (mapa[*naveX][*naveY] == ESTRELLA){
         return 1;
      }
      if (mapa[*naveX][*naveY] == PLANETA){
         return 2;
      }
      i = i + 1; 
   
   }
   return 0;  // este return 0 significa que el avion se perdio implicitamente si no cumple ninguna de las 3

}

// FUNCION DE SALIDA

void archivo_salida(int ruta_avion){
   FILE*archivo_salida = fopen("situacion_final.txt", "w");;
   if(archivo_salida == NULL){
      printf("archivo  no identificado.\n");
      return;    // QUITAR ANTES DE ENTREGAR!!!!
   }

   if(archivo_salida == 1){
      fprintf(archivo_salida, "Nave destruida.\n");
   }
   if (archivo_salida == 2)
   {
      fprintf(archivo_salida,"" "Llegamos a salvo.");
   }

   
   fclose(archivo_salida);
}


/* ==========================================
   CODIGO BASE (MAIN)
   ========================================== */
int main() {
   int mapa[MAX][MAX];
   int filas;
   int columnas;
   int estrellasX, estrellasY, destructor;
   char orientacion;
   char max_mov;
   int avionX, avionY;
}