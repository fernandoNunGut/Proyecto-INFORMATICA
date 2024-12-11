#include <stdio.h>
#include <string.h>

#define DIAS 30
#define LIMITE_FUERTE 5.0

// Función para leer los datos desde un archivo
int leer_datos(float temblores[], int dias, char nombre_archivo[]) {
    FILE *archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo '%s'. Verifique el nombre e intente nuevamente.\n", nombre_archivo);
        return 0; // Error al abrir el archivo
    }

    for (int i = 0; i < dias; i++) {
        if (fscanf(archivo, "%f", &temblores[i]) != 1 || temblores[i] <= 0) {
            printf("Error en los datos del archivo en el día %d. Asegúrese de que todos los valores sean positivos.\n", i + 1);
            fclose(archivo);
            return 0; // Error en los datos
        }
    }

    fclose(archivo);
    return 1; // Lectura exitosa
}

// Función para calcular las diferencias consecutivas
int calcular_diferencias_consecutivas(float temblores[], int dias) {
    int creciente = 1, decreciente = 1;

    for (int i = 1; i < dias; i++) {
        if (temblores[i] > temblores[i - 1]) {
            decreciente = 0; // No es decreciente
        } else if (temblores[i] < temblores[i - 1]) {
            creciente = 0; // No es creciente
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

int contador_temblores(float temblores[], int dias) {
    int contadorTemblores = 0;

    for (int i = 0; i < dias; i++) {
        if ( temblores[i] > dias) {
            contadorTemblores++;
        }
        printf("Leida la magnitud del temblor del dia %d:\n",dias );
    }
}

// Función para mostrar los resultados
void mostrar_resultados(float temblores[], int dias) {
    // Calcular el promedio
    float promedio = calcular_promedio(temblores, dias);

    // Calcular la tendencia
    int tendencia = calcular_diferencias_consecutivas(temblores, dias);

    // Contar los temblores fuertes
    int fuertes = contar_temblor_fuerte(temblores, dias, LIMITE_FUERTE);

    //Contador de temblores
    int TembloresContados = contador_temblores(temblores, dias);

    // Mostrar resultados
    printf("Análisis de la Actividad Sísmica:\n");
    printf("Leida la magnitud del temblor del dia %d: \n ", dias);
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
}

// Función principal
int main() {
    float temblores[DIAS];
    char nombre_archivo[100];
    int archivo_cargado = 0;

    printf("Bienvenido al analizador de actividad sísmica.\n");
    printf("Por favor, ingrese el nombre del archivo con los datos (ejemplo: temblores.txt): ");

    while (!archivo_cargado) {
        scanf("%s", nombre_archivo);

        // Validar y cargar el archivo
        archivo_cargado = leer_datos(temblores, DIAS, nombre_archivo);

        if (!archivo_cargado) {
            printf("Por favor, ingrese un nombre de archivo válido: ");
        }
    }

    // Si se carga correctamente, mostrar los resultados
    mostrar_resultados(temblores, DIAS);

    return 0;
}
