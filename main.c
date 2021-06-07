#include <stdio.h>
#include <string.h>
void ordenamiento(int duraciones[], int llegadas[], int tiemposRestantes[],int num, char IDs[num][3]);
void regreso(int duraciones[], int llegadas[], int tiemposRestantes[],int num, char IDs[num][3], int final, int conteo, int tiemposEspera[], int tiemposTotales[]);
int main() {
    int num;
    printf("Ingrese el numero de procesos\n");
    scanf("%d", &num);
    char IDs[num][3];
    int duraciones[num];
    int llegadas[num];
    int tiemposRestantes[num];
    int tiemposEspera[num];
    int tiemposTotales[num];
    double totalTE = 0;
    double totalTT = 0;
    double promedioTE = 0;
    double promedioTT = 0;
    int quantum = 0;
    int j = 0;
    int suma = 0;
    int sumaDuraciones = 0;
    int conteo = 0;
    for(int i = 0; i<num; i++){
        printf("Ingrese el identificador del proceso %d\n", (i+1));
        scanf("%s", IDs[i]);
        printf("Ingrese la duracion del proceso %s\n", IDs[i]);
        scanf("%d", &duraciones[i]);
        tiemposRestantes[i] = duraciones[i];
        printf("Ingrese la llegada del proceso %s\n", IDs[i]);
        scanf("%d", &llegadas[i]);
    }
    printf("Ingrese el valor del quantum\n");
    scanf("%d", &quantum);
    ordenamiento(duraciones, llegadas, tiemposRestantes,num, IDs);
    for(int k = 0; k<num; k++){
        sumaDuraciones = sumaDuraciones + duraciones[k];
    }
    while(tiemposRestantes[0] != 0){
        if (tiemposRestantes[j] <= quantum && tiemposRestantes[j]>0){
            suma = suma + tiemposRestantes[j];
            tiemposRestantes[j] = 0;
            tiemposEspera[j] = suma-llegadas[j]-duraciones[j];
            tiemposTotales[j]=tiemposEspera[j]+duraciones[j];
            totalTE = totalTE + (double)tiemposEspera[j];
            totalTT = totalTT + (double)tiemposTotales[j];
            if(conteo!=(num-1))
                regreso(duraciones, llegadas, tiemposRestantes,num, IDs, sumaDuraciones, conteo, tiemposEspera, tiemposTotales);
            conteo = conteo + 1;
        }else if(tiemposRestantes[j]>0){
            suma = suma + quantum;
            tiemposRestantes[j] = tiemposRestantes[j]-quantum;
            if(conteo!=(num-1))
                regreso(duraciones, llegadas, tiemposRestantes,num, IDs, suma, conteo, tiemposEspera, tiemposTotales);
        }
    }
    promedioTE = totalTE/(double)num;
    promedioTT = totalTT/(double)num;
    for(int i = 0; i<num; i++){
        printf("%s Duracion: %d Llegada: %d TiempoE: %d TiempoT: %d\n", IDs[i], duraciones[i], llegadas[i], tiemposEspera[i], tiemposTotales[i]);
    }
    printf("Totales Tiempo de espera: %.1f\n", totalTE);
    printf("Totales Tiempo total: %.1f\n", totalTT);
    printf("Promedio Tiempo de espera: %.1f\n", promedioTE);
    printf("Promedio Tiempo total: %.1f\n", promedioTT);
    return 0;
}
void ordenamiento(int duraciones[], int llegadas[], int tiemposRestantes[],int num, char IDs[num][3]){
    int aux;
    char idTemp[3];
    for(int i = 0; i < num; i++){
        for(int j = i; j < num; j++){
            if(llegadas[i]>llegadas[j]){
                aux = llegadas[j];
                llegadas[j] = llegadas[i];
                llegadas[i] = aux;
                aux = duraciones[j];
                duraciones[j] = duraciones[i];
                duraciones[i] = aux;
                aux = tiemposRestantes[j];
                tiemposRestantes[j] = tiemposRestantes[i];
                tiemposRestantes[i] = aux;
                strcpy(idTemp, IDs[j]);
                strcpy(IDs[j], IDs[i]);
                strcpy(IDs[i], idTemp);
            }
        }
    }
}
void regreso(int duraciones[], int llegadas[], int tiemposRestantes[],int num, char IDs[num][3], int final, int conteo, int tiemposEspera[], int tiemposTotales[]){
    int auxDuracion, auxLlegada, auxTR, auxTE, auxTT;
    char idTemp[3];
    int cant = 0;
    for(int i = 0; i<num; i++) {
        if(llegadas[i]<=final){
            cant++;
        }
    }
    cant=cant-conteo;
    auxDuracion = duraciones[cant-1];
    auxLlegada = llegadas[cant-1];
    auxTR = tiemposRestantes[cant-1];
    auxTE = tiemposEspera[cant-1];
    auxTT = tiemposTotales[cant-1];
    strcpy(idTemp, IDs[cant-1]);
    for(int i = 0; i < cant; i++){
        if(i == cant-1){
            duraciones[i-1] = auxDuracion;
            llegadas[i-1] = auxLlegada;
            tiemposRestantes[i-1] = auxTR;
            tiemposEspera[i-1] = auxTE;
            tiemposTotales[i-1] = auxTT;
            strcpy(IDs[i-1], idTemp);
        }else if(i>0){
            duraciones[i-1] = duraciones[i];
            llegadas[i-1] = llegadas[i];
            tiemposRestantes[i-1] = tiemposRestantes[i];
            tiemposEspera[i-1] = tiemposEspera[i];
            tiemposTotales[i-1] = tiemposTotales[i];
            strcpy(IDs[i-1], IDs[i]);
        }else if(i==0){
            duraciones[cant-1] = duraciones[i];
            llegadas[cant-1] = llegadas[i];
            tiemposRestantes[cant-1] = tiemposRestantes[i];
            tiemposEspera[cant-1] = tiemposEspera[i];
            tiemposTotales[cant-1] = tiemposTotales[i];
            strcpy(IDs[cant-1], IDs[i]);
        }

    }
}
