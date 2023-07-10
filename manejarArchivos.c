#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Alumno
{
    char nombre[20];
    char apellido[20];
    int dni;
};

int cantAlumnos;

void agregarAlumnos(struct Alumno *alumno);
void eliminarAlumno(struct Alumno *alumnos);
void modificarAlumno(struct Alumno *alumnos);
void mostrarAlumnos(struct Alumno *alumnos);
void cargarAlumnos(struct Alumno *alumnos);
void actualizarArchivo(struct Alumno *alumnos);

void main()
{
    struct Alumno alumno[10];
    cargarAlumnos(alumno);
    int opcionMenu;
    do
    {
        printf("\n======== MEN%c ========\n", 163);
        printf("1. Agregar Alumno\n");
        printf("2. Eliminar Alumno\n");
        printf("3. Modificar Alumno\n");
        printf("4. Mostrar Alumnos\n");
        printf("5. Salir\n");
        printf("======================\n");
        printf("Ingresa una opci%cn del men%c: ", 162, 163);
        scanf("%i", &opcionMenu);

        switch (opcionMenu)
        {
        case 1:
            agregarAlumnos(&alumno[cantAlumnos]);
            cantAlumnos++;
            actualizarArchivo(alumno);
            break;
        case 2:
            eliminarAlumno(alumno);
            actualizarArchivo(alumno);
            break;
        case 3:
            modificarAlumno(alumno);
            actualizarArchivo(alumno);
            break;
        case 4:
            mostrarAlumnos(alumno);
            break;
        case 5:
            break;
        default:
            printf("\nOpci%cn incorrecta.", 162);
            break;
        }
    } while (opcionMenu != 5);
}

void agregarAlumnos(struct Alumno *alumno)
{
    printf("\nIngresa NOMBRE del alumno: ");
    scanf("%s", alumno->nombre);
    printf("Ingresa APELLIDO del alumno: ");
    scanf("%s", alumno->apellido);
    do
    {
        printf("Ingresa DNI del alumno: ");
        scanf("%i", &alumno->dni);
        if (alumno->dni < 1000000 || alumno->dni > 99999999)
        {
            printf("DNI incorrecto\n");
        }

    } while (alumno->dni < 1000000 || alumno->dni > 99999999);
}
void mostrarAlumnos(struct Alumno *alumnos)
{
    if (cantAlumnos > 0)
    {
        for (int i = 0; i < cantAlumnos; i++)
        {
            printf("\n--------------\n");
            printf("Nombre: %s\n", alumnos[i].nombre);
            printf("Apellido: %s\n", alumnos[i].apellido);
            printf("DNI: %i\n", alumnos[i].dni);
        }
    }
    else
    {
        printf("No hay alumnos cargados\n");
    }
}
void eliminarAlumno(struct Alumno *alumnos)
{
    int dni, encontrado = 0, i = 0;

    printf("\nIngresa el DNI del alumno a eliminar: ");
    scanf("%i", &dni);

    while (i < cantAlumnos)
    {
        if (dni == alumnos[i].dni)
        {
            memmove(&alumnos[i], &alumnos[i + 1], (cantAlumnos - i - 1) * sizeof(struct Alumno));
            cantAlumnos--;

            printf("\nAlumno eliminado con %cxito!", 130);
            encontrado = 1;
            break;
        }
        i++;
    }
    if (encontrado == 0)
    {
        printf("\nAlumno NO encontrado.");
    }
}
void modificarAlumno(struct Alumno *alumnos)
{
    int dni, encontrado = 0, i = 0;

    printf("\nIngresa el DNI del alumno a modificar: ");
    scanf("%i", &dni);

    while (i < cantAlumnos)
    {
        if (dni == alumnos[i].dni)
        {
            printf("\nIngresa NOMBRE del alumno: ");
            scanf("%s", alumnos[i].nombre);
            printf("Ingresa APELLIDO del alumno: ");
            scanf("%s", alumnos[i].apellido);
            printf("Ingresa DNI del alumno: ");
            scanf("%i", &alumnos[i].dni);

            printf("\nAlumno MODIFICADO con %cxito!", 130);
            encontrado = 1;
            break;
        }
        i++;
    }
    if (encontrado == 0)
    {
        printf("\nAlumno NO encontrado.");
    }
}
void cargarAlumnos(struct Alumno *alumnos)
{
    FILE *archivo = fopen("alumnos.txt", "r");
    if (archivo != NULL)
    {
        char linea[100];

        fgets(linea, 100, archivo);
        sscanf(linea, "CANTIDAD:%i", &cantAlumnos);

        for (int i = 0; i < cantAlumnos; i++)
        {
            fgets(linea, sizeof(linea), archivo);
            sscanf(linea, "%[^;];%[^;];%i", alumnos[i].nombre, alumnos[i].apellido, &alumnos[i].dni);
        }

        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}
void actualizarArchivo(struct Alumno *alumnos)
{
    FILE *archivo = fopen("alumnos.txt", "w");
    if (archivo != NULL)
    {
        fprintf(archivo, "CANTIDAD:%d\n", cantAlumnos);
        for (int i = 0; i < cantAlumnos; i++)
        {
            fprintf(archivo, "%s;%s;%i;\n", alumnos[i].nombre, alumnos[i].apellido, alumnos[i].dni);
        }
        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo para guardar los datos de los alumnos.\n");
    }
}