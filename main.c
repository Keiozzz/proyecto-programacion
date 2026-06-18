#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 30
#define MAX_MOV 40

/*FUNCIONES AQUI*/
void archivo_existe(FILE* archivo_entrada){
        if(archivo_entrada == NULL){
            exit(-1);
        }    
}
/*CODIGO BASE*/

/*el espacio por el que puede moverse la nave dividido en m filas (numeradas de 0 a m-1, yendo de N a S)
y n columnas (numeradas de 0 a n-1, yendo de O a E)*/
int main(){
    int filas;
    int columnas;
    char max_mov;
    int planetaX, PlanetaY;
    int estrellaX, estrellaY;
    int filas, columnas;
    char ordenes [MAX_MOV];
    FILE * archivo_entrada;
    

    archivo_entrada = fopen("situacion_inicial.txt", "r");
    archivo_existe(archivo_entrada);
    fscanf(archivo_entrada, "%d%d", &filas,&columnas);
    printf("%d %d",&filas, &columnas);
    if(filas>=30 || columnas >=30){
        return 1;

    }
   // fscanf(que quiero leer, que tipo de dato espera, donde lo guarda)
    printf("seguimo vivo");

}
