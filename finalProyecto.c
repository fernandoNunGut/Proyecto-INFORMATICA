// Marcelo Rios Inicia

#include <stdio.h> // Incluir la librería de entrada/salida
#include <string.h> // Incluir la librería de cadenas de caracteres

#define DIAS 30 // Representa el único día
#define FILAS 1 // Representa el único mes
#define LIMITE_FUERTE 5.0 // Representa el umbral de magnitud para considerar un temblor fuerte

// Función para leer los datos desde un archivo
int leer_datos(float temblores[FILAS][DIAS], int filas, int dias, char nombre_archivo[]) { 
    FILE *archivo = fopen(nombre_archivo, "r"); // Abrir el archivo

    if (archivo == NULL) { // Si no se pudo abrir el archivo
        printf("Error: No se pudo abrir el archivo '%s'.\nVerifique el nombre e intente nuevamente o verifique que el contenitdo solo tenga valores numericos.\n", nombre_archivo); // Mostrar un mensaje de error
        return 0; // Error al abrir el archivo
    }

    for (int i = 0; i < filas; i++) { // Leer cada fila
        for (int j = 0; j < dias; j++) { // Leer cada día
            if (fscanf(archivo, "%f", &temblores[i][j]) != 1 || temblores[i][j] <= 0) { // Comprobar si se pudo leer el valor y si es positivo
                printf("Error en los datos del archivo en el día %d. \nAsegúrese de que todos los valores sean positivos o que el archivo este con los dias totales [30].\n", j + 1); // Mostrar un mensaje de error
                fclose(archivo); // Cerrar el archivo
                return 0; // Error en los datos
            }
            // Mostrar la magnitud leída para cada día
            printf("Leída la magnitud del temblor del día %d: %.1f\n", j + 1, temblores[i][j]); // Mostrar la magnitud leída
        }
    }

    fclose(archivo); // Cerrar el archivo
    return 1; // Lectura exitosa
}

// Marcelo Rios Finaliza

//Fernando Nuñez Inicia
// Función para calcular las diferencias consecutivas
int calcular_diferentes_tendencias(float temblores[FILAS][DIAS], int dias) {
    int creciente = 1, decreciente = 1; // Inicializar variables

    for (int j = 1; j < dias; j++) { // Recorrer cada día
        if (temblores[0][j] > temblores[0][j - 1]) { // Si la magnitud del día actual es mayor que la del día anterior
            decreciente = 0; // No es decreciente
        } else if (temblores[0][j] < temblores[0][j - 1]) { // Si la magnitud del día actual es menor que la del día anterior
            creciente = 0; // No es creciente
        }
    }

    if (creciente) return 1;      // Tendencia creciente
    if (decreciente) return -1;   // Tendencia decreciente
    return 0;                     // Tendencia variable
}

//Fernando Nuñez Finaliza

//Bastian Burgos Inicia

// Función para calcular el promedio de las magnitudes
float calcular_promedio(float temblores[FILAS][DIAS], int dias) {
    float suma = 0.0; // Inicializar variables

    for (int j = 0; j < dias; j++) { // Recorrer cada día
        suma += temblores[0][j]; // Sumar la magnitud del día
    }

    return suma / dias; // Retornar el promedio
}

// Función para contar los temblores fuertes
int contador_temblores_fuertes(float temblores[FILAS][DIAS], int dias, float limite) { 
    int contador = 0; // Inicializar variables

    for (int j = 0; j < dias; j++) { // Recorrer cada día
        if (temblores[0][j] > limite) { // Si la magnitud del día es mayor que el umbral de magnitud para considerar un temblor fuerte
            contador++; // Incrementar el contador
        }
    }

    return contador; // Retornar el número de temblores fuertes
}

//Bastian Burgos Finaliza

// Juan Pablo Inicia
// Función para mostrar los resultados
void mostrar_resultado(float temblores[FILAS][DIAS], int dias) { 
    // Calcular el promedio
    float promedio = calcular_promedio(temblores, dias); 

    // Calcular la tendencia
    int tendencia = calcular_diferentes_tendencias(temblores, dias);

    // Contar los temblores fuertes
    int fuertes = contador_temblores_fuertes(temblores, dias, LIMITE_FUERTE);

    // Mostrar resultados
    printf("Análisis de la Actividad Sísmica:\n"); // Mostrar el título
    printf("- Promedio de las magnitudes: %.2f\n", promedio); // Mostrar el promedio

    printf("- Tendencia: "); // Mostrar la tendencia
    if (tendencia == 1) { // Si la tendencia es creciente
        printf("Creciente\n"); // Mostrar el mensaje de creciente
    } else if (tendencia == -1) { // Si la tendencia es decreciente
        printf("Decreciente\n"); // Mostrar el mensaje de decreciente
    } else { // Si la tendencia es variable
        printf("Variable\n"); // Mostrar el mensaje de variable
    }

    printf("- Número de temblores fuertes (magnitud > %.1f): %d\n", LIMITE_FUERTE, fuertes); // Mostrar el número de temblores fuertes

    // Evaluar la actividad sísmica en general
    if (fuertes > 3) { // Si hay más de 3 temblores fuertes
        printf("- Actividad sísmica: Alta\n"); // Mostrar el mensaje de alta actividad sísmica
    } else { // Si no hay más de 3 temblores fuertes
        printf("- Actividad sísmica: Baja\n"); // Mostrar el mensaje de baja actividad sísmica
    }
}

//Juan Pablo Finaliza

//Fernando Nuñez Inicia 2
// Función principal
int main() {
    float temblores[FILAS][DIAS]; // Declarar la matriz de magnitudes
    char nombre_archivo[100]; // Declarar el nombre del archivo
    int archivo_cargado = 0; // Declarar la variable para almacenar el resultado de la carga del archivo

    printf("Bienvenido al analizador de actividad sísmica.\n"); // Mostrar el título
    printf("Por favor, ingrese el nombre del archivo con los datos (o escriba 'exit' para salir): "); // Mostrar el mensaje de ingreso del nombre del archivo

    while (!archivo_cargado) { // Mientras no se cargue el archivo  
        scanf("%s", nombre_archivo); // Leer el nombre del archivo

        // Verificar si el usuario quiere salir
        if (strcmp(nombre_archivo, "exit") == 0) { // Si se quiere salir
            printf("Saliendo del programa.\n"); // Mostrar el mensaje de salida
            return 0; // Retornar el código de salida
        }

        // Validar y cargar el archivo
        archivo_cargado = leer_datos(temblores, FILAS, DIAS, nombre_archivo); // Llamar a la función para cargar el archivo

        if (!archivo_cargado) { // Si no se cargó el archivo
            printf("Por favor, ingrese un nombre de archivo válido (o escriba 'exit' para salir): "); // Mostrar el mensaje de error
        }
    }

    // Si se carga correctamente, mostrar los resultados
    mostrar_resultado(temblores, DIAS); // Llamar a la función para mostrar los resultados

    return 0; // Retornar el código de salida
}
 // Fernando Finaliza 2