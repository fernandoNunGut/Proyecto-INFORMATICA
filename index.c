#include <stdio.h>
#include <stdlib.h>

#define DIAS 30
#define LIMITE_FUERTE 5.0

// Función para calcular las diferencias consecutivas
int calcular_diferencias_consecutivas(float temblores[], int dias) {
    int creciente = 1, decreciente = 1;

    for (int i = 1; i < dias; i++) {
        if (temblores[i] > temblores[i - 1]) {
            decreciente = 0;  // No es decreciente
        } else if (temblores[i] < temblores[i - 1]) {
            creciente = 0;  // No es creciente
        }
    }

    if (creciente) return 1;      // Tendencia creciente
    if (decreciente) return -1;   // Tendencia decreciente
    return 0;                     // Tendencia variable
}

// Función para calcular el promedio de las magnitudes
float calcular_promedio(float temblores[], int dias) {
    float suma = 0.0;

    for (int i = 0; i < dias; i++) {
        suma += temblores[i];
    }

    return suma / dias;
}

// Función para contar los temblores fuertes
int contar_temblor_fuerte(float temblores[], int dias, float limite) {
    int contador = 0;

    for (int i = 0; i < dias; i++) {
        if (temblores[i] > limite) {
            contador++;
        }
    }

    return contador;
}

// Función principal
int main() {
    float temblores[DIAS];
    FILE *archivo = fopen("temblores.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Leer los datos del archivo
    for (int i = 0; i < DIAS; i++) {
        if (fscanf(archivo, "%f", &temblores[i]) != 1 || temblores[i] <= 0) {
            printf("Error en los datos de entrada (día %d).\n", i + 1);
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);

    // Calcular el promedio
    float promedio = calcular_promedio(temblores, DIAS);

    // Calcular la tendencia
    int tendencia = calcular_diferencias_consecutivas(temblores, DIAS);

    // Contar los temblores fuertes
    int fuertes = contar_temblor_fuerte(temblores, DIAS, LIMITE_FUERTE);

    // Mostrar resultados
    printf("Análisis de la Actividad Sísmica:\n");
    printf("- Promedio de las magnitudes: %.2f\n", promedio);

    printf("- Tendencia: ");
    if (tendencia == 1) {
        printf("Creciente\n");
    } else if (tendencia == -1) {
        printf("Decreciente\n");
    } else {
        printf("Variable\n");
    }

    printf("- Número de temblores fuertes (magnitud > %.1f): %d\n", LIMITE_FUERTE, fuertes);

    // Evaluar la actividad sísmica en general
    if (fuertes > 3) {
        printf("- Actividad sísmica: Alta\n");
    } else {
        printf("- Actividad sísmica: Baja\n");
    }

    return 0;
}
