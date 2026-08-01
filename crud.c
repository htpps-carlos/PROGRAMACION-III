#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int id;
    char nombre[50];
    char email[50];
    char telefono[20];
} Contacto;

typedef struct {
    Contacto *contactos;
    int cantidad;
    int capacidad;
} Base;

Base* inicializar() {
    Base *base = (Base*)malloc(sizeof(Base));
    base->capacidad = 10;
    base->cantidad = 0;
    base->contactos = (Contacto*)malloc(base->capacidad * sizeof(Contacto));
    return base;
}

void redimensionar(Base *base) {
    if (base->cantidad >= base->capacidad) {
        base->capacidad *= 2;
        base->contactos = (Contacto*)realloc(base->contactos, base->capacidad * sizeof(Contacto));
    }
}

void guardar(Base *base, const char *archivo) {
    FILE *f = fopen(archivo, "wb");
    if (!f) return;
    fwrite(&base->cantidad, sizeof(int), 1, f);
    fwrite(base->contactos, sizeof(Contacto), base->cantidad, f);
    fclose(f);
}

void cargar(Base *base, const char *archivo) {
    FILE *f = fopen(archivo, "rb");
    if (!f) return;
    fread(&base->cantidad, sizeof(int), 1, f);
    if (base->cantidad > base->capacidad) {
        base->capacidad = base->cantidad * 2;
        base->contactos = (Contacto*)realloc(base->contactos, base->capacidad * sizeof(Contacto));
    }
    fread(base->contactos, sizeof(Contacto), base->cantidad, f);
    fclose(f);
}

void liberar(Base *base) {
    free(base->contactos);
    free(base);
}

void mostrar_menu() {
    printf("\n=== CRUD CONTACTOS ===\n");
    printf("1. Crear contacto\n");
    printf("2. Leer contactos\n");
    printf("3. Actualizar contacto\n");
    printf("4. Eliminar contacto\n");
    printf("5. Guardar y salir\n");
    printf("Seleccione: ");
}

int main() {
    Base *base = inicializar();
    cargar(base, "contactos.dat");

    int opcion;

    while (1) {
        mostrar_menu();
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            printf("Entrada invalida.\n");
            continue;
        }
        while (getchar() != '\n');

        switch (opcion) {
            case 1:
                printf("Funcionalidad de creacion aun no implementada.\n");
                break;
            case 2:
                printf("Funcionalidad de listado aun no implementada.\n");
                break;
            case 3:
                printf("Funcionalidad de actualizacion aun no implementada.\n");
                break;
            case 4:
                printf("Funcionalidad de eliminacion aun no implementada.\n");
                break;
            case 5:
                guardar(base, "contactos.dat");
                liberar(base);
                printf("Datos guardados. Hasta luego.\n");
                return 0;
            default:
                printf("Opcion invalida.\n");
        }
    }

    return 0;
}
