#include <stdio.h>
#include <stdlib.h>
#define MAX 30
#define MAX_MOV 41
#define VACIO 0
#define NAVE 1
#define ESTRELLA 2
#define DESTRUCTOR 3
#define PLANETA 4
/* ==========================================
   FUNCION 1: ENTADA DE ARCHIVO
   ========================================== */
// CAMBIO 1: Se transformó 'orientacion' en puntero (*orientacion) para no perder el dato leído
int interpretacion_datos(int mapa[][MAX], int *filas, int *columnas, int *naveX, int *naveY, int *planetaX, int *planetaY, int i, char *orientacion, char ordenes[MAX_MOV], int *num_ordenes) {
    
   FILE *archivo_entrada = fopen("situacion_inicial.txt", "r");
   if (archivo_entrada == NULL) {
        exit(-1);    
   }

   // 1. Leer dimensiones del mapa
   fscanf(archivo_entrada, "%d %d", filas, columnas);

   // 2. Inicializar todo el mapa en VACIO
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
    
   // 3. Leer posición de la nave H
   fscanf(archivo_entrada, "%d %d", naveX, naveY);

   // 4. Leer posición del planeta T
   fscanf(archivo_entrada, "%d %d", planetaX, planetaY);
   fscanf(archivo_entrada, "%d", &cantidad_estrellas);
      
   i = 0;
   while( i < cantidad_estrellas){
      fscanf(archivo_entrada, "%d" "%d", &estrellaX, &estrellaY);
      mapa[estrellaX][estrellaY] = ESTRELLA;
      i++;
   }
   i=0;
   fscanf(archivo_entrada, "%d", &cantidad_destructores);
   
   while( i < cantidad_destructores){
      fscanf(archivo_entrada, "%d %d", &destructorX, &destructorY);
      mapa[destructorX][destructorY] = DESTRUCTOR;
      i++;
   }

   // CAMBIO 1 (Continuación): Se añade el asterisco correspondiente a la lectura de la orientación
   fscanf(archivo_entrada," %c", orientacion);
   fscanf(archivo_entrada,"%d", num_ordenes);
   // AHORA VA EL NUMERO DE INDICACIONES
   i=0;
   while(i < *num_ordenes){
      // CAMBIO 2: Se corrigió el destino de lectura para usar 'ordenes[i]' con el espacio necesario " %c"
      fscanf(archivo_entrada," %c", &ordenes[i]);
      i++;
   }
   // 5. Colocar el planeta en el mapa
   mapa[*planetaX][*planetaY] = PLANETA;
   fclose(archivo_entrada);
   return 0;
} 

/* ==========================================
   FUNCION 2: SIMULACION DE LA NAVE
   ========================================== */
int ruta_nave(int *naveX, int *naveY, char *orientacion, char ordenes[], int *num_ordenes, int mapa[][MAX], int *filas, int *columnas, int *i) {
   while (*i < *num_ordenes){
      if(ordenes[*i] == 'A'){
         if (*orientacion == 'N'){
            // CAMBIO 3: Se añadieron paréntesis para corregir la precedencia en la modificación de coordenadas
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
      } else if (ordenes[*i] =='I'){
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
      } else if (ordenes[*i] == 'D'){
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
      if (mapa[*naveX][*naveY] == DESTRUCTOR){
         return 2; 
      }
      if (mapa[*naveX][*naveY] == ESTRELLA){
         return 2;
      }
      if (mapa[*naveX][*naveY] == PLANETA){
         return 3;
      }
      if (*naveX < 0 || *naveX >= *filas || *naveY < 0 || *naveY >= *columnas) {
         return 1;
      }
      // CAMBIO 4: Se movió el incremento de la variable de control DENTRO del ciclo while usando (*i)++
      (*i)++; 
   } 
}


/* ==========================================
   FUNCION 3 SALIDA.
   ========================================== */

void resultado_final(int ruta_nave){
   FILE*archivo_salida = fopen("situacion_final.txt", "w");
   if(archivo_salida == NULL){
      printf("archivo no identificado.");       
   }
   if (ruta_nave == 1){
      fprintf(archivo_salida,"Nave perdida.");
   }
   if (ruta_nave == 2){
      fprintf(archivo_salida,"Nave destruida.");
   }
   if (ruta_nave == 3){
      fprintf(archivo_salida,"Llegamos a salvo.");
   }
   
   fclose(archivo_salida);
}
/* ==========================================
   CODIGO BASE (MAIN)
   ========================================== */
int main() {
   int mapa[MAX][MAX];
   int filas, i=0;
   int columnas;
   int estrellasX, estrellasY, destructor;
   char orientacion, ordens[MAX_MOV];
   int planetaX, planetaY;
   char ordenes[MAX_MOV];
   int naveX, naveY;
   int num_ordenes;
   // CAMBIO 1 (Continuación): Se pasa la dirección de memoria de la orientación (&orientacion)
   int resultado_datos = interpretacion_datos(mapa, &filas,&columnas,&naveX,&naveY,&planetaX,&planetaY, i, &orientacion, ordenes, &num_ordenes);
   int resultado_nave = ruta_nave(&naveX,&naveY, &orientacion, ordenes, &num_ordenes, mapa, &filas, &columnas, &i);
   resultado_final(resultado_nave);
   return 0;
}