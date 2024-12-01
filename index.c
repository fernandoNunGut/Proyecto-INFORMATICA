#include <stdio.h>
#include <stdlib.h>

#define DIAS 30  // Número de días a analizar
#define LIMITE_FUERTE 5.0  // Límite de magnitud para considerar un temblor fuerte

// Función para calcular las diferencias consecutivas
int calcular_diferencias_consecutivas(float temblores[], int dias) {  // Devuelve 1 si es creciente, 0 si es decreciente, -1 si es variable
    int creciente = 1, decreciente = 1;  // Variables para almacenar el resultado
 
    for (int i = 1; i < dias; i++) {  // Recorrer los días
        if (temblores[i] > temblores[i - 1]) {  // Si es creciente
            decreciente = 0;  // No es decreciente (se ha encontrado un creciente)
        } else if (temblores[i] < temblores[i - 1]) {  // Si es decreciente
            creciente = 0;  // No es creciente 
        }
    }

    if (creciente) return 1;      // Tendencia creciente
    if (decreciente) return -1;   // Tendencia decreciente
    return 0;                     // Tendencia variable
}

// Función para calcular el promedio de las magnitudes
float calcular_promedio(float temblores[], int dias) {  // Devuelve el promedio de las magnitudes
    float suma = 0.0;  // Variable para sumar las magnitudes

    for (int i = 0; i < dias; i++) {  // Recorrer los días
        suma += temblores[i];  // Sumar las magnitudes
    }

    return suma / dias;  // Devolver el promedio
}

// Función para contar los temblores fuertes
int contar_temblor_fuerte(float temblores[], int dias, float limite) {  // Devuelve el número de temblores fuertes
    int contador = 0;  // Contador para contar los temblores fuertes

    for (int i = 0; i < dias; i++) {  // Recorrer los días
        if (temblores[i] > limite) {  // Si es un temblor fuerte
            contador++;  // Incrementar el contador
        }
    }

    return contador;  // Devolver el número de temblores fuertes
}

// Función principal
int main() {  // Devuelve 0 si todo ha ido bien, 1 si hay errores
    float temblores[DIAS];  // Array para almacenar las magnitudes
    FILE *archivo = fopen("temblores.txt", "r");  // Archivo de entrada

    if (archivo == NULL) {  // Si no se pudo abrir el archivo
        printf("Error al abrir el archivo.\n");  // Mostrar un mensaje de error
        return 1;  // Devolver 1 para indicar un error
    }

    // Leer los datos del archivo
    for (int i = 0; i < DIAS; i++) {  // Recorrer los días
        if (fscanf(archivo, "%f", &temblores[i]) != 1 || temblores[i] <= 0) {  // Leer la magnitud y comprobar que sea positiva
            printf("Error en los datos de entrada (día %d).\n", i + 1);  // Mostrar un mensaje de error
            fclose(archivo);  // Cerrar el archivo
            return 1;  // Devolver 1 para indicar un error
        }
    }
    fclose(archivo);  // Cerrar el archivo

    // Calcular el promedio
    float promedio = calcular_promedio(temblores, DIAS);

    // Calcular la tendencia
    int tendencia = calcular_diferencias_consecutivas(temblores, DIAS);

    // Contar los temblores fuertes
    int fuertes = contar_temblor_fuerte(temblores, DIAS, LIMITE_FUERTE);

    // Mostrar resultados
    printf("Analisis de la Actividad Sismica:\n");  // Mostrar un mensaje de resultados
    printf("- Promedio de las magnitudes: %.2f\n", promedio);  // Mostrar el promedio

    printf("- Tendencia: ");  // Mostrar la tendencia
    if (tendencia == 1) {  // Si la tendencia es positiva
        printf("Creciente\n");  // Mostrar un mensaje de resultados
    } else if (tendencia == -1) {  // Si la tendencia es negativa
        printf("Decreciente\n");  // Mostrar un mensaje de resultados
    } else {  // Si la tendencia es variable
        printf("Variable\n");  // Mostrar un mensaje de resultados
    }

    printf("- Numero de temblores fuertes (magnitud > %.1f): %d\n", LIMITE_FUERTE, fuertes);  // Mostrar el número de temblores fuertes

    // Evaluar la actividad sísmica en general
    if (fuertes > 3) {  // Si hay más de 3 temblores fuertes
        printf("- Actividad sismica: Alta\n");  // Mostrar un mensaje de resultados
    } else {  // Si no hay más de 3 temblores fuertes
        printf("- Actividad sismica: Baja\n");  // Mostrar un mensaje de resultados
    }

    return 0;  // Devolver 0 para indicar que todo ha ido bien
}