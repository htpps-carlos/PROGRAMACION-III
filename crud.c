#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    int id;
    char nombre[50];
    char email[50];
    char telefono[20];
    char fecha_registro[11];
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

void crear(Base *base, int id, const char *nombre, const char *email, const char *telefono) {
    redimensionar(base);
    Contacto c;
    c.id = id;
    strncpy(c.nombre, nombre, 49);
    c.nombre[49] = '\0';
    strncpy(c.email, email, 49);
    c.email[49] = '\0';
    strncpy(c.telefono, telefono, 19);
    c.telefono[19] = '\0';
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    sprintf(c.fecha_registro, "%02d/%02d/%04d", tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year + 1900);
    base->contactos[base->cantidad++] = c;
}

void leer(Base *base) {
    if (base->cantidad == 0) {
        printf("No hay contactos.\n");
        return;
    }
    printf("\n%-5s %-20s %-25s %-15s %-12s\n", "ID", "Nombre", "Email", "Telefono", "Registrado");
    printf("%-5s %-20s %-25s %-15s %-12s\n", "--", "------", "-----", "--------", "----------");
    for (int i = 0; i < base->cantidad; i++) {
        printf("%-5d %-20s %-25s %-15s %-12s\n",
               base->contactos[i].id,
               base->contactos[i].nombre,
               base->contactos[i].email,
               base->contactos[i].telefono,
               base->contactos[i].fecha_registro);
    }
    printf("\n");
}

int buscar_indice(Base *base, int id) {
    for (int i = 0; i < base->cantidad; i++) {
        if (base->contactos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void actualizar(Base *base, int id, const char *nombre, const char *email, const char *telefono) {
    int idx = buscar_indice(base, id);
    if (idx == -1) {
        printf("Contacto con ID %d no encontrado.\n", id);
        return;
    }
    strncpy(base->contactos[idx].nombre, nombre, 49);
    base->contactos[idx].nombre[49] = '\0';
    strncpy(base->contactos[idx].email, email, 49);
    base->contactos[idx].email[49] = '\0';
    strncpy(base->contactos[idx].telefono, telefono, 19);
    base->contactos[idx].telefono[19] = '\0';
    printf("Contacto actualizado.\n");
}

void eliminar(Base *base, int id) {
    int idx = buscar_indice(base, id);
    if (idx == -1) {
        printf("Contacto con ID %d no encontrado.\n", id);
        return;
    }
    for (int i = idx; i < base->cantidad - 1; i++) {
        base->contactos[i] = base->contactos[i + 1];
    }
    base->cantidad--;
    printf("Contacto eliminado.\n");
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

    int opcion, id;
    char nombre[50], email[50], telefono[20];

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
                printf("ID: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                printf("Nombre: ");
                fgets(nombre, 50, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                printf("Email: ");
                fgets(email, 50, stdin);
                email[strcspn(email, "\n")] = '\0';
                printf("Telefono: ");
                fgets(telefono, 20, stdin);
                telefono[strcspn(telefono, "\n")] = '\0';
                crear(base, id, nombre, email, telefono);
                printf("Contacto creado.\n");
                break;
            case 2:
                leer(base);
                break;
            case 3:
                printf("ID a actualizar: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                printf("Nuevo nombre: ");
                fgets(nombre, 50, stdin);
                nombre[strcspn(nombre, "\n")] = '\0';
                printf("Nuevo email: ");
                fgets(email, 50, stdin);
                email[strcspn(email, "\n")] = '\0';
                printf("Nuevo telefono: ");
                fgets(telefono, 20, stdin);
                telefono[strcspn(telefono, "\n")] = '\0';
                actualizar(base, id, nombre, email, telefono);
                break;
            case 4:
                printf("ID a eliminar: ");
                scanf("%d", &id);
                while (getchar() != '\n');
                eliminar(base, id);
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
