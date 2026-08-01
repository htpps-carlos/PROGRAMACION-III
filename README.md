# CRUD Contactos

Aplicacion de consola en C para gestionar una lista de contactos (crear, leer,
actualizar y eliminar), con persistencia en un archivo binario `contactos.dat`.

## Compilar y ejecutar

```
gcc crud.c -o crud
./crud
```

## Flujo de trabajo (Git Flow)

Este repositorio sigue Git Flow:

- `main`: version estable, lista para produccion.
- `dev`: rama de integracion de desarrollo.
- `qa`: rama de control de calidad / pruebas.
- `feature/*`: una rama por funcionalidad, integrada a `dev`, `qa` y `main` mediante Pull Requests.
- `hotfix/*`: correcciones puntuales, integradas de la misma forma.

Ramas de trabajo:

- `feature/create-contact`
- `feature/list-contacts`
- `feature/update-contact`
- `feature/delete-contact`
- `hotfix/fix-date-format`
